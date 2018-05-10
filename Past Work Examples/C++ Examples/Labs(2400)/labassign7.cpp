/*
Name: Mark Brown
Date: 08/10/2015
Description: 
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//prototypes
double calculate_taxes(double salary);
void output_salary(string name, double salary, double taxes, int count, double gross_pay);
void output_summary(double total_salaries, double total_taxes, double gross_pay2);

//declartions
ifstream in_stream;
ofstream out_stream;
string name;
double sum1, sum2, sum3;
double taxes;
double salary;
int count;
double total_salaries, total_taxes;
char ch;
double gross_pay, gross_pay2;

int main()
{
	out_stream << fixed << showpoint;
	out_stream << setprecision(2);
	out_stream.setf(ios::left);

	//error sets to protect the files
	in_stream.open("lab.txt");
	if (in_stream.fail())
	{
		cout << "Error opening input file\n";
		exit(1);
	}
	out_stream.open("report.txt");
	if (out_stream.fail())
	{
		cout << "Error opening input file\n";
		exit(1);
	}

	out_stream << setw(4) << "#" << setw(20) << "Name" << setw(15) << "Salary" << setw(16) << "Taxes" << setw(16) << 	"Gross Pay" << endl << "--------------------------------------------------------------------" << endl;

	//set varaibles to 0 to help during each file
	count = 0;
	sum1= 0;
	sum2 = 0;
	sum3 = 0;

	while (!in_stream.eof())
	{
		//input and read step
		in_stream >> salary;
		taxes = calculate_taxes(salary);
		getline(in_stream, name);
		count++;

		//replacing and calculation step
		gross_pay = salary - taxes;
		sum1 = total_salaries;
		sum2 = total_taxes;
		sum3 = gross_pay2;

		//sum of totals
		total_salaries = sum1 + salary;
		total_taxes = sum2 + taxes;
		gross_pay2 = sum3 + gross_pay;
		
		//function to salary lines
		output_salary(name, salary, taxes, count, gross_pay);
	}
	output_summary(total_salaries, total_taxes, gross_pay2);
	in_stream.close();
	out_stream.close();

}

double calculate_taxes(double salary)
{
	double taxes_percent;	
	if (salary < 1000)
		taxes_percent  = 0;
	else if (salary >= 1000 && salary <= 2000)
		taxes_percent  = 0.1;
	else
		taxes_percent = 0.15;
	taxes = salary * taxes_percent;
	return taxes;
}

void output_salary(string name, double salary, double taxes, int count, double gross_pay)
{
	out_stream << setw(3) << count << setw(20) << name << "$" << setw(15) << salary << "$" << setw(15) << taxes << "$" 		<< setw(15) << gross_pay << endl;	
}

void output_summary(double total_salaries, double total_taxes, double gross_pay2)
{
	
	out_stream << "====================================================================" << endl;
	out_stream << setw(23) << "Total:";
	out_stream << "$" << setw(15) << total_salaries << "$" << setw(15) << total_taxes << "$" << setw(15) << gross_pay2 << endl;
}
