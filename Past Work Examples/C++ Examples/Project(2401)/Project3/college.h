/*************************************************************************

Created by Mark Brown on 24/02/2016
Description: This class is designed to hold linked lists of courses taken 
by the students. It has the ability to add, remove, copy, display, remember
previous lists, calculate the hours, and calucate your overall GPA.

^Below is the header file^

*************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "course.h"
#include "node.h"

#ifndef COLLEGE_H
#define COLLEGE_H
class College {
public:
	College(std::string n);
	~College();
	College (const College& other);
	College operator =(const College& other);

	double hours();
	double gpa();
	void add(course c);
	void display(std::ostream& outs);
	void remove(std::string name);

	void load(std::istream& ins);
	void save(std::ostream& outs);

private:
	std::string name;
	node *head;
};
#endif