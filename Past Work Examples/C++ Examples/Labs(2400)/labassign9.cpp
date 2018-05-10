/*
Mark Brown
22/10/2015
This program is designed to...
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>


using namespace std;

//prototypes
void getFileName (string &fileName);
void get_numbers(ifstream &inFile, double numbers[], int &count);
void print_numbers(double numbers[], int count);
void get_smallest(double numbers[], int count);
void get_largest(double numbers[], int count);
double get_total(double numbers [], int count);

//beginning of program
int main ()
{
	string fileName;
	ifstream inFile;
	double numbers [100];
	int count;
	double sum;
	getFileName(fileName);
	inFile.open(fileName.c_str());
	if (inFile.fail() )
	{
		cout << "Error opening file. Closing Program now." << endl;
		exit(1);
	}
	get_numbers(inFile, numbers, count);
	print_numbers(numbers, count);
	get_smallest(numbers, count);
	get_largest(numbers, count);
	sum = get_total(numbers, count);
	cout<< "The total of all the values is " << sum << endl;
	
	inFile.close();
	
	return EXIT_SUCCESS;
}

//functions
void getFileName (string &fileName)
{
		cout << "Please enter the input file name: ";
		cin >> fileName;
}

void get_numbers(ifstream &inFile, double numbers[], int &count)
{
	int i = 0;
	count = 0;
	while(1)
	{
		if (inFile.eof())
			break;
		inFile >> numbers[i];
		count++;
		i++;
	}
	count--;
}

void print_numbers(double numbers[], int count)
{
	int a = 0;
	cout << std::fixed << std::showpoint;
	cout << std::setprecision(2);
	cout << "Values read: " << endl;
	for (int i = 0; i < count; i++)
	{
		if (a == 5)
		{
			cout << endl;
			a=0;
		}
		a++;
		cout << setw(10) << numbers[i];
	}
	cout << endl;
}

void get_smallest(double numbers[], int count)
{

	sort(numbers, numbers + count);
	cout << "The smallest value is " << numbers [0] << endl;
}

void get_largest(double numbers[], int count)
{

	sort(numbers, numbers + count);
	cout << "The largest value is " << numbers [count - 1] << endl << "Number of values read is " << count << endl;
}

double get_total(double numbers [], int count)
{
	double sum = 0;
	for (int i = 0; i < count; i++)
		sum = numbers[i] + sum;
	return sum;
}

