#include "ParallelScheduler.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

ParallelScheduler::ParallelScheduler(int count) : 
			capacity(count), 
			threads(std::vector<pthread_t>(count)),
			lock(new pthread_mutex_t()),
			cond(new pthread_cond_t())
{
	pthread_mutex_init(lock, NULL);
	pthread_cond_init(cond, NULL);
	
	for (auto& thread : threads)
	{
		int error = pthread_create(&thread, NULL, execute, this);
		if(error)
		{
			perror("Failed to create a thread");
			exit(error);
		}
	}
}
	
void ParallelScheduler::run(void (*func)(void*), void* arg) 
{
	// lock the queue
	pthread_mutex_lock(lock);

	// queue the function for execution
	functions.push(std::make_pair(func, arg));

	// unlock the queue
	pthread_mutex_unlock(lock);
			
	// signal about a new function
	pthread_cond_broadcast(cond);
}

void* ParallelScheduler::execute(void* arg)
{
	ParallelScheduler* sch = (ParallelScheduler*)arg;

	while(true)
	{
		// lock the queue
		pthread_mutex_lock(sch->lock);

		// wait for a function to run
		while(sch->functions.empty())
		{
			pthread_cond_wait(sch->cond, sch->lock);
		}

		auto cur = sch->functions.front();
		sch->functions.pop();

		// unlock the queue
		pthread_mutex_unlock(sch->lock);

		// execute the function
		cur.first(cur.second);
	}

	return nullptr; 
}

ParallelScheduler::~ParallelScheduler()
{		
	for(auto& thread : threads)
		pthread_cancel(thread);
		
	pthread_mutex_destroy(lock);
	pthread_cond_destroy(cond);

	delete lock; 
	delete cond;	 
}