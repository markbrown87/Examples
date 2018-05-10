/************************************************
   This is the header file for a class called Friend.
   It holds the information about a single Facebook
   friend, just their name and birthday. It uses a class
   called Date for the storage of the birthday. The member
   functions are just accessors and input/output functions.
       John Dolan	Spring 2014	Ohio University ***********************************************************/
#include<iostream> 
#include<string> 
#include<cstdlib> 
#include "date.h" 
#ifndef FRIEND_H 
#define FRIEND_H
class Friend{
    public:
	Friend();
	std::string get_name()const;
	Date get_bday()const;
	bool operator == (const Friend& other)const;
	bool operator != (const Friend& other)const;
	void input(std::istream& ins);
	void output(std::ostream& outs)const;
    private:
	std::string name;
	Date bday;
};
std::istream& operator >>(std::istream& ins,Friend& f); std::ostream& operator <<(std::ostream& outs,const Friend& f);
#endif
