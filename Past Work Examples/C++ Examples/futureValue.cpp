#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>

using namespace std;

//declare variables
double future_value;
double investment_amount;
double interest;
double number_of_years;

//declare constants
//declare characters
char repeat;


//main program
int main ()
{
	do
	{
		std::cout << std::fixed << std::showpoint; //allowing for 2 precision places after the decimal place
		std::cout <<std::setprecision(2);	
		cout << "What is the investment amount, annual interest rate, and time period in years (in that order)?" <<endl;
		cin >> investment_amount >> interest >> number_of_years;
	
		
	if (investment_amount < 0 || interest < 0 || number_of_years < 0)
	{
		cout << "Error: Invalid Input" << endl << endl;

	}
	else
	{
		future_value = investment_amount * pow((1 + (interest/100)), number_of_years);
		cout << "Investment Amount: $" << investment_amount << endl << "Interest: " << interest << "%" << 			endl << "Number of Years: " << number_of_years << endl << "Future Value: $" << future_value << endl;
	}
	cout << "Would you like to repeat the program? (y/n)";
	cin >> repeat;
	cout << endl << endl;
	} while (repeat == 'y' || repeat == 'Y');

	//end of program
	return EXIT_SUCCESS;
}
