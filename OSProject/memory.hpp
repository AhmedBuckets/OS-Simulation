#ifndef _memory
#define _memory
#include <vector>
#include <iostream>
#include "pcb.hpp"


using namespace std;


class memory
{
private:
   unsigned int memsize; 
   std::vector<pcb> ram; 
   vector<int> bruh;

   pcb emptyram; 


public:
	memory(unsigned int c); 
	void init();
	bool ramprog(pcb d); 
	void displayram();
	void dealloc(unsigned int e);
	pcb merge3(pcb f, pcb g, pcb h);
	pcb merge2(pcb f, pcb g);
	void reset(pcb h);
	void displayq(); 

    
};


#endif