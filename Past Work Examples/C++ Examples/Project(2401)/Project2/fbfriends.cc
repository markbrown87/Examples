/*
Name:Mark Brown
Date:03/02/2016
Description: This file is a container class. It is designed to hold facebook friends as well do many other 
interesting features like search by name, sort by birthday, add or remove, and cut and place.
*/

#include <iostream>
#include <string>
#include <fstream>
#include<cstdlib>
#include <algorithm>
#include "fbfriends.h"

using namespace std;
//constructor
FBFriends::FBFriends(){
	used = 0;
	capacity = 5;
	data = new Friend[capacity];
	current_index = 0;
}
//destructor
FBFriends::~FBFriends(){
	delete [] data;
}
//copy function
FBFriends::FBFriends(const FBFriends &original){
	used = original.used;
	capacity = original.capacity;
	current_index = original.current_index;
	data=new Friend[capacity];
	copy(original.data, original.data+used,data);
}
//overloaded operator that copies two dynamtic memory locations
FBFriends& FBFriends::operator =(const FBFriends& other){
	if(this == &other)
		return *this;
	if(capacity != other.capacity){
		delete [] data;
		data = new Friend[other.capacity];
		capacity = other.capacity;
	}
	used = other.used;
	copy(other.data, other.data+used, data);
	return *this;
}
//begins the internal iterator
void FBFriends::start(){
	current_index = 0;
}
//advances the internal iterator
void FBFriends::advance(){
	current_index++;
}
//checks if the current_index is a valid location
bool FBFriends::is_item(){
	return current_index < used;
}
//returns the current_index location
Friend FBFriends::current(){
	if (is_item())
		return data[current_index];
	else
		cout << "Not valid current index\n";
		Friend tmp;
		return tmp;
}
//removes the current_index location details
void FBFriends::remove_current(){
	if(is_item()){
		for(int i=current_index;i<used-1;i++)
			data[i]=data[i+1];
		used--;
	}
}
//inserts details in the element before the current_index or at the beginning of the array
void FBFriends::insert(const Friend& f){
	if (used == capacity)
		resize();
	if(!is_item())
		current_index=0;
	for(int i=used;i>current_index;i--)
		data[i]=data[i-1];
	data[current_index] = f;
	used++;
}
//attaches details after the current_index element or at the end of the array
void FBFriends::attach(const Friend& f){
	if(used == capacity)
		resize();
	if(!is_item())
		data[current_index]=f;
	for(int i=used;i>current_index;i--)
		data[i]=data[i-1];
	data[current_index+1]=f;
	current_index++;
	used++;
}
//prints all of the current friends to the screen
void FBFriends::show_all(ostream& outs)const{
	for(int i=0;i<used;i++)
		data[i].output(outs);
}
void FBFriends::bday_sort(){
	bool check = false;
	Friend tmp;
	while(!check){
		check = true;
		for (int i=0;i <used-1;i++){
			if(data[i].get_bday() > data[i+1].get_bday()){
				tmp = data[i];
				data[i]=data[i+1];
				data[i+1]=tmp;
				check = false;
			}
		}
	}
}
//searches for a friend's name -- case sensitive
Friend FBFriends::find_friend(const string& name)const{
	for(int i=0;i<used;++i){
		if(data[i].get_name() == name)
			return data[i];
	}
	Friend tmp;
	cout << "No friend by that name was found. Error 404.";
	return tmp;
}
//checks if there is another person by that name and birthday -- case sensitive
bool FBFriends::is_friend(const Friend& f) const{
	for(int i=0;i<used;++i){
		if(data[i] == f)
			return true;
	}
	return false;
}
//loads friends from file
void FBFriends::load(istream& ins){
	Friend tmp;
	
	ins >> tmp;
	data[used] = tmp;
	used++;
	while(ins >> tmp){
		if (used == capacity)
			resize();
		data[used] = tmp;
		++used;
	}
}
//saves all the friends from the current sessions to a file previously named
void FBFriends::save(ostream& outs){
	for(int i=0;i<used;i++)
		data[i].output(outs);
}
//resizes the dynamtic array for more memeory
void FBFriends::resize(){
	Friend *tmp;
	tmp= new Friend [capacity+5];
	copy(data,data+used,tmp);
	capacity=capacity+5;
	delete[] data;
	data=tmp;
}
