/*
Name: Mark Brown
Date: 01/10/2015
Description: 
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

//declartions
const double PI = 3.14159;

//prototypes
void display_menu();
void get_input(double& radius);
void get_input(double& radius, double& height);
double get_volume_sphere (double radius);
double get_volume_cylinder (double radius, double height);


int main()
{
	int choice;
	double radius, height;
	std::cout << std::fixed << std::showpoint;
	std::cout << std::setprecision(2);
	do
	{
		display_menu();
		cin >> choice;
		if (choice == 1)
		{
			double answer = 0;
			get_input(radius);
			answer = get_volume_sphere(radius);
			cout << "The volume of a sphere with a radius of " << radius << " is " << answer << endl;
		}
		else if (choice == 2)
		{
			double answer = 0;
			get_input(radius, height);
			answer = get_volume_cylinder (radius, height);
			cout << "The volume of a cylinder with a radius of " << radius << " and a height of " << height << 				" is " << answer << endl << endl;
		}
	}while (choice != 3);
	
	return EXIT_SUCCESS;
}

void display_menu()
{
	cout << "1. Calculate the volume of a sphere\n2. Calulcate the volume of a cylinder\n3. Quit\nEnter your choice: ";
}

void get_input(double& radius)
{
	cout << "Enter the radius of the sphere: ";
	cin >> radius;
}

void get_input(double& radius, double& height)
{
	cout << "Enter the radius and the height of the cylinder: ";
	cin >> radius >> height;
}

double get_volume_sphere (double radius)
{
	double answer = 4 * (PI * pow(radius, 3)) / 3;
	return answer;
}

double get_volume_cylinder (double radius, double height)
{
	double answer = PI * pow(radius, 2) * height;
	return answer;
}
