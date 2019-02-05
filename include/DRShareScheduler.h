#ifndef DR_SHARE_SCHEDULER_H
#define DR_SHARE_SCHEDULER_H

#include <vector>
#include <tbb/concurrent_queue.h>

#include "MMParRecTask.h"

class DRShareScheduler {

private:
	bool isComplete;
	vector<tbb::concurrent_bounded_queue<MMParRecTask*>>& queueList;


public:

	DRShareScheduler(
		vector<tbb::concurrent_bounded_queue<MMParRecTask*>>& queueList) : queueList(queueList) {

		isComplete = false;
	}

	bool isProcessComplete() {
		return isComplete;
	}

	void setProcessComplete(bool isComplete) {
		this->isComplete = isComplete;
	}

	void addTaskToQueue(int pos, MMParRecTask* task) {
		queueList[pos].push(task);
	}
};

#endif