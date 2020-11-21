#include <queue>
#include <utility>
#include <pthread.h>

class ParallelScheduler
{
	// queue of pointers to functions and their arguments
	std::queue<std::pair<void (*)(void*), void*> > functions;

	// threads to run in parallel 
	std::vector<pthread_t> threads;

	// the number of tasks that can be executed in parallel
	int capacity;

	// thread condition variable 
	pthread_cond_t* cond;

	// mutex lock for the functions
	pthread_mutex_t* lock;

	// execute the functions
	static void* execute(void* arg);

public:
	ParallelScheduler(int count);
	void run(void (*func)(void*), void* arg);
	~ParallelScheduler();
};