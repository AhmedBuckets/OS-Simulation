#include <iostream>
#include "pcb.hpp"
using namespace std;

pcb::pcb()
{
	id=0;
	size=0;
	priority=0;
	empty=1; //starts out as empty
}

pcb::pcb(unsigned int a, unsigned int b, unsigned int c)
{
    id=a;
    size=b; 
    priority=c;
    empty=0; 
}



unsigned int pcb::getid()
{
	return id;
}

unsigned int pcb::getsize()
{
	return size;
}

unsigned int pcb::getpriority() 
{
	return priority;
}

void pcb::setsize(unsigned int c)
{
	size=c; 
}

bool pcb::getempty()
{
	return empty; 
}

void pcb::setempty()
{
	empty=1; 
}
	
void pcb::setpriority(unsigned int d)
{
	priority=d; 
}
	
void pcb::setid(unsigned int e)
{
	id=e;				
}

