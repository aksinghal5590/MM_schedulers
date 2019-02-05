#ifndef C_SHARE_SCHEDULER_H
#define C_SHARE_SCHEDULER_H

class CShareScheduler {

private:
	bool processComplete;

public:

	CShareScheduler() {
		processComplete = false;
	}

	void* runThread();

	static void* runThread_helper(void* context) {
		return ((CShareScheduler*)context)->runThread();
	}
};

#endif