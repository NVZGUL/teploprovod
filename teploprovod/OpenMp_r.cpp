#include<iostream>
#include <vector>
#include "Task.h"
#include <thread>
#include "Print_res.h"
#include <omp.h>  

void yavn_openMP(double time, double h, std::vector<double> T_arr)
{
	std::vector<double> T_prev = T_arr;
	double a = lambda / (ro*c);
	double tau = 0.25 * pow(h, 2) / a; /// из условий устойчивости
	T_arr[0] = T_l;
	T_arr[N - 1] = T_r;
#pragma omp parallel
	for (double j = time; j < t_final; j += tau)
	{
		T_prev = T_arr;
#pragma omp for schedule(dynamic, 1)
		for (int i = 1; i < N - 1; i++)
		{
			T_arr[i] = T_prev[i] + a*tau / pow(h, 2)*(T_prev[i + 1] - 2 * T_prev[i] + T_prev[i - 1]);
		}
	}
	print_res(T_arr);
}

void neyavn_openMP(double time, double tau, double h, std::vector<double> alfa, std::vector<double> beta, std::vector<double> T_arr)
{
	double a_i, b_i, c_i, f_i;

#pragma omp parallel
	for (double j = time; j < t_final; j++)
	{
		time += tau;
		alfa[0] = 0;
		beta[0] = T_l;
#pragma omp for schedule(dynamic, 1)
		for (int i = 1; i < T_arr.size() - 1; i++)
		{
			//	#pragma omp atomic
			a_i = lambda / pow(h, 2);
			b_i = 2 * lambda / pow(h, 2) + ro * c / tau;
			c_i = lambda / pow(h, 2);
			f_i = -ro*c*T_arr[i] / tau;
			alfa[i] = a_i / (b_i - c_i*alfa[i - 1]);
			beta[i] = (c_i*beta[i - 1] - f_i) / (b_i - c_i*alfa[i - 1]);
		}
		T_arr[N - 1] = T_r;
#pragma omp for schedule(dynamic, 1)
		for (int i = T_arr.size() - 2; i >= 0; i--)
		{
			T_arr[i] = alfa[i] * T_arr[i + 1] + beta[i];
		}
	}

	
	//	print_res(T_arr);
}