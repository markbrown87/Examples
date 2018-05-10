/* 	Created: Mark Brown 
	Date: 6/11/2017
	Description: Find the min and max as well as the second min and max from an array
		Also, the searching algorithm returns first, second, second last, and last
		members alphabetically
*/
#include <iostream>
#include <fstream>
#include "FindMaxMin.h"
#include "student.h"

using namespace std;

int main() {
	vector<Student> students;
	size_t max = 0, max2 = 0, min = 0, min2 = 0, num_compares = 0;

	//test examples
	ifstream fin;
	string first, last, ssn;
	int counter;
	Student holder;

	fin.open("students.txt");
	while (fin >> first >> last >> ssn) {
		holder.first_name = first;
		holder.last_name = last;
		holder.SSN = ssn;
		students.push_back(holder);
	}


	FindMaxMin(students, max, max2, min, min2, num_compares);


	cout << "Below is the max and min (and 2's) of students\n";
	cout << "Number of students in the list: " << students.size() << endl;
	cout << "[MAX]: " << max << " [MAX2]: " << max2 << " [MIN]: " << min << " [MIN2]: " << min2 << " number of compares: " << num_compares << endl;
}