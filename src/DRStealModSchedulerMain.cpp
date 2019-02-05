#include <cstdlib>
#include <iostream>
#include <sstream>
#include <atomic>
#include <vector>
#include <tbb/tbb.h>
#include <tbb/compat/thread>
#include <tbb/concurrent_queue.h>
#include <tbb/concurrent_vector.h>

#include "DRStealModWorker.h"
#include "DRStealModScheduler.h"
#include "MMParRecTask.h"

using namespace std;

void init(int *m, int row, int col) {
	int a = 1;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			m[i * col + j] = (a++) % 10;
		}
		a = 1;
	}
}

void printMatrix(int *m, int row, int col) {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			cout << m[i * col + j] << " ";
		}
		cout << endl;
	}
}

void mmIKJ(int *mZ, int row0, int col0, int *mX, int row1, int col1, int *mY, int row2, int col2, int n, int size) {

	for (int i = 0; i < n; ++i) {
		for (int k = 0; k < n; ++k) {
			for (int j = 0; j < n; ++j) {
				mZ[(i + row0) * size + col0 + j] += mX[(row1 + i) * size + col1 + k] * mY[(row2 + k) * size + col2 + j];
			}
		}
	}
}

void MMParRecTask::call_mmParRec(tbb::concurrent_bounded_queue<MMParRecTask*> *task_queue, uint64_t *work) {
	if (n == base) {
		mmIKJ(mZ, row0, col0, mX, row1, col1, mY, row2, col2, n, size);
	} else {
		if(!atSync1) {
			//Z11, X11, Y11
			task1 = new MMParRecTask(mZ, row0, col0, mX, row1, col1, mY, row2, col2, n / 2, size, base, false);
			task_queue->push(task1);
			(*work) += task1->getWorkAmt();

			//Z12, X11, Y12
			task2 = new MMParRecTask(mZ, row0, col0 + n / 2, mX, row1, col1, mY, row2, col2 + n / 2, n / 2, size, base, false);
			task_queue->push(task2);
			(*work) += task2->getWorkAmt();

			//Z21, X21, Y11
			task3 = new MMParRecTask(mZ, row0 + n / 2, col0, mX, row1 + n / 2, col1, mY, row2, col2, n / 2, size, base, false);
			task_queue->push(task3);
			(*work) += task3->getWorkAmt();

			//Z22, X21, Y12
			task4 = new MMParRecTask(mZ, row0 + n / 2, col0 + n / 2, mX, row1 + n / 2, col1, mY, row2, col2 + n / 2, n / 2, size, base, false);
			task_queue->push(task4);
			(*work) += task4->getWorkAmt();

			atSync1 = true;
		}
		if((task1 != NULL && !task1->isTaskComplete()) || (task2 != NULL && !task2->isTaskComplete()) ||
			(task3 != NULL && !task3->isTaskComplete()) || (task4 != NULL && !task4->isTaskComplete())) {
			return;
		}
		if(!atSync2) {
			//Z11, X12, Y21
			task5 = new MMParRecTask(mZ, row0, col0, mX, row1, col1 + n / 2, mY, row2 + n / 2, col2, n / 2, size, base, false);
			task_queue->push(task5);
			(*work) += task5->getWorkAmt();

			//Z12, X12, Y22
			task6 = new MMParRecTask(mZ, row0, col0 + n / 2, mX, row1, col1 + n / 2, mY, row2 + n / 2, col2 + n / 2, n / 2, size, base, false);
			task_queue->push(task6);
			(*work) += task6->getWorkAmt();

			//Z21, X22, Y21
			task7 = new MMParRecTask(mZ, row0 + n / 2, col0, mX, row1 + n / 2, col1 + n / 2,
				mY, row2 + n / 2, col2, n / 2, size, base, false);
			task_queue->push(task7);
			(*work) += task7->getWorkAmt();

			//Z22, X22, Y22
			task8 = new MMParRecTask(mZ, row0 + n / 2, col0 + n / 2, mX, row1 + n / 2, col1 + n / 2,
				mY, row2 + n / 2, col2 + n / 2, n / 2, size, base, false);
			task_queue->push(task8);
			(*work) += task8->getWorkAmt();

			atSync2 = true;
		}
		if((task5 != NULL && !task5->isTaskComplete()) || (task6 != NULL && !task6->isTaskComplete()) ||
			(task7 != NULL && !task7->isTaskComplete()) || (task8 != NULL && !task8->isTaskComplete())) {
			return;
		}
	}
	//cout << "Task Complete - n = " << n <<" base = "<< base << endl;
	isComplete = true;
}

int main(int argc, char *argv[]) {

	if(argc < 2) {
		cout << "Please provide N to construct matrices of size NxN." << endl;
		return 1;
	}
	if(argc < 3) {
		cout << "Please provide the value of base." << endl;
		return 1;
	}
	if (argc < 4) {
		cout << "Please provide the count of threads to run." << endl;
		return -1;
	}
	int n;
	istringstream iss1(argv[1]);
	if(!(iss1 >> n)) {
		cerr << "Invalid number: " << argv[1] << endl;
		return 1;
	}
	int base;
	istringstream iss2(argv[2]);
	if(!(iss2 >> base)) {
		cerr << "Invalid number: " << argv[2] << endl;
		return 1;
	}
	int numCPU;
	istringstream iss3(argv[3]);
	if (!(iss3 >> numCPU)) {
		cerr << "Invalid number: " << argv[3] << endl;
		return -1;
	}

	int *mX = new int[n*n];
	int *mY = new int[n*n];
	int *mZ = new int[n*n];
	init(mX, n, n);
	init(mY, n, n);
	memset(mZ, 0, sizeof(int) * n * n);
	//printMatrix(mX, n, n);

	MMParRecTask task0(mZ, 0, 0, mX, 0, 0, mY, 0, 0, n, n, base, true);
	vector<tbb::concurrent_bounded_queue<MMParRecTask*>> queueList(numCPU);
	tbb::concurrent_vector<uint64_t> workList(numCPU);
	DRStealModScheduler stealScheduler(queueList, workList);
	queueList[0].push(&task0);
	workList[0] += task0.getWorkAmt();

	auto start = std::chrono::system_clock::now();

	vector<unique_ptr<tbb::tbb_thread>> threads(numCPU);
	for(int i = 0; i < threads.size(); i++) {
		DRStealModWorker worker(i, numCPU, &queueList[i], &workList[i], stealScheduler);
		threads[i].reset(new tbb::tbb_thread(worker));
	}
	for(int i = 0; i < threads.size(); i++) {
		threads[i]->join();
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	//printMatrix(mZ, n, n);

	cout << "Time taken using "
		 << "DR-Steal-Mod scheduler with "
		 << "n=" << n
		 << ", base=" << base
		 << " and thread_count=" << numCPU
		 << " : " << elapsed_seconds.count() << " s "
		 << endl;

	delete[] mX;
	delete[] mY;
	delete[] mZ;

	return 0;
}
