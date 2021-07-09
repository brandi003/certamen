#include <boost/mpi.hpp>
#include <iostream>
#include <random>
#include <thread> 
#include <chrono>
#include <cmath>
#include <cstring>


namespace mpi = boost::mpi;

void createNumbers(const int& count, double* out, double step)
{
	std::random_device rd;  //seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> distrib(0, 10000);

	for (size_t i = 1; i <= count; i++){
		double x;
		out[i] = (i-0.5)*step;
		
	}
}

int main(int argc, char *argv[])
{
	mpi::environment env{argc, argv};
	mpi::communicator world;
	
	int rankID     = world.rank();
	int procInComm = world.size();
	
	double step;
	uint32_t num_steps = 100000;
	
	
	double piValue, sum = 0.0;
	step = 1.0/(double)num_steps;
	uint32_t inicio, fin;
	inicio = 1;
	fin    = num_steps;



	double* numbersToShare;
	numbersToShare = new double[num_steps];
	createNumbers(num_steps, numbersToShare,step);
	int ntotalByProc = num_steps/procInComm;
	double* numbersToSum;
	numbersToSum = new double[ntotalByProc];


	mpi::scatter(world,numbersToShare,numbersToSum,ntotalByProc,0);

	double sumaParcial = 0.0;
	for(size_t idx = 0; idx < ntotalByProc; idx++){
		sumaParcial += 4.0/(1.0+numbersToSum[idx]*numbersToSum[idx]);
	}
	std::cout << sumaParcial << std::endl;
	/*
	for (size_t i = 1; i <= ntotalByProc; i++){
		double x;
		
		x = (i-0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	}
	resultado = step * sum;
	*/
	
	//std::cout << "pi=" << piValue << std::endl;
	return(EXIT_SUCCESS);
}

