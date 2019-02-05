#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <papi.h>
#include <tbb/tbb.h>
#include <tbb/compat/thread>
#include <tbb/concurrent_queue.h>

#include "DRStealWorker.h"
#include "DRStealScheduler.h"
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

void MMParRecTask::call_mmParRec(tbb::concurrent_bounded_queue<MMParRecTask*> *task_queue) {
	if (n == base) {
		mmIKJ(mZ, row0, col0, mX, row1, col1, mY, row2, col2, n, size);
	} else {
		if(!atSync1) {
			//Z11, X11, Y11
			task1 = new MMParRecTask(mZ, row0, col0, mX, row1, col1, mY, row2, col2, n / 2, size, base, false);
			task_queue->push(task1);

			//Z12, X11, Y12
			task2 = new MMParRecTask(mZ, row0, col0 + n / 2, mX, row1, col1, mY, row2, col2 + n / 2, n / 2, size, base, false);
			task_queue->push(task2);

			//Z21, X21, Y11
			task3 = new MMParRecTask(mZ, row0 + n / 2, col0, mX, row1 + n / 2, col1, mY, row2, col2, n / 2, size, base, false);
			task_queue->push(task3);

			//Z22, X21, Y12
			task4 = new MMParRecTask(mZ, row0 + n / 2, col0 + n / 2, mX, row1 + n / 2, col1, mY, row2, col2 + n / 2, n / 2, size, base, false);
			task_queue->push(task4);

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
			//Z12, X12, Y22
			task6 = new MMParRecTask(mZ, row0, col0 + n / 2, mX, row1, col1 + n / 2, mY, row2 + n / 2, col2 + n / 2, n / 2, size, base, false);
			task_queue->push(task6);
			//Z21, X22, Y21
			task7 = new MMParRecTask(mZ, row0 + n / 2, col0, mX, row1 + n / 2, col1 + n / 2,
				mY, row2 + n / 2, col2, n / 2, size, base, false);
			task_queue->push(task7);
			//Z22, X22, Y22
			task8 = new MMParRecTask(mZ, row0 + n / 2, col0 + n / 2, mX, row1 + n / 2, col1 + n / 2,
				mY, row2 + n / 2, col2 + n / 2, n / 2, size, base, false);
			task_queue->push(task8);

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
	if (argc < 5) {
		cout << "Please provide 1/2 for L1/L2 cache miss evaluation." << endl;
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
	int PAPI;
	istringstream iss4(argv[4]);
	if (!(iss4 >> PAPI)) {
		cerr << "Invalid number: " << argv[4] << endl;
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
	queueList[0].push(&task0);
	DRStealScheduler stealScheduler(queueList);

	int retval, eventSet = PAPI_NULL;
	long_long values[2] = {0};

	/* Initialize the PAPI library */
	retval = PAPI_library_init(PAPI_VER_CURRENT);

	if (retval != PAPI_VER_CURRENT) {
		fprintf(stderr, "PAPI library init error!\n");
		return - 1;
	}
	if (PAPI_create_eventset(&eventSet) != PAPI_OK) {
		cerr << "error_create" << endl;
		return -1;
	}
	if (PAPI == 1) {
		if (PAPI_add_event(eventSet, PAPI_L1_TCM) != PAPI_OK) {
			cerr << "Error adding L1 cache" << endl;
			return -1;
		}
	} else if (PAPI == 2) {
		if (PAPI_add_event(eventSet, PAPI_L2_TCM) != PAPI_OK) {
			cerr << "Error adding L2 cache" << endl;
			return -1;
		}
	} else if (PAPI == 3) {
		if (PAPI_add_event(eventSet, PAPI_L3_TCM) != PAPI_OK) {
			cerr << "Error adding L3 cache" << endl;
			return -1;
		}
	} else {
		cout << "Wrong input" << endl;
		return -1;
	}
	if (PAPI_start(eventSet) != PAPI_OK) {
		cerr << "start_error" << endl;
		return -1;
	}

	vector<unique_ptr<tbb::tbb_thread>> threads(numCPU);
	for(int i = 0; i < threads.size(); i++) {
		DRStealWorker worker(i, numCPU, &queueList[i], stealScheduler);
		threads[i].reset(new tbb::tbb_thread(worker));
	}
	for(int i = 0; i < threads.size(); i++) {
		threads[i]->join();
	}

	if (PAPI_read(eventSet, values) != PAPI_OK) {
		cerr << "read error" << endl;
		return -1;
	}
	if (PAPI_stop(eventSet, values) != PAPI_OK) {
		cerr << "stop error" << endl;
		return -1;
	}
	cout << "L" << PAPI
		 << " cache misses for DR-steal scheduler with "
		 << "n=" << n
		 << ", base=" << base
		 << " and thread_count=" << numCPU
		 << " : " << values[0] << endl;

	//printMatrix(mZ, n, n);

	delete[] mX;
	delete[] mY;
	delete[] mZ;

	return 0;
}
