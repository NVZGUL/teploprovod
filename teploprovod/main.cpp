#include<iostream>
#include <vector>
#include <thread>
#include "Task.h"
#include "Simple.h"
#include "Thread_r.h"
#include "OpenMp_r.h"


int main()
{	
	//input params
	
	double time = 0;
	std::vector<double> T_arr;
	std::vector<double> alfa;
	std::vector<double> beta;

	auto h_step = [](double L, int N) { return L / (N - 1); };
	auto tau_step = [](double t) { return t / t1; }; 

	double h = h_step(L, N);
	double tau = tau_step(t_final);
	

	for(int i = 0; i < N; i++)
	{
		T_arr.push_back(0);
		alfa.push_back(0);
		beta.push_back(0);
	}

	//Неявная
	clock_t start = clock();
	//neyavn_thread(time, tau, h, alfa, beta, T_arr);
	//	yavn_thread(time, h, T_arr);
	clock_t end = clock();
	//std::cout << "Thread time is: " << (float)(end - start) / CLOCKS_PER_SEC << std::endl;
	//start = clock();
	neyavn(time, tau, h, alfa, beta, T_arr);
	//	yavn(time, h, T_arr);
	//end = clock();
	//std::cout << "Simple time is: " << (float)(end - start) / CLOCKS_PER_SEC << std::endl;
	//start = clock();
	//neyavn_openMP(time, tau, h, alfa, beta, T_arr);
	//	yavn_openMP(time, h, T_arr);
	//end = clock();
	//std::cout << "OpenMP time is: " << (float)(end - start)/ CLOCKS_PER_SEC << std::endl;




	return 0;
}