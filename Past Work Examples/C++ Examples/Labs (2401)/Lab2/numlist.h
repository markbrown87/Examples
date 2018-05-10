//Modified by Mark Brown on 27/01/2016


#ifndef NUMLIST_H
#define NUMLIST_H
#include <iostream>
#include <cstdlib>
#include <cmath>

class NumList{
    public:
	static const size_t CAPACITY = 100;
	
	// Default constructor
	NumList();

	// Precondition: none
	// Postcondition: num is placed at the end of the list, 
	//               if there is sufficient Capacity
	void insert(int num);
	size_t size()const {return used;}

	//Precondition: istream is a stream that has already been connected to 
	//              a successfully opened file
	// Postcondition: integers from the file are loaded into the object
	void load_from_file(std::istream& ins);

	// Preconditon: ostream is connected to a successfully open file
	// Postconditon numbers in the object are written to the file
	void save_to_file(std::ostream& outs);
	void b_sort();
	int get_item(size_t index)const;
	void see_all()const;
    private:
	int data[CAPACITY];
	size_t used;
};

#endif
