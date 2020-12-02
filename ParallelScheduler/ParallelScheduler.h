#ifndef PARALLEL_SCHEDULER_H
#define PARALLEL_SCHEDULER_H

#include <pthread.h>
#include <queue>
#include <utility>

typedef void (*scheduler_fn_t)(void*);

class ParallelScheduler
{
private:
	// the number of tasks that can be executed in parallel
	int capacity;

	// threads to run in parallel 
	pthread_t* threads;
	
	// queue of pointers to functions and their arguments
	std::queue<std::pair<scheduler_fn_t, void*> > functions;

	// mutex lock for queue
	pthread_mutex_t* queueLock;

	// thread condition variable 
	pthread_cond_t* hasFunction;

private:
	// execute the functions
	static void* execute(void* arg);	
	
public:
	ParallelScheduler(int capacity);
	void run(scheduler_fn_t func, void* arg);
	~ParallelScheduler();
};

#endif
