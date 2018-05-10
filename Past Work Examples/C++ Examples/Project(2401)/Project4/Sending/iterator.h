/*
*Mark Brown
*23/03/2016
*This file is the declaration file for the external iterator used in the
*doubly linked lists.
*
*/

#ifndef ITERATOR_H
#define ITERATOR_H


template <class T>//dlist prototype
class dlist;

template <class T>//external iterator
class node_iterator
: public std::iterator<std::forward_iterator_tag, const T>
{
	public:
		friend class dlist<T>;//allowing the friendship between dlist and node_iterator
		//constructor
		node_iterator(Dnode<T>* init = NULL){current = init;}
		//returns the data
		T& operator *() const {return current->data();}
		//functions used to advance and manipulate the dlist
		node_iterator& operator ++(){current = current->next(); return *this;}//pre ++
		node_iterator operator ++(int){node_iterator original(current); current=current->next(); return original;}//post ++
		node_iterator& operator --(){current = current->previous(); return *this;}//pre --
		node_iterator operator --(int){node_iterator original(current); current=current->previous(); return original;}// post --
		bool operator ==(const node_iterator other) const{return current == other.current;}
		bool operator !=(const node_iterator other){return current != other.current;}
	private:
		Dnode<T> *current;
};
#endif
