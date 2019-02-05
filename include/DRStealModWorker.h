#ifndef DR_STEAL_WORKER_H
#define DR_STEAL_WORKER_H

#include <random>
#include <tbb/concurrent_queue.h>

#include "DRStealModScheduler.h"
#include "MMParRecTask.h"

using namespace std;

class DRStealModWorker {

private:
	int id;
	int numCPU;
	tbb::concurrent_bounded_queue<MMParRecTask*> *task_queue;
	DRStealModScheduler& stealScheduler;
	uint64_t *work;

public:

	DRStealModWorker(
		int id,
		int numCPU,
		tbb::concurrent_bounded_queue<MMParRecTask*> *task_queue,
		uint64_t *work,
		DRStealModScheduler& stealScheduler) : id(id),
											numCPU(numCPU),
											task_queue(task_queue),
											work(work),
											stealScheduler(stealScheduler) {

	}

	void operator()() {
		//cout << "Starting thread " << id << endl;
		subtract_with_carry_engine<uint_fast32_t, 9, 10, 24> randGenerator(id + 1);
		MMParRecTask *task = NULL;
		while(true) {
			if(!stealScheduler.isProcessComplete()) {
				if(task_queue->try_pop(task)) {
					(*work) -= task->getWorkAmt();
					if(task->isTaskComplete()) {
						if(task->isFirstTask()) {
							stealScheduler.setProcessComplete(true);
							break;
						}
						continue;
					}
					task->call_mmParRec(task_queue, work);
					task_queue->push(task);
					(*work) += task->getWorkAmt();
				} else {
					int randomNo1 = (randGenerator() % numCPU);
					if(randomNo1 == id) {
						randomNo1 = (id + 1) % numCPU;
					}
					int randomNo2 = (randGenerator() % numCPU);
					if(randomNo2 == id) {
						randomNo2 = (id + 2) % numCPU;
					}
					uint64_t work1 = stealScheduler.getWorkAmtFromQueue(randomNo1);
					uint64_t work2 = stealScheduler.getWorkAmtFromQueue(randomNo2);
					if(work1 >= work2) {
						task = stealScheduler.getTopFromQueue(randomNo1);
					} else {
						task = stealScheduler.getTopFromQueue(randomNo2);
					}
					if(task != NULL) {
						//cout << "Task Stolen by thread# " << id << endl;
						task_queue->push(task);
						(*work) += task->getWorkAmt();
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
