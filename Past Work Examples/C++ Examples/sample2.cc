/*
Name: Mark Brown
Date: 17/09/15
Description: The program is designed to check all sides of the triangle. If any two sides don't match the third, there will be an invalid input error. Thus, it checks the validness of the triangle and then performs the heron's formula.
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>

using namespace std;

double side1, side2, side3;
double area;
double s_x;
double added_sides1, added_sides2, added_sides3, limit1, limit2, limit3;

int main()
{
	do
	{
		cout << fixed << showpoint; //allowing for 2 precision places after the decimal place
		cout << setprecision(2);

		cout << "Please input the three sides of a triangle (a,b, & c) [All 0's will terminate the program]: " << endl;
		cin >> side1 >> side2 >> side3;
		
		//The calculations for determining the correctness of the triangle.
		added_sides1 = side2 + side3;
		added_sides2 = side1 + side3;
		added_sides3 = side1 + side2;
		
		//the limit or the check variable against the sides of the triangle.
		limit1 = side1;
		limit2 = side2;
		limit3 = side3;

		//the if loop to determine the heron's theorm.
		if ((limit1 < added_sides1) && (limit2 < added_sides2) && (limit3 < added_sides3) )
		{
			s_x = ((side1 + side2 + side3)/2);
			area = sqrt(s_x * ((s_x - side1) * (s_x - side2) * (s_x - side3)));
			cout << "(Valid, " << area << ")" << endl;
		}
		else if ((limit1 > added_sides1) || (limit2 > added_sides2) || (limit3 > added_sides3))
		{
			cout << "(Invalid)" << endl;
		}
		
	}while (side1 != 0 && side2 != 0 && side3 != 0); //used to pitch out the program.

	return EXIT_SUCCESS;
}
