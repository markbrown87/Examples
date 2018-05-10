/*
 * Created by Mark Brown
 * 9/6/2017
 * 
 * This very simple program is designed solely for the purpose of practicing and perfecting my skills in C++.
 *  The program will be converted to Python once all subprograms have been created and all errors fixed. 
 *
 */


#include <iostream>
#include <stdlib.h>

using namespace std;

int menu();
void program1();


int main() {
	int selection = 1;


	while (!selection == 0) {
	
	selection = menu();
	
	if (selection == 1)
		program1();
	else if (selection == 2);
		//program2();
	else if (selection == 3);
		//program3();
	else if (selection == 4);
		//program4();
	}
	
	cout << "Thank you and have a nice day." << endl;
	
	return 0;
}

int menu() {
	int selection;
	cout << "Please select which program you would like to run? (1,2,3, or 4); 0 to exit the program." << endl;
	cin >> selection;
	
	return selection;
}

void program1() {
	cout << "PRACTICE PRACTICE PRACTICE" << endl;
}
