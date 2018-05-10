/*
*Mark Brown
*23/03/2016
*This file houses the declartion code for the dnode.template file which is used
*for the dlist file.
*
*/

#ifndef DNODE_H
#define DNODE_H


template <class T>
class Dnode{
	public:
		//typedef
		typedef T value_type;
		//constructor
		Dnode(const T& d = T(), Dnode *init=NULL){nextfield = init; previousfield = init; datafield =d;}
		//modification member functions
		T& data(){return datafield;}
		Dnode *next(){return nextfield;}
		Dnode *previous(){return previousfield;}
		void set_next(Dnode *link){nextfield = link;}
		void set_previous(Dnode *link){previousfield = link;}
		void set_data(const T& data) {datafield = data;}
		//const member functions
		const T& data() const {return datafield;}
		const Dnode* next() const {return nextfield;}
		const Dnode* previous() const {return previousfield;}
	private:
		T datafield;
		Dnode *nextfield;
		Dnode *previousfield;
};
#endif
