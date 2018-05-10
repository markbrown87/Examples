/*
Mark Brown
Sept 03, 2015
Program thatconverts seconds into day(s)/hour(s)/Minute(s)/seconds
*/

#include <iostream>
#include <cstdlib>

using namespace std;

//below are the declared variables
int secs;
int mins;
int hours;
int days;
int remx, remy; //remainders

//calculation variables below
int const CALMIN = 60;
int const CALHOUR = 3600;
int const CALDAY = 86400;


//start of program
int main()
{
	//ask for inputs
	cout << "Please enter the amount of time (in seconds only): ";
	cin >> secs;

	//caculate inputs - don't forget to add % and use the remainder as remaining seconds
	days = (secs / CALDAY); //calculation for finding days
	remx = (secs % CALDAY);

	hours = (remx / CALHOUR); //calculation for finding hours
	remy = (remx % CALHOUR);

	mins = (remy / CALMIN); //calculation for finding minutes
	remx = (remy % CALMIN);

	secs = remx; // remainder is equal to seconds

	//output response
	cout << days << "d:" << hours << "h:" << mins << "m:" << secs << "s" << endl;

	return EXIT_SUCCESS;
}
