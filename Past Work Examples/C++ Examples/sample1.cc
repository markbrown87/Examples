
//Mark Brown
//Sept 03, 2015
//Program thatconverts seconds into day(s)/hour(s)/Minute(s)/seconds


#include <iostream>
#include <cstdlib>

using namespace std;

//below are the declared variables
int secs;
int mins;
int hours;
int days;
//remainders
int remx, remy;

//calculation variables below 
int const CALMIN = 60, vara, varb = 20, varss;
int const CALHOUR = 3600; 
int const CALDAY = 86400; 


//start of program 
int main()
{
	//ask for inputs
	cout << "Please enter the amount of time (in seconds only): ";
	cin >> secs;


	//caculate inputs 
	//calculation for finding days 
	days = (secs / CALDAY);
	remx = (secs % CALDAY);

	//calculation for finding hours 
	hours = (remx / CALHOUR);
	remy = (remx % CALHOUR);

	//calculation for finding minutes 
	mins = (remy / CALMIN);
	remx = (remy % CALMIN);

	//remainder is equal to seconds 
	secs = remx;

	//output response 
	cout << days << "d:" << hours << "h:" << mins << "m:" << secs << "s" << endl;

	//testing function
	while (fred != george)
	{
		cout << "This is just a test";
	}

	return false;
}
