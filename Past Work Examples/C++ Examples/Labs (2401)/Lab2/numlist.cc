//*******************************************
//    Implementation file for the Numlist class, which 
//    allows programmers to store a list of numbers that they
//    choose to have sorted if they like.
//	January 2013		John Dolan
//	Ohio University		EECS
//**********************************************/

//Modified by Mark Brown on 27/01/2016

#include "numlist.h"
using namespace std;

// Constructor
NumList::NumList(){
	used = 0;
}

void NumList::insert(int num){
	used++;
	if(used <CAPACITY){
		data[used] = num;
	}
	else{
		cout<<"Error. List capacity has been reached.\n";
	}
}

void NumList::load_from_file(istream& ins){
	int num;

	ins >> num;
	while(!ins.eof())
	{
		insert(num);
		ins >> num;
	}
}


void NumList::save_to_file(ostream& outs){
	for(size_t i = 0; i < used; i++)	
		outs << data[i] << endl;
	
}

void NumList::see_all()const{
	if(used == 0)
	    cout<<"Empty list.\n";
	else
	    for(size_t i = 0; i<used; ++i)
		cout<<data[i]<<endl;
}

int NumList::get_item(size_t index)const{
	if(index < used)
		return data[index];
	else
		return -1;
}
	
void NumList::b_sort(){
    bool done = false;
    size_t j;
    int tmp;
    while(!done){
		done = true;
		for(j=used-1;j>0; --j){
			if(data[j] < data[j-1]){
				done = false;
				tmp = data[j];
				data[j] = data[j-1];
				data[j-1] = tmp;
			}
		}
    }
}
