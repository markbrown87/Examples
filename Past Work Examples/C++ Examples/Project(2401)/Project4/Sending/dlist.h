/*
*Mark Brown
*23/03/2016
*This file is designed to connect all other files (dnode.h and iterator.h) into one file to produce
*a file designed to hold a doubly linked list.
*
*/



#ifndef DLIST_H
#define DLIST_H
#include <cstdlib>
#include <iterator>
#include "dnode.h"
#include "iterator.h"


//class to manipulate a doubly linked list
template <class T>
class dlist{
	public:
		//constructor and the big 3
		dlist();
		~dlist();
		dlist(const dlist& other);
		dlist operator =(const dlist& other);
		//functions for manipulating the list
		void front_insert(T item);
		void rear_insert(T item);
		void front_remove();
		void rear_remove();
		void show();//used for testing
		void reverse_show();//used for testing
		//iterator manipulations
		typedef node_iterator<T> iterator;
		iterator begin() {return iterator(head);}
		iterator end() {return iterator();}
		iterator r_begin(){return iterator(tail);}
		iterator r_end(){return iterator();}
		size_t size();
		void remove(iterator it);
		void insert_before(iterator it, T item);
		void insert_after(iterator it, T item);		
	private:
		Dnode<T> *head;
		Dnode<T> *tail;
};

#include "dnode.template"
#endif
