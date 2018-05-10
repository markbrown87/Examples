/*
Mark Brown
19/11/2015
Description: Design claess, search strings, tokenizing strings, and separate compilation
*/

#include <iostream>//for use of cout and cin 
#include <fstream>//need this for input, output file
#include <string>//need for converting numerical value into string, and for string functions
#include <algorithm>//need this for transform function
#include <sstream>//used to stream a string into another string
#include "dvd.h"

using namespace std;

//main program
int main ()
{	
	DVD dvd1("This is a test|1900|PS4");
	
	/*DVD dvd2("Big butts!!", 1987, "PC Master race");
	DVD dvd3("My Cousin Vinny", 1992, "Joe Pesci");
	DVD dvd4("Pokemon", 1998, "Brock The-man");*/
		
	bool tester1 = dvd1.match(" is a t");
	/*bool tester2 = dvd2.match_year (8);
	bool tester3 = dvd3.match_actor ("pes");
	bool tester4 = dvd4.match("the-man");*/
	
	if(tester1 == true)
		dvd1.output();
	else
		cout << "Did not find Title" << endl;
	
	/*if(tester2 == true)
		dvd2.output();
	else
		cout << "Did not find Year" << endl;

	if(tester3 == true)
		dvd3.output();
	else
		cout << "Did not find Actor" << endl;	
		
	if(tester4 == true)
		dvd4.output();
	else
		cout << "Did not find Match" << endl;*/

	
	return EXIT_SUCCESS;
}
