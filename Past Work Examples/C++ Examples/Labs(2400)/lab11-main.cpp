/*
Mark Brown
05/11/2015
This program is designed to...
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>


using namespace std;

//prototypes
void get_data(double numbers[][20], int row, int column, ifstream &inp);
void print_data(double numbers[][20], int row, int column);
double get_total(double numbers[][20], int row, int column);
double get_average(double numbers[][20], int row, int column);
double get_row_total(double numbers[][20], int row, int column, int ivar);
double get_column_total(double numbers[][20], int row, int column, int ivar);

//declarations


//beginning of program
int main(int argc, char const *argv[])
{
	double numbers[10][20];
	int num_r = 5, num_c = 7;
	ifstream inp;
	string filename;

	cout << "Enter the data file name: ";
	cin >> filename;
	inp.open(filename.c_str());

	cout.setf(ios::fixed);
	cout.precision(2);

	//get the the data from the file
	get_data(numbers, num_r, num_c, inp);
	print_data(numbers, num_r, num_c);
	cout << endl;

	//this calls the function to add the total
	double total = get_total(numbers, num_r, num_c);
	cout << "The total of all values: " << total << endl;

	//get the average of all the data
	double average = get_average(numbers, num_r, num_c);
	cout << "The average of all values: " << average << endl;

	//get total for row 2
	double row2_total = get_row_total(numbers, num_r, num_c, 2); 
	cout << "Total for row 2: " << row2_total << endl;

	//get the total for column 2
	double column2_total = get_column_total(numbers, num_r, num_c, 2);
	cout << "Total for column 2: " << column2_total << endl;
	
	inp.close();
	return 0;
}
//Functions
//function calls to get the data from the file
void get_data(double numbers[][20], int row, int column, ifstream &inp)
{
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < column;j++)
			inp >> numbers[i][j];
	}
}
//function prints the data to the screen
void print_data(double numbers[][20], int row, int column)
{
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
			cout << setw(7) << numbers[i][j];
		cout << endl;
	}
}
//function sums all of the data
double get_total(double numbers[][20], int row, int column)
{
	double sum = 0;	
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < column;j++)
			sum += numbers[i][j];
	}
	return sum;
}
//function averages the sum of all the data
double get_average(double numbers[][20], int row, int column)
{
	double sum = 0;	
	double final = 0;
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < column;j++)
			sum += numbers[i][j];
	}
	final = sum / (row * column);
	return final;
}
//function gathers the sum of a certain row
double get_row_total(double numbers[][20], int row, int column, int ivar)
{
	double sum = 0;	
	for(int j = 0; j < column;j++)
		sum += numbers[ivar][j];
	return sum;
}
//function gathers the sum of a certain column
double get_column_total(double numbers[][20], int row, int column, int ivar)
{
	double sum = 0;	
	for(int j = 0; j < row;j++)
		sum += numbers[j][ivar];
	return sum;
}




