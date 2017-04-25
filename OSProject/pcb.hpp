#ifndef _pcb
#define _pcb
#include <iostream>

class pcb
{
private:
	unsigned int id; 
    unsigned int size;
    unsigned int priority; 
    bool empty; //1 if empty portion of RAM, 0 if program to be run
    unsigned int position; //where the process starts in RAM 

public:
	unsigned int getid() ;
	unsigned int getsize();
	unsigned int getpriority();
	bool getempty();
	void setsize(unsigned int c);
	void setempty();
	void setpriority(unsigned int d);
	void setid(unsigned int e);
	
	pcb();
	pcb(unsigned int a, unsigned int b, unsigned int c); 
	
    
};


#endif