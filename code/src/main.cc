#include <boost/mpi.hpp>
#include <iostream>
#include <random>
#include <thread> 
#include <chrono>
#include <cmath>
#include <cstring>


namespace mpi = boost::mpi;

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
	int ntotalByProc = num_steps/procInComm;
	uint32_t inicio, fin;
	inicio = 1;
	fin    = num_steps;
	float* resultado;

	mpi::scatter(world,resultado,num_steps,0);
	std::cout << "num_steps-" << num_steps << "\t";
	std::cout << "rankID-" << rankID << "\t";
	std::cout << "resultado-" << resultado << "\t";
	std::cout << "ntotalByProc-" << ntotalByProc << std::endl;
	/*
	for (size_t i = 1; i <= ntotalByProc; i++){
		double x;
		
		x = (i-0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	}
	resultado = step * sum;
	*/
	
	std::cout << "pi=" << piValue << std::endl;
	return(EXIT_SUCCESS);
}

