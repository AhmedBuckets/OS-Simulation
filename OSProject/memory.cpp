#include <iostream>
#include "memory.hpp"
#include "pcb.hpp"
#include <vector>

using namespace std;

memory::memory(unsigned int c)
{
	memsize=c;
	emptyram.setsize(c);
	ram.push_back(emptyram);

	// cout<<emptyram.getsize()<<endl;
	// cout<<emptyram.getpriority()<<endl;
	// cout<<emptyram.getid()<<endl;
	cout<<"The ram is of size: "<<emptyram.getsize()<<endl;

}

void memory::init()
{
	cout<<"memory size is: " <<memsize<<endl; 
}


void memory::reset(pcb h)
{
	cout<<"RESET"<<endl;
	h.setsize(0);
	h.setpriority(0);
	h.setid(0);
	h.setempty();
	cout<< "RESETTED! "<<endl;
}


bool memory::ramprog(pcb d)
{
	unsigned int size, newemptysize;
	size=d.getsize(); 

	for(unsigned int i=0; i<ram.size(); i++) //iterate through the ram vector
	{
		std::vector<pcb>::iterator it;  //iterator created
		it=ram.begin();    				//position it at the beginning of the vector

		if (ram[i].getempty()==1) //find an empty space
		{
			if(ram[i].getsize() >= size) //check if the empty space is big enough for the new pcb
			{
				//cout<<"Space found"<<endl;
				it=it+i; //it points to the position if the empty pcb
				newemptysize=ram[i].getsize()-size; //newempty size is the size of the previiously empty pcb minus the size of the newly introduced pcb
				ram[i].setsize(newemptysize); //reduce the size of the empty space
				ram.insert(it, d); //insert the new pcb into the position of the empty space-empty space is now at ram[i+1]
				if(newemptysize == 0)
				{
					it=ram.begin();
					it=it+i+1;
					//cout<<"Deleting empty pcb"<<endl;
					ram.erase(it);
					//cout<<"Deleted"<<endl;
				}
				
				return 1; //successful
			}
		}

	}	
}

void memory::displayram()
{
	cout<<"Ram: "<<endl;
	for(unsigned int i=0; i<ram.size(); i++)
	{
		if(ram.at(i).getempty()==0)
		{
			cout<<"[ID: "<<ram.at(i).getid()<<" P: "<<ram.at(i).getpriority()<<" "<<" Size: "<<ram.at(i).getsize()<<"]   " ;
		}

		else
		{
			cout<<"[EMPTY: "<<ram.at(i).getsize()<<"]   ";
		}

	}
	cout<<endl<<endl;
}

pcb memory::merge3(pcb f, pcb g, pcb h)
{
	//add up the sizes of the three pcb's
	//create a new pcb with that big size
	//return that pcb
	unsigned int mergedsize;
	pcb mergedpcb; 
	mergedsize= (f.getsize()+ g.getsize() + h.getsize());
	mergedpcb.setsize(mergedsize);
	//cout<<"Merged3: the new empty pcb is of size: "<<mergedpcb.getsize()<<endl;
	return mergedpcb;

}

pcb memory::merge2(pcb f, pcb g)
{
	unsigned int mergedsize;
	pcb mergedpcb; 
	mergedsize= (f.getsize()+ g.getsize());
	mergedpcb.setsize(mergedsize);
	//cout<<"Merged2: the new empty pcb is of size: "<<mergedpcb.getsize()<<endl;
	return mergedpcb;
}

