/*********************************************************************
	This is a class to introduce you to the syntax of working with 
	template classes. Notice that the type being stored is completely
	anonymous.
	Your assignment is to implent the eight functions listed in this 
	header in a tarray.template file.
		Lab 7		Fall 2014
	John Dolan			Ohio University 
********************************************************************/

#include<iostream>

template<class T>
class Tarray{
    public:
	// Constructor makes an object with a dynamic array of size 5
	Tarray(); 

    	// This function puts the item into the next available spot in the 
	//array.
	// If the array is full, resize is called.
	void add(T item);

	// iterator functions

	// places the current_index at the beginning of the array
	void start();

	// returns true if the current index is less than used
	bool is_item()const;

	// moves current index to the next array location
	void advance();

   	// returns the array item being referenced by cuurent index
	T current()const;

	// removes the item at the current index spot
	void remove_current();
    private:
	void resize();
	T *data; // pointer to the dynamic array
	std::size_t capacity;
	std::size_t used;
	std::size_t current_index;
};

// This is how we hook this to the implementation file for templates:
#include "tarray.template"
