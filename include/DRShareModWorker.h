#ifndef DR_SHARE_WORKER_H
#define DR_SHARE_WORKER_H

#include <random>
#include <tbb/concurrent_queue.h>

#include "DRShareModScheduler.h"
#include "MMParRecTask.h"

using namespace std;

class DRShareModWorker {

private:
	int id;
	int numCPU;
	tbb::concurrent_bounded_queue<MMParRecTask*> *task_queue;
	uint64_t *work;
	DRShareModScheduler& shareScheduler;

public:

	DRShareModWorker(
		int id,
		int numCPU,
		tbb::concurrent_bounded_queue<MMParRecTask*> *task_queue,
		uint64_t *work,
		DRShareModScheduler& shareScheduler) : id(id),
											numCPU(numCPU),
											task_queue(task_queue),
											work(work),
											shareScheduler(shareScheduler) {

	}

	void operator()() {
		//cout << "Starting thread " << id << endl;
		subtract_with_carry_engine<uint_fast32_t, 9, 10, 24> randGenerator(id + 1);
		MMParRecTask *task = NULL;
		while(true) {
			if(!shareScheduler.isProcessComplete()) {
				if(task_queue->try_pop(task)) {
					(*work) -= task->getWorkAmt();
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
							(*work) -= share_task->getWorkAmt();
							int randomNo1 = (randGenerator() % numCPU);
							if(randomNo1 == id) {
								randomNo1 = (randomNo1 + 1) % numCPU;
							}
							int randomNo2 = (randGenerator() % numCPU);
							if(randomNo2 == id) {
								randomNo2 = (randomNo1 + 2) % numCPU;
							}
							uint64_t work1 = shareScheduler.getWorkAmtFromQueue(randomNo1);
							uint64_t work2 = shareScheduler.getWorkAmtFromQueue(randomNo2);
							if(work1 <= work2) {
								shareScheduler.addTaskToQueue(randomNo1, share_task);
							} else {
								shareScheduler.addTaskToQueue(randomNo2, share_task);
							}
						}
					}
					task->call_mmParRec(task_queue, work);
					task_queue->push(task);
					(*work) += task->getWorkAmt();
				}
			} else {
				break;
			}
		}
		//cout << "Finishing thread " << id << endl;
	}
};

#endif