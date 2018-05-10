/*
Name:Mark Brown
Date:03/02/2016
Description: This fine is designed to house the friends portion of the facebook friends.
It is designed to add, remove, and compare individual Friend(s).
*/

#include<iostream>
#include<string>
#include<cstdlib>
#include "friend.h"
#include "date.h"

using namespace std;
//constructor
Friend::Friend(){
	name = "";
}
//retrieves the name of said friend
string Friend::get_name()const{
	return name;
}
//retrieves the birthday of said friend
Date Friend::get_bday()const{
	return bday;
}
//compares two friends based on their bday and name to find if they are equal
bool Friend::operator == (const Friend& other)const{
	return (name == other.name || bday == other.bday);
}
//compares two friends based on their bday and name to find if they are not equal
bool Friend::operator !=(const Friend& other)const{
	return (name != other.name||bday != other.bday);
}
void Friend::input(istream& ins){//input will be coming from a file
	if(&ins == &cin){
		cout << "Please provide name: ";
		if (cin.peek() == '\n')
			cin.ignore();
		getline(ins,name);
		cout << "Good, and their birthday?";
		if (cin.peek() == '\n')
			cin.ignore();
		ins >> bday;
	}
	else{
		getline(ins, name);
		if(ins.peek() == '\n')
			ins.ignore();
		ins >> bday;
		ins.ignore();
	}
}
//output to screen or the file
void Friend::output(ostream& outs)const{
	outs << name << endl;
	outs << bday << endl;
}
//links >> operator to the input format above
istream& operator >>(istream& ins, Friend& f){
	f.input(ins);
    return ins;
}
//links the << operator to the output format above
ostream& operator <<(ostream& outs, const Friend& f){
    f.output(outs);
    return outs;
}
