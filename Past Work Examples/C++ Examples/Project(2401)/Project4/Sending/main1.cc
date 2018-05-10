/********************************************************************
   This main is to be used as a testing platform as you develop your
   dlist class and the associated dnode and dnode iterator classes for 
   project 4.
   After you have developed each function you should uncomment the code 
   that calls that function, recompile everything and run the test. If it
   crashes, fix that function before moving on.
       John Dolan				Spring 2014
***********************************************************************/
#include<iostream>
#include "dlist.h"

using namespace std;

int main(){
// default constructor for the list
   dlist<int> lis1, lis2;
   int tmp;
// testing rear_insert and show

   for(int i = 0; i<10; ++i)
	lis1.rear_insert(i);
   lis1.show();
   cout<<endl<<endl;

// testing front_insert and show

   for(int i = 100; i <110; ++i)
	lis2.front_insert(i);    
   lis2.show();
   cout<<endl<<endl;

// testing the front and rear removes
/*
   lis1.front_remove();
   lis1.rear_remove();
   lis1.show();
   cout<<endl<<endl;
*/
// testing if the list can be traversed in both directions
/*
   lis1.reverse_show();
   cout<<endl<<endl;
*/
// declaring an iterator and using it to traverse list frontwards
/*
   dlist<int>::iterator it1;
   for(it1=lis1.begin(); it1 != lis1.end(); ++it1)
	cout<<*it1<<endl;
   cout<<endl<<endl;
*/
// using iterator to traverse list backwards
/*
   for(it1 = lis1.r_begin(); it1 != lis1.r_end(); --it1)
	cout<<*it1<<endl;
   cout<<endl<<endl;
*/
// moving the iterator to the third element and putting 89 before that
/*
   it1 = lis1.begin();
   for(int i = 0; i<3; ++it1,++i)
	;
   tmp =89;
   lis1.insert_before(it1, tmp);
   for(it1=lis1.begin(); it1 != lis1.end(); ++it1)
        cout<<*it1<<endl;
   cout<<endl<<endl;
   for(it1 = lis1.r_begin(); it1 != lis1.r_end(); --it1)
        cout<<*it1<<endl;
   cout<<endl<<endl;
*/
// traversing the second list from the rear and putting 256 in middle
/*
   tmp = 256;
   it1=lis2.r_begin();
   for(int i = 0; i<lis2.size()/2; --it1,++i)
       ;
   lis2.insert_after(it1, tmp);
   for(it1=lis2.begin(); it1 != lis2.end(); ++it1)
        cout<<*it1<<endl;
   cout<<endl<<endl;
   for(it1 = lis2.r_begin(); it1 != lis2.r_end(); --it1)
        cout<<*it1<<endl;
   cout<<endl<<endl;
/*
// testing copy constructor and assignment operator
/*
{
   dlist<int> copy(lis1);
   lis1 = lis2;
   for(it1=lis1.begin(); it1 != lis1.end(); ++it1)
        cout<<*it1<<endl;
   cout<<endl<<endl;
   for(it1 = lis1.r_begin(); it1 != lis1.r_end(); --it1)
        cout<<*it1<<endl;
   cout<<endl<<endl;
   for(it1=copy.begin(); it1 != copy.end(); ++it1)
        cout<<*it1<<endl;
   cout<<endl<<endl;
   for(it1 = copy.r_begin(); it1 != copy.r_end(); --it1)
        cout<<*it1<<endl;
   cout<<endl<<endl;
} // copy has been destroyed
*/
// finding out if the list still works after the copy is destroyed
/*
   for(it1=lis1.begin(); it1 != lis1.end(); ++it1)
        cout<<*it1<<endl;
   cout<<endl<<endl;
   for(it1 = lis1.r_begin(); it1 != lis1.r_end(); --it1)
        cout<<*it1<<endl;
   cout<<endl<<endl;
*/

return 0;
}

  
