#include <iostream>
#include "cpu.hpp"
#include "pcb.hpp"
using namespace std;

cpu::cpu()
{
	//cout<<"CPU Initialized!"<<endl<<endl;
	currprog=emptyprog;

	//cout<<currprog.getpriority()<<currprog.getsize()<<endl; 
}

void cpu::run(pcb a)
{
	currprog = a;
	//cout<<"Currently running program has priority of: "<<currprog.getpriority()<<endl;
}


void cpu::terminate()
{
	cout<<"Terminating program id: "<<currprog.getid()<<endl;
	currprog=emptyprog; 
	//cout<<"done terminating"<<endl;

}

bool cpu::idle()
{
	if(getcurrid() == 0)
	{
		return 1; 
	}
	else 
	{
		return 0;
	}
}

int cpu::getcurrpriority()
{
	return currprog.getpriority();
}

int cpu::getcurrsize()
{
	return currprog.getsize();
}

int cpu::getcurrid()
{
	return currprog.getid();
}
		




        

