#ifndef MM_PAR_REC_TASK_H
#define MM_PAR_REC_TASK_H

#include <deque>
#include <tbb/concurrent_queue.h>

using namespace std;

class MMParRecTask {

private:
	int *mZ;
	int row0;
	int col0;
	int *mX;
	int row1;
	int col1;
	int *mY;
	int row2;
	int col2;
	int n;
	int size;
	int base;
	bool atSync1;
	bool atSync2;
	bool isFirst;
	bool isComplete;
	MMParRecTask *task1;
	MMParRecTask *task2;
	MMParRecTask *task3;
	MMParRecTask *task4;
	MMParRecTask *task5;
	MMParRecTask *task6;
	MMParRecTask *task7;
	MMParRecTask *task8;

public:

	MMParRecTask() {}

	MMParRecTask(
		int *mZ,
		int row0,
		int col0,
		int *mX,
		int row1,
		int col1,
		int *mY,
		int row2,
		int col2,
		int n,
		int size,
		int base,
		bool isFirst) : mZ(mZ), row0(row0), col0(col0), mX(mX), row1(row1), col1(col1),
				   mY(mY), row2(row2), col2(col2), n(n), size(size), base(base), isFirst(isFirst) {

		atSync1 = false;
		atSync2 = false;
		isComplete = false;
		task1 = NULL;
		task2 = NULL;
		task3 = NULL;
		task4 = NULL;
		task5 = NULL;
		task6 = NULL;
		task7 = NULL;
		task8 = NULL;
	}

	void call_mmParRec();

	void call_mmParRec(tbb::concurrent_bounded_queue<MMParRecTask*> *task_queue);

	void call_mmParRec(tbb::concurrent_bounded_queue<MMParRecTask*> *task_queue, uint64_t *work);

	bool isFirstTask() {
		return isFirst;
	}

	bool isTaskComplete() {
		return isComplete;
	}

	uint64_t getWorkAmt() {
		uint64_t w = n;
		return(w*w*w);
	}

	int getN() {
		return n;
	}

	~MMParRecTask() {
		delete task1;
		delete task2;
		delete task3;
		delete task4;
		delete task5;
		delete task6;
		delete task7;
		delete task8;
	}
};

#endif