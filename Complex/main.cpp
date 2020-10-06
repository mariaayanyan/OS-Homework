#include "complex.h"
#include <iostream>
#include <algorithm>
#include <vector>

void Sort(std::vector<Complex> &vComplex)
{
	for(int i = 0; i < vComplex.size(); ++i)
		for(int j = i + 1; j < vComplex.size(); ++j)
			if(vComplex[j] < vComplex[i]) 
				std::swap(vComplex[i], vComplex[j]);
}

int main()
{
	int n; 
	std::cin >> n;
	std::vector<Complex> v(n);
	
	// read n complex numbers
	for(int i = 0; i < n; ++i)
		std::cin >> v[i];
	
	// sort the given complex numbers by their absolute vakue in increasing order
	Sort(v);
	    
	// print the complex numbers
	for(int i = 0; i < n; ++i)
		std::cout << v[i] << " ";
	std::cout << '\n';
}