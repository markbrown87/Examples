/*
Mark Brown
27/01/2016
This program is designed ...
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include "numlist.h"

using namespace std;


//beginning of program
int main ()
{
	string fileName;
	ifstream ifs;
	ofstream ofs;
	NumList list;
	int num1, num2, num3;
	
	cout << "Please enter the name of the file you wish to open: ";
	cin >> fileName;
	
	ifs.open(fileName.c_str());
	if(ifs.fail()){
		cout << "Error 404" << endl;
		exit(1);
	}
	list.load_from_file(ifs);
	ifs.close();

	list.b_sort();
	list.see_all();
	
	cout << "Please enter three different numbers: ";
	cin >> num1 >> num2 >> num3;
	list.insert(num1);
	list.insert(num2);
	list.insert(num3);
	list.b_sort();
	
	int pos;
	pos = fileName.find('.');
	fileName.insert(pos,"sorted");//This inserts "sorted" at the end of the file name
	ofs.open(fileName.c_str());
	list.save_to_file(ofs);
	ofs.close();
	
	return EXIT_SUCCESS;
}
