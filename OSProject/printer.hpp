#ifndef _printer
#define _printer

#include <iostream>
#include "pcb.hpp"
#include <vector>

class printer
{
private:
	int printerid; 
	pcb pcurrprog; //the program currently using the printer 
	pcb emptyprog; 
    std::vector<pcb> printerqueue; //the queue of pcbs waiting to use this printer


public:
    printer(int a);
    void init(); 
    void setprint(pcb p);
    void displayprinterqueue();
    int getcurrid();
    int getcurrpriority(); 
	int getcurrsize();
    void pterminate(); 
    bool idle(); 
    void push(pcb k);
    bool emptyqueue();
    void printnext(); 
    int getprinterid();
    void displayq();
    
    
    
};


#endif