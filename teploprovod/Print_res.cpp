#include<iostream>
#include <vector>


void print_res(std::vector<double> T_arr)
{
	using Iter = std::vector<double>::const_iterator;
	for (Iter it = T_arr.begin(); it != T_arr.end(); ++it) {
		std::cout << *it << std::endl;
	}
}