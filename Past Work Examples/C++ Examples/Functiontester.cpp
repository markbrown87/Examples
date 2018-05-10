#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//prototypes
double calculate_taxes(double salary);
void output_salary(string name, double salary, double taxes, int count);
//void output_summary(out_stream, double total_salaries, double total_taxes);

//declartions
ifstream in_stream;
ofstream out_stream;
string name;
double taxes;
double salary;
int count;
double total_salary, total_taxes;
char ch;

int main()
{
	out_stream << fixed << showpoint;
	out_stream << setprecision(2);	
	in_stream.open("lab.txt");
	if (in_stream.fail())
	{
		cout << "Error opening input file\n";
		exit(1);
	}
	out_stream.open("testfile2.txt");
	if (out_stream.fail())
	{
		cout << "Error opening input file\n";
		exit(1);
	}
	count = 0;
	while (!in_stream.eof())
	{
		in_stream >> salary;
		taxes = calculate_taxes(salary);
		getline(in_stream, name);
		count++;
		output_salary(name, salary, taxes, count);
	}
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

void output_salary(string name, double salary, double taxes, int count)
{
	out_stream << count << " " << name << " " << salary << " " << taxes << endl;
}
