#include <iostream>
#include "printer.hpp"
#include "hdd.hpp"
#include "memory.hpp"
#include "pcb.hpp"
#include "cpu.hpp"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;


bool lowerp(pcb& x, pcb& y) //comparison function for use with sort algorithm
	{
		return x.getpriority()  < y.getpriority() ; 
	}




unsigned int extractinput(string z) //when user inputs p1 or d1, this function will extract the number portion of the input
{
	
	//cout<<z<<endl;
	unsigned int extractednum; 
	z.erase(z.begin());
	//cout<<"The new string is now "<<z<<". Converting to integer: "<<endl;
	extractednum=  stoi(z); 

	return extractednum; 
}




int main()
{


	cout<<endl<<"Welcome to the -MEM[E]- Operating System"<<endl<<endl;

	cpu mycpu; //the cpu is initialized!!

	unsigned int p;
	cout<<"SysGen ACTIVATE!"<<endl<<endl<<"Enter the number of printers."<<endl; 
	cin>>p; //#printers

	vector<int> bruh; 
	
	vector<printer> pvector; //printer vector

	for(unsigned int i=0; i<p; i++) //pushback p printers
	{
		 printer a(i+1);
		 pvector.push_back(a);  
	}

	for (unsigned int i=0; i<pvector.size(); i++)
	{
		cout<<"P"<<pvector.at(i).getprinterid()<<", ";
	}
	cout<<"Online!"<<endl<<endl;

	unsigned int q;
	cout<<"Enter the number of disks."<<endl; 
	cin>>q;

	vector<hdd> hddvector; //hard disk vector

	for(unsigned int k=0; k<q; k++) //pushback q hard disks
	{
		 hdd a(k+1);
		 hddvector.push_back(a);   
	}

	for (unsigned int i=0; i<hddvector.size(); i++)
	{
		cout<<"D"<<hddvector.at(i).gethddid()<<", ";
	}
	cout<<"Online! "<<endl<<endl; 

	cout<<"Enter the size of the memory: "<<endl; 

	unsigned int r; 
	cin>>r; 

	memory m(r); 
	//m.init();
	cout<<endl;

	std::string x;
	unsigned int psize, ppriority, psize2, ppriority2, counter; 
	
	counter=1; //counter is used to give programs ids

	vector<pcb> readyqueue; //initialize the ready queue

	

	
	
	while(x != "s")
	{
		cout<<endl<<"Enter what you want to do, enter s to exit: "<<endl; 
		cout<<"A= new program,"<<endl<<"t=terminate currently running program"<<endl<<"p followed by a number to access a printer"<<endl<<"P followed by a number to end printer use"<<endl<<"d followed by a number to access a disk"<<endl<<"D followed by a number to end disk use"<<endl;
		cout<<endl<<"S gives you a snapshot of the system. "<<endl<<"Sr will display the readyqueue. "<<endl<<"Si will display the I/O queue info."<<endl<<"Sm will display the RAM"<<endl<<endl;
		cin>>x; 

		if(x=="A") //start new program- user enters details
		{
			cout<<endl;
			cout<<"New process. Enter the size: "<<endl;
			cin>>psize; 

			cout<<"Enter priority:"<<endl; 
			cin>>ppriority; 

			cout<<endl;

			pcb prog(counter, psize, ppriority); //create a program with the user entered details 

			counter++; //increment the counter

			//load the pcb into RAM

			if(m.ramprog(prog)==1) //the newly created prog object is given a place in ram, if no space then error 
			
			{

				if (mycpu.idle()==1) //if cpu is idle, run the new pcp immediately
				{
					//cout<<"Currently running cpu size+priority= "<<mycpu.getcurrsize()<<" "<<mycpu.getcurrpriority()<<endl;
					//cout<<"FIRSTPROG!"<<endl;
					mycpu.run(prog);
					//cout<<"Currently running cpu size+priority= "<<mycpu.getcurrsize()<<" "<<mycpu.getcurrpriority()<<endl;
				}

				else //if cpu is not idle, either preempt the curr running program or wait in ready queue
				{
					if(prog.getpriority() <= mycpu.getcurrpriority()) //if the new programs priority is less than the priority of the current program in cpu, push it into ready queue
					{
						readyqueue.push_back(prog);
						sort (readyqueue.begin(), readyqueue.end(), lowerp);
						//cout<<"WAITING"<<endl;
					}
					else if(prog.getpriority() > mycpu.getcurrpriority()) //if the new priority is higher, remove the old program from cpu and preempt
					{
						//cout<<"PREEMPTION"<<endl;
						pcb tempprog(mycpu.getcurrid(), mycpu.getcurrsize(), mycpu.getcurrpriority());
						mycpu.run(prog);
						readyqueue.push_back(tempprog);
						sort (readyqueue.begin(), readyqueue.end(), lowerp);
					}
				}
				//cout<<endl;
				
			} 

			else
			{
				cout<<"Program is too big! Not enough ram."<<endl; 
			}

				
		}

		if(x=="t") //terminate prog and check ready queue for next prog in priority
		{
			if (mycpu.idle() == 0) //if the cpu is not idle
			{
				unsigned int e=mycpu.getcurrid();
				//cout<<"MAIN: PROGRAM ID TO BE DEALLOCED: "<<e<<endl;
				m.dealloc(e); //dealloc take the integer, searches through the RAM vector, and removes the pcb with that particular ID
				mycpu.terminate();
				//make call to function to remove the PCB that WAS in the CPU

				if(readyqueue.empty()==1)
				{
					cout<<"Ready queue is empty." <<endl;
				}

				else
				{
					mycpu.run(readyqueue.back());
					//cout<<"bruh"<<endl;
					readyqueue.pop_back();
				}
			}

			else
			{
				cout<<"The cpu is idle."<<endl;
			}
			
		}

	
		

		if(x[0] == 'p' && x[1] != '0'  ) //current program uses printer x
		{

			if(x.size() > 1)
			{

				if(mycpu.idle() == 1) //if the cpu is idle dont run the printer
				{
					cout<<"The CPU is idle. No program to print."<<endl; 
				}

				else //if there is a pcb using the cpu: 
				{
					pcb tempprog2(mycpu.getcurrid(), mycpu.getcurrsize(), mycpu.getcurrpriority()); //create a temp pcb that has the details of the currently running program in cpu
					unsigned int g;

					g=extractinput(x); //extract the input from x 
					g=g-1; 

					//IF THE PRINTER IS NOT IDLE THEN PUSH TO QUEUE
					if(pvector.size() > g && g>=0)  //if the input is not larger than the pqueue and g is not 0
					{
						if(pvector.at(g).idle() == 1) //if the
						{

							pvector.at(g).setprint(tempprog2); //the pcb will use the printer

							cout<<"Now printing on printer "<< g+1<<endl; 

							mycpu.terminate(); //remove the program from the cpu
							//start Check Ready Queue Routine to see if there are pcbs waiting to use the cpu
							if(readyqueue.empty()==1)
							{
								cout<<"Ready queue is empty." <<endl;
							}
							else
							{
								mycpu.run(readyqueue.back());
								//cout<<"bruh"<<endl;
								readyqueue.pop_back();
							}
							//END check ready queue routine
					
						}

						else
						{

							mycpu.terminate(); //remove the program from the cpu
							//start Check Ready Queue Routine to see if there are pcbs waiting to use the cpu
							if(readyqueue.empty()==1)
							{
								cout<<"Ready queue is empty." <<endl;
							}
							else
							{
								mycpu.run(readyqueue.back());
								//cout<<"bruh"<<endl;
								readyqueue.pop_back();
							}
							//END check ready queue routine

							pvector.at(g).push(tempprog2);
							cout<<"Prog ID "<<tempprog2.getid()<<" pushed into printer queue"<<endl;
						}

						}

					else
					{
						cout<<"That is not a valid printer"<<endl; 
						
					}

				}

			}
			else
			{
				cout<<"That is not valid input. Please input p followed by a number. "<<endl; 
			}

			
		}

		if(x[0] == 'P' && x[1] != '0' ) //currently printing program finishes and returns to ready queue
			{
				if (x.size() >1 )
				{

					unsigned int g=extractinput(x); //extract the unsigned int portion of the input
					g=g-1; 

					if(g<pvector.size())
						{

							if (pvector.at(g).idle()==0) //if the printer is not idle, terminate the printer and take the pcb back to cpu

							{

								pcb temppcb(pvector.at(g).getcurrid(), pvector.at(g).getcurrsize(), pvector.at(g).getcurrpriority() ); //temp pcb that has the details of the pcb in the printer
								pvector.at(g).pterminate(); //remove the program from the printer


									//the RUN Routine
								if (mycpu.idle()==1) //if cpu is idle, run the new pcp immediately
								{
									//cout<<"P1 Currently running cpu size+priority= "<<mycpu.getcurrsize()<<" "<<mycpu.getcurrpriority()<<endl;
									//cout<<"P1 FIRSTPROG!"<<endl;
									mycpu.run(temppcb);
									//cout<<"P1 Currently running cpu size+priority= "<<mycpu.getcurrsize()<<" "<<mycpu.getcurrpriority()<<endl;
								}
								else //if cpu is not idle, either preempt the curr running program or wait in ready queue
								{
									if(temppcb.getpriority() <= mycpu.getcurrpriority()) //if the new programs priority is less than the priority of the current program in cpu, push it into ready queue
									{
										readyqueue.push_back(temppcb);
										sort (readyqueue.begin(), readyqueue.end(), lowerp);
										//cout<<"P1 WAITING"<<endl;
									}
									else if(temppcb.getpriority() > mycpu.getcurrpriority()) //if the new priority is higher, remove the old program from cpu and preempt
									{
										//cout<<"P1 PREEMPTION"<<endl;
										pcb tempprog(mycpu.getcurrid(), mycpu.getcurrsize(), mycpu.getcurrpriority());
										mycpu.run(temppcb);
										readyqueue.push_back(tempprog);
										sort (readyqueue.begin(), readyqueue.end(), lowerp);
									}
								}
								cout<<endl;
								cout<<endl;
								//the RUN Routine ENDS 
								
								

								if(pvector.at(g).emptyqueue() == 0) //if the printers queue is not empty
									{
										pvector.at(g).printnext();

									}
								else
									{
										cout<<"The printer queue is empty. "<<endl;
									}

								}

							else
							{
								cout<<"The printer is idle, nothing to print. "<<endl; 
							}
							//check the printers printerqueue, if it is not empty, run the pcb at the lowest position
						}

					else
						{
							cout<<"This is not a valid printer"<<endl;
						}
				}
				else
				{
					cout<<"That is not valid input. Please input P followed by a number."<<endl; 
				}

			}

			

			if(x[0] == 'd' && x[1] != '0' ) //current program uses disk x
		{
			if(x.size()>1)
			{
				if(mycpu.idle() == 1) //if the cpu is idle dont write to disk
				{
					cout<<"The CPU is idle. No program to use disk."<<endl; 
				}

				else //if there is a pcb using the cpu: 
				{
					pcb tempprog2(mycpu.getcurrid(), mycpu.getcurrsize(), mycpu.getcurrpriority()); //create a temp pcb that has the details of the currently running program in cpu
					unsigned int g;

					g=extractinput(x); //extract the input from x 

					g=g-1; 
					

					//IF THE DISK IS NOT IDLE THEN PUSH TO QUEUE
					if(hddvector.size() > g && g>=0)  //if the input is not larger than the pqueue and g is not 0
					{
						if(hddvector.at(g).idle() == 1)
						{
							hddvector.at(g).setdisk(tempprog2); //the pcb will use the disk

							cout<<"Now writing to disk "<< g+1<<endl; 

							mycpu.terminate(); //remove the program from the cpu

							//start Check Ready Queue Routine to see if there are pcbs waiting to use the cpu
							if(readyqueue.empty()==1)
							{
								cout<<"Ready queue is empty." <<endl;
							}
							else
							{
								mycpu.run(readyqueue.back());
								//cout<<"bruh"<<endl;
								readyqueue.pop_back();
							}
							//END check ready queue routine
					
						}
						else
						{

							mycpu.terminate(); //remove the program from the cpu

							//start Check Ready Queue Routine to see if there are pcbs waiting to use the cpu
							if(readyqueue.empty()==1)
							{
								cout<<"Ready queue is empty." <<endl;
							}
							else
							{
								mycpu.run(readyqueue.back());
								//cout<<"bruh"<<endl;
								readyqueue.pop_back();
							}
							//END check ready queue routine

							hddvector.at(g).push(tempprog2);
							cout<<"Prog ID "<<tempprog2.getid()<<" pushed into disk queue"<<endl;
						}

						}

					else
					{
						cout<<"That is not a valid disk"<<endl; 
						
					}

				}
			}
			else
			{
				cout<<"That is not a valid input. Please input d followed by a number. "<<endl; 
			}

			
		}

		if(x[0] == 'D' && x[1] != '0' ) //currently printing program finishes and returns to ready queue
			{
				if(x.size() > 1)
				{

					unsigned int g=extractinput(x); //extract the unsigned int portion of the input
					g=g-1; 

					if(g< hddvector.size())
					{

						//cout<<"MAKE LIKA DISK: " <<endl;

						if (hddvector.at(g).idle()==0) //if the disk is not idle, terminate the printer and take the pcb back to cpu

						{

							pcb temppcb(hddvector.at(g).getcurrid(), hddvector.at(g).getcurrsize(), hddvector.at(g).getcurrpriority() ); //temp pcb that has the details of the pcb using the disk
							hddvector.at(g).dterminate(); //remove the program from the disk


								//the RUN Routine
							if (mycpu.idle()==1) //if cpu is idle, run the new pcp immediately
							{
								//cout<<"P1 Currently running cpu size+priority= "<<mycpu.getcurrsize()<<" "<<mycpu.getcurrpriority()<<endl;
								//cout<<"P1 FIRSTPROG!"<<endl;
								mycpu.run(temppcb);
								//cout<<"P1 Currently running cpu size+priority= "<<mycpu.getcurrsize()<<" "<<mycpu.getcurrpriority()<<endl;
							}
							else //if cpu is not idle, either preempt the curr running program or wait in ready queue
							{
								if(temppcb.getpriority() <= mycpu.getcurrpriority()) //if the new programs priority is less than the priority of the current program in cpu, push it into ready queue
								{
									readyqueue.push_back(temppcb);
									sort (readyqueue.begin(), readyqueue.end(), lowerp);
									//cout<<"P1 WAITING"<<endl;
								}
								else if(temppcb.getpriority() > mycpu.getcurrpriority()) //if the new priority is higher, remove the old program from cpu and preempt
								{
									//cout<<"P1 PREEMPTION"<<endl;
									pcb tempprog(mycpu.getcurrid(), mycpu.getcurrsize(), mycpu.getcurrpriority());
									mycpu.run(temppcb);
									readyqueue.push_back(tempprog);
									sort (readyqueue.begin(), readyqueue.end(), lowerp);
								}
							}
							// cout<<endl;
							// cout<<endl;
							//the RUN Routine ENDS 
							
							

							if(hddvector.at(g).emptyqueue() == 0) //if the disks queue is not empty
								{
									hddvector.at(g).disknext();

								}
							else
								{
									cout<<"The disk queue is empty. "<<endl;
								}

							}

						else
						{
							cout<<"The disk is idle, nothing to remove. "<<endl; 
						}
					}
					
					else
					{
						cout<<"This is not a valid disk."<<endl; 
					}
				}
				else
				{
					cout<<"That is not valid input. Please input D followed by a number."<<endl; 
				}



			}


		if(x == "Sr") //info about ready queue and cpu
		{
			cout<<"Ready Queue: "<<endl;
			for (unsigned int i=0; i<readyqueue.size(); i++)
				{
					//cout<<"program "<<i<<" priority: "<<readyqueue[i].getpriority()<<endl; 
					//cout<<"program "<<i<<" size: "<<readyqueue[i].getsize()<<endl;
					cout<<"[PID: "<<readyqueue[i].getid()<<" Size: "<<readyqueue[i].getsize()<< " Priority: "<<readyqueue[i].getpriority()<<"] "<<endl;;
					
				}

				cout<<endl<<"Currently running PID: "<<mycpu.getcurrid()<<" Priority: "<<mycpu.getcurrpriority()<<endl;
			
		}

		if(x == "Si") //io queue info
		{
			for(int i = 0; i<pvector.size(); i++)
			{
				pvector.at(i).displayq();
			}

			for(int i = 0; i<hddvector.size(); i++)
			{
				hddvector.at(i).displayq();
			}


			
			
		}

		if(x == "Sm") //memory related info
		{
			m.displayram();
			
		}

		
			
			
			
	}

	return 0; 
		
}