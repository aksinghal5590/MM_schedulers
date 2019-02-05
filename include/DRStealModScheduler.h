#ifndef DR_STEAL_SCHEDULER_H
#define DR_STEAL_SCHEDULER_H

#include <vector>
#include <tbb/concurrent_queue.h>
#include <tbb/concurrent_vector.h>

#include "MMParRecTask.h"

using namespace std;

class DRStealModScheduler {

private:
	bool isComplete;
	vector<tbb::concurrent_bounded_queue<MMParRecTask*>>& queueList;
	tbb::concurrent_vector<uint64_t>& workList;

public:

	DRStealModScheduler(
		vector<tbb::concurrent_bounded_queue<MMParRecTask*>>& queueList,
		tbb::concurrent_vector<uint64_t>& workList) : queueList(queueList), workList(workList) {

		isComplete = false;
	}

	bool isProcessComplete() {
		return isComplete;
	}

	void setProcessComplete(bool isComplete) {
		this->isComplete = isComplete;
	}

	MMParRecTask* getTopFromQueue(int pos) {
		MMParRecTask* task = NULL;
		if(queueList[pos].try_pop(task)) {
			workList[pos] -= task->getWorkAmt();
		}
		return task;
	}

	uint64_t getWorkAmtFromQueue(int pos) {
		return workList[pos];
	}

};

#endif