void memory::dealloc(unsigned int e)
{
	for(unsigned int i=0; i<ram.size(); i++)
	{
		if(ram[i].getid()==e) //find the pcb with the matching id
		{
			//if program .empty()=0 remove it from ram by deleting object from the ram vector
			//before that, check if the programs to the left or the right are empty, if so, run merge 2
			//if both are empty, run merge 3 
			if (ram[i].getempty() == 0) //check if that pcb is empty or not- of not, delete
			{
				std::vector<pcb>::iterator it;
				std::vector<pcb>::iterator it2;
				it=ram.begin();

				//cout<<"ID PRIORITY SIZE TO BE DELETED: "<< ram[i].getid()<<" "<< ram[i].getpriority()<<" "<<ram[i].getsize()<<endl;
				//cout<<"VECTOR POSITION i TO BE DELETED: "<<i<<endl;
				unsigned int pos, posplus1, posplus2, posminus1;
				pos=i;
				posplus1=(i+1);
				posplus2=(i+2);
				posminus1=(i-1);


				if(i == 0 ) //if the pcb to be deleted is the very first in the vector
				{
					//cout<<"DA FURST!"<<endl;
					//cout<<"pcb at the right is empty? "<<ram.at(posplus1).getempty()<<endl;
					//ONLY check the pcb to the right 

					if( ram.at(posplus1).getempty() == 1 ) //if pcb to the right is empty
						{
							//cout<<"Merging positions"<<i<<"and "<<posplus1<<endl;
							//cout<<"MERGE 2 RIGHT!"<<endl;
							it=it+i; //move the iterator to the pcb to be deleted (it should be leftmost)
							pcb temppcb;
							temppcb = merge2(ram[i], ram[posplus1]); //merge the two pcb- the pcb to be deleted and the one that is empty
							ram.insert(it, temppcb); //insert the newly formed pcb in the place of the leftmost pcb
							//cout<<"inserted 2 R!"<<endl<<endl;

							displayram();

							it=ram.begin();
							it= it + posplus1;
							it2= ram.begin();
							it2= it2+posplus2+1;
							//cout<<"deleto from "<<it->getsize()<<" to "<<it2->getsize()<<endl;

							ram.erase(it, it2); //delete the two unneeded pcb's
							
							break;
						}

					else //if pcb to the right is not empty
					{
							pcb temppcb2;                   //create a new empty pcb
							temppcb2.setsize(ram[i].getsize()); //make the size of the new empty pcb the same as the size of the deleted pcb
							it=ram.begin();                 //iterator begins at the start of the vector
							it=it+pos;						//iterator moves to the position of the pcb to be deleted
							ram.insert(it, temppcb2);		//insert the empty pcb into the position of the pcb tobe deleted

							it=ram.begin();                 //iterator goes back to the begining
							it=it+posplus1;					//iterator goes to the POS pcb +1, which is were the pcb to be original deleted is now
							ram.erase(it);					//erase that pcb
							break;


					}
					
				}
				//cout<<"Oh naaaaah"<<endl;
				//cout<<"SIZE OF RAM "<< ram.size()<<endl; 

				if (i == ram.size()-1) //if the pcb to be deleted is the very last pcb
				{
					//cout<<"Oh naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaah"<<endl;
					//ONLY check the pcb to the left
					if( ram.at(posminus1).getempty() == 1 ) //if pcb to left is empty 
						{
							//cout<<"MERGE 2 LEFT!"<<endl;
							//cout<<"Merging positions "<<i<<" and "<<posminus1<<endl;
							//cout<<"Position "<<posminus1<<" has an empty size of " <<ram[posminus1].getsize()<<endl;
							/*cout<<"The pcb to be deleted has size: "<< ram[(i)].getsize()<<endl;
							cout<<"The pcb to the left has size: "<< ram[posminus1].getsize()<<endl;
							cout<<"The pcb to the right has size: "<< ram[posplus1].getsize()<<endl;
							*/
							it=it+posminus1;
							ram.insert(it, merge2(ram[i-1], ram[i]));
							//cout<<"inserted2 L !"<<endl;

							it=ram.begin();
							it2= ram.begin();
							it2= it2+posplus1+1;
							it= it + pos;
							ram.erase(it, it2); //delete the two unneeded pcb's
							break; 
						}

					else
					{
							//cout<<"oh yess"<<endl;

							pcb temppcb2;                   //create a new empty pcb
							temppcb2.setsize(ram[i].getsize()); //make the size of the new empty pcb the same as the size of the deleted pcb
							it=ram.begin();                 //iterator begins at the start of the vector
							it=it+pos;						//iterator moves to the position of the pcb to be deleted
							ram.insert(it, temppcb2);		//insert the empty pcb into the position of the pcb tobe deleted
							
							it=ram.begin();                 //iterator goes back to the begining
							it=it+posplus1;					//iterator goes to the POS pcb +1, which is were the pcb to be original deleted is now
							ram.erase(it);					//erase that pcb
							break;

					}			

				}

				else //if the pcb to be deleted is anywhere else within the vector, NOT on the edges
				{
					//cout<<"OH NAH 3"<<endl;

							if( ram.at(posminus1).getempty() == 1   &&   ram.at(posplus1).getempty() == 1)
							{
								it=it+(posminus1);
								//cout<<"Merging positions"<<i<<"and "<<posminus1<<"and "<<posplus1<<endl;
								ram.insert(it, merge3(ram[posminus1], ram[pos], ram[posplus1] )); 
								//cout<<"inserted3!"<<endl;

								it=ram.begin();
								it2= ram.begin();
								it2= it2+posplus2+1;
								it= it + pos;
								ram.erase(it, it2); //delete the three unneeded pcb's
								break;
							}


							if( ram.at(posminus1).getempty() == 1 ) //if pcb to left is empty 
							{
								//cout<<"MERGE 2 LEFT!"<<endl;
								//cout<<"Merging positions "<<i<<" and "<<posminus1<<endl;
								//cout<<"Position "<<posminus1<<" has an empty size of " <<ram[posminus1].getsize()<<endl;
								/*cout<<"The pcb to be deleted has size: "<< ram[(i)].getsize()<<endl;
								cout<<"The pcb to the left has size: "<< ram[posminus1].getsize()<<endl;
								cout<<"The pcb to the right has size: "<< ram[posplus1].getsize()<<endl;
								*/
								it=it+posminus1;
								ram.insert(it, merge2(ram[i-1], ram[i]));
								//cout<<"inserted2 L !"<<endl;

								it=ram.begin();
								it2= ram.begin();
								it2= it2+posplus1+1;
								it= it + pos;
								ram.erase(it, it2); //delete the two unneeded pcb's
								break; 
							}

							if( ram.at(posplus1).getempty() == 1 ) //if pcb to the right is empty
							{
								// cout<<"Merging positions"<<i<<"and "<<posminus1<<endl;
								// cout<<"MERGE 2 RIGHT!"<<endl;
								it=it+i; //move the iterator to the pcb to be deleted (it should be leftmost)
								pcb temppcb;
								temppcb = merge2(ram[i], ram[posplus1]); //merge the two pcb- the pcb to be deleted and the one that is empty
								ram.insert(it, temppcb); //insert the newly formed pcb in the place of the leftmost pcb
								//cout<<"inserted 2 R!"<<endl;


								it=ram.begin();
								it= it + posplus1;
								it2= ram.begin();
								it2= it2+posplus2+1;
								
								ram.erase(it, it2); //delete the two unneeded pcb's
								break;
							}

							else //if neither the left or right are empty
							{
								pcb temppcb2;                   //create a new empty pcb
								temppcb2.setsize(ram[i].getsize()); //make the size of the new empty pcb the same as the size of the deleted pcb
								it=ram.begin();                 //iterator begins at the start of the vector
								it=it+pos;						//iterator moves to the position of the pcb to be deleted
								ram.insert(it, temppcb2);		//insert the empty pcb into the position of the pcb tobe deleted

								it=ram.begin();                 //iterator goes back to the begining
								it=it+posplus1;					//iterator goes to the POS pcb +1, which is were the pcb to be original deleted is now
								ram.erase(it);					//erase that pcb
								break;
							}

				}

				
				//cout<<"DEALLOC FINISH"<<endl; 


			}

			else
			{
				cout<<"Error, not empty. "<<endl; 
			}
			
		}
		
	}
	
}

