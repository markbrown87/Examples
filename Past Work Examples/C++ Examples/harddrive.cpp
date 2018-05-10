/*
Name: Mark Brown
Date: 07/09/2015
Description: The program is designed to check three variables (hard 
drives), which apply % discounts when
purchasing certain number of hard drives which depends on each variable. 
The program has if and while loops and
won't quit until the user enters 'y or n' into the program.
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;


//varaible declartion
int drnum;
char hadr;
char ohio;
char qt;
double dscnt;
double totpr, subtot, total;
double tax;

//constant declartion
double WEST = 90;
double LACIE = 100;
double SEA = 95;

int main ()
{
	do //beginning of loop
	{
	std::cout << std::fixed << std::showpoint; //allowing for 2 precision places after the decimal place
	std::cout <<std::setprecision(2);
	
	//prompt the user for input
	cout << "<W, L, or S> followed by number of drives." << endl;
	cin >> hadr >> drnum;
	cout << "Are you an Ohio resident? <y or n>" << endl;
	cin >> ohio;
	cout << endl;
	
	//if statments
	//Western hard drive
	if (hadr == 'W' || hadr == 'w')
	{
		if (drnum <=2)
		{
			totpr = (WEST * drnum); //normal - nondiscounted - price applied
			subtot = totpr;
		}
		else if (drnum >= 3)
		{
		totpr = (WEST * drnum);
		subtot = (WEST * drnum) * 0.95; //discount prices applied
		}
	}

	//LACIE hard drive
	if(hadr == 'L' || hadr == 'l')
	{
		if (drnum == 1)
		{
			totpr = (LACIE * drnum);
			subtot = totpr;
		}
		else if (drnum != 1)
		{
			totpr = (LACIE * drnum);
			subtot = (LACIE * drnum) * 0.97;
		}
	}
	
	//Seagate hard drive	
	if(hadr == 'S' || hadr == 's')
	{
		if (drnum <= 4)
		{
			totpr = (SEA * drnum);
			subtot = totpr;
		}
		else if (drnum >= 5)
		{
		totpr = (SEA * drnum);
		subtot = (SEA * drnum) * 0.90;
		}
	}
	
	//ohio residents tax
	tax = 0.00;
	if(ohio == 'Y' || ohio == 'y')
	{
		tax = subtot * 0.07;
	}

	//output for the user to read
	cout << "\t\t Hard Drives Order" << endl << endl;
	if (hadr == 'l' || hadr == 'L')
	{
		cout << "Drive brand: Lacie" << endl << "Quantity: " << 
drnum << endl << "Price: $" << LACIE << endl;
	}
	if (hadr == 's' || hadr == 'S')
	{
		cout << "Drive brand: Seagate" << endl << "Quantity: " 
<< drnum << endl << "Price: $" << SEA << endl;
	}	
	if (hadr == 'w' || hadr == 'W')
	{
		std::cout << "Drive brand: Western Digital" << endl << 
"Quantity: " << drnum << endl << "Price: $" << WEST << endl;
	}
	
	//applying the answer to the question "Ohio resident?"
	if (ohio == 'y' || ohio == 'Y')
	{
		cout << "Ohio Resident: Yes" << endl << endl;
	}	
	if (ohio == 'n' || ohio == 'N')
	{
		cout << "Ohio Resident: No" << endl << endl;
	}
	
	//calculations for 'discount' and 'total'
	dscnt = subtot - totpr;
	total = subtot + tax;
	
	//output the final section of the transaction (receipt)
	cout << "Total price: " << totpr << endl << 
"---------------------" << endl << endl << "Discount: $" << dscnt << 
endl 
	<< "Subtotal: $" << subtot << endl << "Taxes: $" << tax << endl 
<< "=====================" << endl << endl << "Total: $" << total << 
endl;
	
	//prompting the user if they would like to quit or loop the program again
	cout << endl << endl << endl;
	cout << "Would you like to quit the program? (y/n)" << endl;
	cin >> qt;
	cout << endl << endl << endl;
	}
	while (qt == 'n' || qt == 'N'); //loop condition
	
	//outside loop
	return EXIT_SUCCESS;
}
