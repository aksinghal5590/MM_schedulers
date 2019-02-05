#ifndef DR_STEAL_SCHEDULER_H
#define DR_STEAL_SCHEDULER_H

#include <vector>
#include <tbb/concurrent_queue.h>

#include "MMParRecTask.h"

using namespace std;

class DRStealScheduler {

private:
	bool isComplete;
	vector<tbb::concurrent_bounded_queue<MMParRecTask*>>& queueList;


public:

	DRStealScheduler(
		vector<tbb::concurrent_bounded_queue<MMParRecTask*>>& queueList) : queueList(queueList) {

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
		queueList[pos].try_pop(task);
		return task;
	}
};

#endif