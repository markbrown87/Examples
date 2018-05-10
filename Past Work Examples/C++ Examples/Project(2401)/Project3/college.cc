/*************************************************************************

Created by Mark Brown on 24/02/2016
Description: This class is designed to hold linked lists of courses taken 
by the students. It has the ability to add, remove, copy, display, remember
previous lists, calculate the hours, and calucate your overall GPA.

^Below is the .cc connected with the college header file^

*************************************************************************/
#include <iostream>
#include <string>
#include "college.h"
#include "course.h"
#include "node.h"

using namespace std;
//constructor
College::College(string n){
	name = n;
	head = NULL;
}
//deconstructor
College::~College(){
	node *rmptr;
	while(head != NULL){
		rmptr = head;
		head = head->link();
		delete rmptr;
	}
}
//copy constructor
College::College(const College& other){
	if(other.head ==NULL)
		head = NULL;
	else{
		node * source, *dest;
		head =new node(other.head->data());
		source = other.head->link();
		dest=head;
		while(source !=NULL){
			dest->set_link(new node(source->data()));
			dest=dest->link();
			source = source->link();
		}
	}
}
//an overloaded operator for self assignment
College College::operator =(const College& other){
	if(this == &other)
		return *this;
	else{
		delete head;
		node *new_head = other.head;
		node *last = NULL;

		head = NULL;

		while(new_head != NULL){
			if(last == NULL){
				head = new node;
				head->set_data(new_head->data());
				head->set_link(NULL);
				last = head;
			}else{
				last->set_link(new node);
				last = last->link();
				last->set_data(new_head->data());
				last->set_link(NULL);
			}
			new_head = new_head->link();
		}
		return *this;
	}
}
//adds a course to the data field
void College::add(course c){
	node *tmp;
	node *cursor, *nxt, *prev;
	cursor=head;
	bool check=false;
	
	if (head==NULL){//insert head
		head = new node;
		head -> set_data(c);
		head -> set_link(NULL);
	}
	else if (head->data() > c){//insert before head node if taken
		tmp = new node;
		tmp->set_data(c);
		tmp->set_link(cursor);
		head=tmp;
	}
	else{
		for(; cursor != NULL; cursor = cursor->link()){
			if(cursor->data() < c){
				tmp = new node;
				tmp->set_data(c);
				tmp->set_link(cursor->link());
				cursor->set_link(tmp);
			}
		}
	}
}
//displays all the data onto the screen for viewing
void College::display(ostream& outs){
	for(node *cursor=head; cursor != NULL; cursor = cursor->link())
		outs << cursor->data() << endl;
}
//removes the selected (string n) course from the linked list
void College::remove(string n){
	if (head==NULL)
		return;
	else if(head->data().get_course_number()==n){
		node* tmp = head;
		head = head->link();
		delete tmp;
	}
	else if (head !=NULL){
		node *cursor, *nxt, *prv;
		cursor = head;
		while(cursor != NULL){
		nxt = cursor->link();
		prv = cursor;
            	while(nxt != NULL){
               		if(nxt->data().get_course_number() == n){
                  		prv->set_link(nxt->link());
                  		delete nxt;
                  		nxt = prv->link();
               		}
               		else{
                  		prv = nxt;
                  		nxt = nxt->link();
               		}
            	}
		cursor = cursor->link();
		}
	}
	else {
		node *nextToEnd = head;
		node *end = head->link();
		while (end->link() != NULL) {
			nextToEnd = end;
			end = end->link();
		}
		if(end->data().get_course_number() == n){
			delete end;
			nextToEnd->set_link(NULL);
		}
	}
}
//calculates the total number of hours taken thus far
double College::hours(){
	double th = 0.0;
	
	for(node *tmp = head; tmp != NULL; tmp = tmp->link())
		th += tmp->data().get_hours();
	return th;
}
//calculates the overall gpa of a course
double College::gpa(){
	double p = 0.00;
	double th = 0.00;
	node*tmp;
	for(tmp = head; tmp != NULL; tmp = tmp->link()){
		p += tmp->data().get_number_grade() * tmp->data().get_hours();
		th += tmp->data().get_hours();
	}
	return p/th;
}
//loads from file to be used within the program
void College::load(istream& ins){
	course c;

	while(ins>>c)
		add(c);
}
//saves information to a file for later use
void College::save(ostream& outs){
	for(node *tmp = head; tmp != NULL; tmp = tmp->link())
		outs << tmp->data();
}
