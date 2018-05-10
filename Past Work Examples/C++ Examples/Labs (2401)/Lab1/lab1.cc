/* Mark Brown 20/01/2016 This program is designed to ask the user to enter two times and a scalar, once 
finished complete many math operations as well as a few boolean operations. */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "MyTime.cc"

//beginning of program 
int main () {
	MyTime time1;
	MyTime time2;
	int tmph, tmpm;
	int scalar;
	
	//usual input/output options
	cout << "Please enter time(1) [example 3:55]: ";
	cin >> time1;
	cout << "Now enter time(2): ";
	cin >> time2;
	cout << "Good, now enter a scalar: ";
	cin >> scalar;
	//Boolean operations found below
	if (time1 == time2)
	cout << "Time1 and time2 are the same" << endl;
	else if (time1 < time2)
	cout << "Time1 is < time2" << endl;
	else if (time2 <= time1)
	cout << "Time2 is <= time1" << endl;
	else
	cout << "Error 404" << endl;
	//use of temp to remember the hours for later math operations as well as math operations found below	
	tmph = time1.get_hours();
	tmpm = time1.get_minutes();
	time1 = time1 / scalar;
	cout << "time1 divided by scalar: " << time1 << endl;
	time1.Reset(tmph, tmpm);
	//above is the divider operation and below is the multipler operations for time1
	time1 = time1 * scalar;
	cout << "time1 times scalar: " << time1 << endl;
	time1.Reset(tmph, tmpm);
	
	
	
	//same as above but for time2
	tmph = time2.get_hours();
	tmpm = time2.get_minutes();
	time2 = time2 / scalar;
	cout << "time2 divided by scalar: " << time2 << endl;
	time2.Reset(tmph, tmpm);
	
	time2 = time2 * scalar;
	cout << "time2 times scalar: " << time2 << endl;
	time2.Reset(tmph, tmpm);
	
	
	
	//adds the two times together and then prints to the screen
	MyTime tmptime;
	tmptime = time1 + time2;
	cout << "time1 added with time2: " << tmptime << endl;
	
	tmptime = time1 - time2;
	cout << "time1 minus time2: " << tmptime << endl;

	return EXIT_SUCCESS;
}
