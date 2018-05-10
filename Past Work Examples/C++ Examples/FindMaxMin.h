/* 	Created: Mark Brown
Date: 6/11/2017
Description: Find the min and max as well as the second min and max from an array
Also, the searching algorithm returns first, second, second last, and last
members alphabetically
*/
#ifndef FINDMAXMIN_H
#define FINDMAXMIN_H

#include <vector>
#include "student.h"

using namespace std;

void FindMaxMin(vector<Student> &students, size_t &max, size_t &max2, size_t &min, size_t &min2, size_t &num_compares);
bool compareMax(Student student, Student other);
bool compareMin(Student student, Student other);


#endif