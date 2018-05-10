#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstddef>
#include <vector>
#include <string>
#include "sort.h"

using namespace std;


void usage() {
  cout << "Usage: project5 [option] **< [input filename] > [output filename]"    << endl;
  cout << " ** : Optional BUT must have numbers following project5 [option]"     << endl;
  cout << endl;
  cout << "  Options: " << endl;
  cout << "    -s  performs shell sort on input array then displays results"     << endl;
  cout << "    -i  performs insertion sort on input array then displays results" << endl;
  cout << "    -l  performs quick sort on input array, using the last element"   << endl;
  cout << "          as the pivot, then displays result"                         << endl;
  cout << "    -m  performs quick sort on input array, using the median of"      << endl;
  cout << "          the first, middle and last elements as the pivot, then"     << endl; 
  cout << "          displays results"                                           << endl;

  exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
	
	sortBag vars;

	if(argc < 2)
		usage();
	else{
		if(string(argv[1]) == "-s")
			vars.shellSort();
		else if(string(argv[1]) == "-l")
			vars.quickSort_l();
		else if(string(argv[1]) == "-m")
			vars.quickSort_m();
		else if(string(argv[1]) == "-i")
			vars.insertionSort();
		else
			cout<<"not working; error -> incorrect selection for sort type" << endl;
	}

	vars.print();
	

	//usage(); //remember to only call this if there are no parameters added
  
  //read input from the command line
  
  //if else statement to decide which one to run
  
  //activate the sort choosen
  
  //spit the output into another file for reading later
  
  
  
  
  //note: argc == 1 then run standard operations as per usual BUT is argc == 2 run operation based on argv[1]

  return EXIT_SUCCESS;
}



