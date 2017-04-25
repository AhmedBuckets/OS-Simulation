#include <iostream>
#include "hdd.hpp"
#include "pcb.hpp"
#include <vector>
using namespace std;

hdd::hdd(int b)
{
	hddid=b;
	
}




void hdd::setdisk(pcb p)
{
	dcurrprog=p; 
	//cout<<"hdd set"<<endl;
}


void hdd::displaydiskqueue()
{
	for (int i=0; i<hddqueue.size(); i++)
	{
		cout<<"[ID: "<<hddqueue.at(i).getid()<<"] ";
	}
	cout<<endl;
}


int hdd::getcurrpriority()
{
	return dcurrprog.getpriority();
}

int hdd::getcurrsize()
{
	return dcurrprog.getsize();
}

int hdd::getcurrid()
{
	return dcurrprog.getid();
}


void hdd::dterminate()
{
	dcurrprog=emptyprog;
}

bool hdd::idle()
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

void hdd::push(pcb k)
{
	hddqueue.push_back(k); 
}

bool hdd::emptyqueue()
{
	if(hddqueue.size() == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void hdd::disknext()
{
	dcurrprog = hddqueue.at(0); 

	std::vector<pcb>::iterator it;
	it= hddqueue.begin();
	hddqueue.erase(it);

}

int hdd::gethddid()
{
	return hddid; 
}

void hdd::displayq()
{
	if(dcurrprog.getid() == 0)
	{
		cout<<"Disk "<<hddid<<" is idle."<<endl;
	}
	else
	{
		cout<<"Disk "<<hddid<<" is currently writing program id: "<<getcurrid()<<endl; 

	}


	if(hddqueue.size() == 0)
	{
		cout<<"Disk "<<hddid<<"'s queue is empty."<<endl;
	}
	else
	{
		cout<<"The queue for disk "<<hddid<<" "<<endl;
		for (int i=0; i<hddqueue.size(); i++)
		{
			cout<<hddqueue.at(i).getid()<<" "; 
		}
	}
	
	cout<<endl<<endl;
}
