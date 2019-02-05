#ifndef DR_SHARE_WORKER_H
#define DR_SHARE_WORKER_H

#include <random>
#include <tbb/concurrent_queue.h>

#include "DRShareScheduler.h"
#include "MMParRecTask.h"

using namespace std;

class DRShareWorker {

private:
	int id;
	int numCPU;
	tbb::concurrent_bounded_queue<MMParRecTask*> *task_queue;
	DRShareScheduler& shareScheduler;

public:

	DRShareWorker(
		int id,
		int numCPU,
		tbb::concurrent_bounded_queue<MMParRecTask*> *task_queue,
		DRShareScheduler& shareScheduler) : id(id),
											numCPU(numCPU),
											task_queue(task_queue),
											shareScheduler(shareScheduler) {

	}

	void operator()() {
		//cout << "Starting thread " << id << endl;
		subtract_with_carry_engine<uint_fast32_t, 9, 10, 24> randGenerator(id + 1);
		MMParRecTask *task = NULL;
		while(true) {
			if(!shareScheduler.isProcessComplete()) {
				if(task_queue->try_pop(task)) {
					if(task->isTaskComplete()) {
						if(task->isFirstTask()) {
							shareScheduler.setProcessComplete(true);
							break;
						}
						continue;
					}
					while(!task_queue->empty() && numCPU > 1) {
						MMParRecTask *share_task = NULL;
						if(task_queue->try_pop(share_task)) {
							int randomNo = (randGenerator() % numCPU);
							if(randomNo == id) {
								randomNo = (id + 1) % numCPU;
							}
							shareScheduler.addTaskToQueue(randomNo, share_task);
						}
					}
					task->call_mmParRec(task_queue);
					task_queue->push(task);
				}
			} else {
				break;
			}
		}
		//cout << "Finishing thread " << id << endl;
	}
};

#endif