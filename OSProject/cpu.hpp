#ifndef _cpu
#define _cpu

#include "pcb.hpp"

class cpu
{
	private: 
		pcb emptyprog; 
		pcb currprog;


	public:
		cpu();

		void run(pcb a);
		void terminate();
		bool idle();
		int getcurrid();
		int getcurrpriority(); 
		int getcurrsize();

};

#endif