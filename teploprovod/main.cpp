#include<iostream>
#include <vector>
#include <ctime>

//������� ������
//����������� ������ 2
//	 ����� ���� ������� ������ ���������� ���������� ������� tau < ro * c * h^2 / 2 * lambda
const double t1 = 500; 
const int N = 100;			//����������� ��������� �� ������� �������� �������� 
const double t_final = 600;	//����� ������������ ��������
const double L = 0.1;		//����� �������
const double lambda = 46;	//��������� ������ � ��������� ����������������
const double ro = 7800;		//��������� � �������� ����������������
const double c = 460;		//������������ ��������� � ��������� ����������������
const double T_0 = 20;		//��������� �����������
const double T_l = 300;		//����������� �� ������ �=0
const double T_r = 100;		//����������� �� ������� �=L


void print_res(std::vector<double> T_arr)
{
	using Iter = std::vector<double>::const_iterator;
	for (Iter it = T_arr.begin(); it != T_arr.end(); ++it) {
		std::cout << *it << std::endl;
	}
}

void yavn(double time, double h, std::vector<double> T_arr)
{
	std::vector<double> T_prev = T_arr;
	double a = lambda / (ro*c);
	double tau = 0.25 * pow(h, 2) / a; /// �� ������� ������������
	T_arr[0] = T_l;
	T_arr[N - 1] = T_r;
//#pragma omp parallel for private(i)
		for (double j = time; j < t_final; j += tau)
		{
			T_prev = T_arr;
			for (int i = 1; i < N - 1; i++)
			{
				T_arr[i] = T_prev[i] + a*tau / pow(h, 2)*(T_prev[i + 1] - 2 * T_prev[i] + T_prev[i - 1]);
			}
		}
	print_res(T_arr);
}

void neyavn(double time, double tau, double h, std::vector<double> alfa, std::vector<double> beta, std::vector<double> T_arr)
{
	double a_i, b_i, c_i, f_i;
//#pragma omp parallel for private(i)
	for (auto j = time; j < t_final; j++)
	{
		time += tau;
		alfa[0] = 0;
		beta[0] = T_l;
		for (int i = 1; i < T_arr.size()-1; i++)
		{
//#pragma omp atomic
			a_i = lambda / pow(h, 2);
			b_i = 2 * lambda / pow(h, 2) + ro * c / tau;
			c_i = lambda / pow(h, 2);
			f_i = -ro*c*T_arr[i] / tau;
			alfa[i] = a_i / (b_i - c_i*alfa[i - 1]);
			beta[i] = (c_i*beta[i - 1] - f_i) / (b_i - c_i*alfa[i - 1]);
		}
		T_arr[N - 1] = T_r;
		for (int i = T_arr.size() - 2; i >= 0; i--)
		{
			T_arr[i] = alfa[i] * T_arr[i + 1] + beta[i];
		}
	}
	print_res(T_arr);
}


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
		T_arr.push_back(T_0);
		alfa.push_back(0);
		beta.push_back(0);
	}

	//�������
	clock_t start = clock();
	neyavn(time,tau,h,alfa,beta,T_arr);
	//yavn(time, h, T_arr);
	clock_t end = clock();
	std::cout << "time is: " << (float)(end - start)/ CLOCKS_PER_SEC << std::endl;




	return 0;
}