/* 	Created: Mark Brown
Date: 6/11/2017
Description: Find the min and max as well as the second min and max from an array
Also, the searching algorithm returns first, second, second last, and last
members alphabetically
*/


#include "FindMaxMin.h"
#include "student.h"

using namespace std;

void FindMaxMin(vector<Student> &students, size_t &max, size_t &max2, size_t &min, size_t &min2, size_t &num_compares) {
	//set max and min variables
	max = 0;
	min = 0;
	max2 = 0;
	min2 = 0;

	//note it's last name then first name, not first name and then last name
	// also make sure to look at 214 in the book and modify that style of selection for max2 and min2 and it will run O('2n-2')
	//  ONE more point, change the class or operator to overload it and use the comparisons that way

	for (int i = 1; i < students.size(); ++i) {
		num_compares++;
		if (compareMax(students[max],students[i])) {
			max2 = max;
			max = i;
		}
		num_compares++;
		if (compareMin(students[min], students[i])) {
			min2 = min;
			min = i;
		}

	}
}

bool compareMax(Student student, Student other) {
		if (student.last_name == other.last_name) {
			if (student.first_name == other.first_name) {
				return (student.SSN < other.SSN ? true : false);
			}
			else
				return (student.first_name < other.first_name ? true : false);
		}
		else
			return(student.last_name < other.last_name ? true : false);
}

bool compareMin(Student student, Student other) {
	if (student.last_name == other.last_name) {
		if (student.first_name == other.first_name) {
			return (student.SSN > other.SSN ? true : false);
		}
		else
			return (student.first_name > other.first_name ? true : false);
	}
	else
		return(student.last_name > other.last_name ? true : false);
}