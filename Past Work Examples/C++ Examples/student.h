/* 	Created: Mark Brown
Date: 6/11/2017
Description: Find the min and max as well as the second min and max from an array
Also, the searching algorithm returns first, second, second last, and last
members alphabetically
*/

#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using std::string;

class Student {
public:
	string SSN;
	string first_name;
	string last_name;
	string major;
	float gpa;
};

#endif