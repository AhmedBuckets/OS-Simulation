#include <iostream>
#include "printer.hpp"
#include "pcb.hpp"
#include <vector>
using namespace std;

printer::printer(int a)
{
	printerid=a;
	
}

void printer::init()
{
	cout<<"printer"<<printerid<<" online!"<<endl;
}


void printer::setprint(pcb p)
{
	pcurrprog=p; 
	//cout<<"printer set"<<endl;
}


void printer::displayprinterqueue()
{
	for (int i=0; i<printerqueue.size(); i++)
	{
		cout<<"[ID: "<<printerqueue.at(i).getid()<<"] ";
	}
	cout<<endl;
}


int printer::getcurrpriority()
{
	return pcurrprog.getpriority();
}

int printer::getcurrsize()
{
	return pcurrprog.getsize();
}

int printer::getcurrid()
{
	return pcurrprog.getid();
}


void printer::pterminate()
{
	pcurrprog=emptyprog;
}

bool printer::idle()
{
	if (getcurrid() ==0)
	{
		return 1; 
	}
	else
	{
		return 0; 
	}
}

void printer::push(pcb k)
{
	printerqueue.push_back(k); 
}

bool printer::emptyqueue()
{
	if(printerqueue.size() == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void printer::printnext()
{
	pcurrprog = printerqueue.at(0); 

	std::vector<pcb>::iterator it;
	it= printerqueue.begin();
	printerqueue.erase(it);

}

int printer::getprinterid()
{
	return printerid; 
}

void printer::displayq()
{
	if(pcurrprog.getid() == 0)
	{
		cout<<"Printer "<<printerid<<" is idle."<<endl;
	}
	else
	{
		cout<<"Printer "<<printerid<<" is currently printing program id: "<<getcurrid()<<endl; 

	}


	if(printerqueue.size() == 0)
	{
		cout<<"Printer "<<printerid<<"'s queue is empty."<<endl;
	}
	else
	{
		cout<<"The queue for printer "<<printerid<<" "<<endl;
		for (int i=0; i<printerqueue.size(); i++)
		{
			cout<<printerqueue.at(i).getid()<<" "; 
		}
	}
	
	cout<<endl<<endl;
}
