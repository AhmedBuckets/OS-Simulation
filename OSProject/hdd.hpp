#ifndef _hdd
#define _hdd
#include "pcb.hpp"
#include <vector>
#include <iostream>

class hdd
{
private:
    int hddid; 
    pcb dcurrprog; //the program currently using the disk
	pcb emptyprog; 
    std::vector<pcb> hddqueue; //the queue of pcbs waiting to use this disk

public:
    hdd(int b);
    void init(); 
    void setdisk(pcb p);
    void displaydiskqueue();
    int getcurrid();
    int getcurrpriority(); 
	int getcurrsize();
    void dterminate(); 
    bool idle(); 
    void push(pcb k);
    bool emptyqueue();
    void disknext(); 
    int gethddid();
    void displayq(); 
};


#endif