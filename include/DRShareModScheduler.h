#ifndef DR_SHARE_SCHEDULER_H
#define DR_SHARE_SCHEDULER_H

#include <vector>
#include <tbb/concurrent_queue.h>
#include <tbb/concurrent_vector.h>

#include "MMParRecTask.h"

using namespace std;

class DRShareModScheduler {

private:
	bool isComplete;
	vector<tbb::concurrent_bounded_queue<MMParRecTask*>>& queueList;
	tbb::concurrent_vector<uint64_t>& workList;

public:

	DRShareModScheduler(
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

	void addTaskToQueue(int pos, MMParRecTask* task) {
		queueList[pos].push(task);
		workList[pos] += task->getWorkAmt();
	}

	uint64_t getWorkAmtFromQueue(int pos) {
		return workList[pos];
	}
};

#endif