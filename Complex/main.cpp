#include <iostream>
#include <algorithm>
#include <vector>
#include "complex.h"

void Sort(std::vector<Complex> &v)
{
	for(int i = 0; i < v.size(); ++i)
	for(int j = i + 1; j < v.size(); ++j)
	if(v[j] < v[i]) std::swap(v[i], v[j]);
}

int main()
{
	int n;
	std::cin >> n;
	std::vector<Complex> v(n);
	
	for(int i = 0; i < n; ++i)
		std::cin >> v[i];

	Sort(v);
	
	for(int i = 0; i < n; ++i)
		std::cout << v[i] << " ";
	std::cout << '\n';
}
