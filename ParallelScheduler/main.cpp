#include "ParallelScheduler.h"
#include <iostream>


void f(void* arg)
{
	std::cout << "f" << *(int*)arg << '\n';
}


int main()
{
	ParallelScheduler* scheduler = new ParallelScheduler(3);

	for(int i = 0; i < 12; ++i)
	{
		int* arg = &i;
		scheduler->run(f, arg);
	}
	
	//delete scheduler;
}