#ifndef DR_STEAL_WORKER_H
#define DR_STEAL_WORKER_H

#include <random>
#include <tbb/concurrent_queue.h>

#include "DRStealScheduler.h"
#include "MMParRecTask.h"

using namespace std;

class DRStealWorker {

private:
	int id;
	int numCPU;
	tbb::concurrent_bounded_queue<MMParRecTask*> *task_queue;
	DRStealScheduler& stealScheduler;

public:

	DRStealWorker(
		int id,
		int numCPU,
		tbb::concurrent_bounded_queue<MMParRecTask*> *task_queue,
		DRStealScheduler& stealScheduler) : id(id),
											numCPU(numCPU),
											task_queue(task_queue),
											stealScheduler(stealScheduler) {

	}

	void operator()() {
		//cout << "Starting thread " << id << endl;
		subtract_with_carry_engine<uint_fast32_t, 9, 10, 24> randGenerator(id + 1);
		MMParRecTask *task = NULL;
		while(true) {
			if(!stealScheduler.isProcessComplete()) {
				if(task_queue->try_pop(task)) {
					if(task->isTaskComplete()) {
						if(task->isFirstTask()) {
							stealScheduler.setProcessComplete(true);
							break;
						}
						continue;
					}
					task->call_mmParRec(task_queue);
					task_queue->push(task);
				} else {
					int randomNo = (randGenerator() % numCPU);
					if(randomNo == id) {
						randomNo = (id + 1) % numCPU;
					}
					task = stealScheduler.getTopFromQueue(randomNo);
					if(task != NULL) {
						//cout << "Task Stolen by thread# " << id << endl;
						task_queue->push(task);
					}
				}
			} else {
				break;
			}
		}
		//cout << "Finishing thread " << id << endl;
	}
};

#endif
