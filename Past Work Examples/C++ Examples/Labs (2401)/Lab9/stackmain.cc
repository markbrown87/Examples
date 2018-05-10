*****************************************************************
	Lab Assignment 8 - working with a stack
	It's sometimes tricky to set up the loop that reads the 
expression from the keyboard, so I am giving that to you. You have to 
fill in the rest of the main.
	John Dolan Spring 2015
			Ohio University
			Home of the Bobcats 
******************************************************************/
#include <stack> 
#include <iostream>
#include "calc_useful.h"
using namespace std; 


int main(){
    // declare your stack here
    char c;
    int onenum, twonum;
    cout<<"Please enter your expression:\n";

    c = cin.get(); // priming read for the sentinel loop.
    while(c != '\n'){
 	if(isdigit(c)){
	    cin.putback(c);
	    cin>>onenum;
	// stack operation here.
	}
	else if(isop(c)){
	// if the stack is empty here you have an error.

	// here is where you have to pop a couple of numbers,
        // apply the operator to the numbers
        // and then push the result back into the stack		    
	}
	c = cin.get(); // reading at the bottom of the sentinel loop
    }
	// this is where you get your final answer off the stack
	// it should be the only number left on the stack at this point
    if(! nums.empty()){
	cout<<"Error. Insufficient operators for operands.\n";
	return -1;
    }
    cout<<"The answer is: "<< onenum<<endl; return 0;
}
