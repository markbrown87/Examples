/*
Mark Brown
12/11/2015
This program is designed to...
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstring>


using namespace std;

struct Employee{
	string first_name;
	string last_name;
	int id;
	double salary;
};

//prototypes
void getFileNames(string &inFileName);
void get_employee_info(ifstream& inFile, Employee all_emps[], int i);
void print_sort_id(Employee all_emps[], int count);
void print_sort_salary(Employee all_emps[], int count);
void print_sort_name(Employee all_emps[], int count);
void sort_name(Employee all_emps[], int count);
void sort_id(Employee all_emps[], int count);
void sort_salary(Employee all_emps[], int count);
void print_total_payroll(Employee all_emps[], int count);

//beginning of program
int main ()
{
	cout.setf(ios::left);
	cout << fixed << showpoint;
	cout.precision(2);
	
	string inFileName;
	ifstream inFile;

	Employee all_emps[100];

	getFileNames(inFileName);
	inFile.open(inFileName.c_str());
	if (inFile.fail())
	{
		cout << "Error opening file. Exiting program.";
		exit(1);
	}
	

	int i = 0;
	while(!inFile.eof())
	{
		if(inFile.eof())
			break;
		
		get_employee_info(inFile, all_emps, i);
		i++;
	}

	//calls all functions below to sort by id, name, salary and print in that order, respectively
	print_sort_id(all_emps,i);
	print_sort_name(all_emps, i);
	print_sort_salary(all_emps, i);
	print_total_payroll(all_emps, i);


	return EXIT_SUCCESS;
}

//functions
void getFileNames(string &inFileName)//used to ask for the input file name
{
	cout << "Please provide the input file name: ";
	cin >> inFileName;
}

void get_employee_info(ifstream& inFile, Employee all_emps[], int i)//gathers all the employee's information
{
	inFile >> all_emps[i].id >> all_emps[i].first_name >> all_emps[i].last_name >> all_emps[i].salary;
}

void print_sort_id(Employee all_emps[], int count)//sorts the employees by id then prints to the screen
{
	for(int j=0;j<count;j++)
		sort_id(all_emps, j);

	cout << endl << "Sorted by ID" << endl << setw(8) << "ID" << setw(20) << "Name" << setw(8) << "Salary" << endl;
	cout << "------------------------------------" << endl;

	for(int i = 0;i < (count-1); i++)
	{
		cout << setw(8) << all_emps[i].id << setw(20) << all_emps[i].last_name + ", " + all_emps[i].first_name;
		cout << "$" << all_emps[i].salary << endl;
	}
}

void print_sort_name(Employee all_emps[], int count)//sorts the employees by name then prints to the screen
{
	for(int j=0;j<count;j++)
		sort_name(all_emps, j);

	cout << endl << "Sorted by Name" << endl << setw(8) << "ID" << setw(20) << "Name" << setw(8) << "Salary" << endl;
	cout << "------------------------------------" << endl;

	for(int i = 0;i < (count-1); i++)
	{
		cout << setw(8) << all_emps[i].id << setw(20) << all_emps[i].last_name + ", " + all_emps[i].first_name;
		cout << "$" << all_emps[i].salary << endl;
	}
}

void print_sort_salary(Employee all_emps[], int count)//sorts the employees by salary then prints to the screen
{
	for(int j=0;j<count;j++)
		sort_salary(all_emps, j);

	cout << endl << "Sorted by Salary" << endl << setw(8) << "ID" << setw(20) << "Name" << setw(8) << "Salary" << endl;
	cout << "------------------------------------" << endl;

	for(int i = 0;i < (count-1); i++)
	{
		cout << setw(8) << all_emps[i].id << setw(20) << all_emps[i].last_name + ", " + all_emps[i].first_name;
		cout << "$" << all_emps[i].salary << endl;
	}
}

void print_total_payroll(Employee all_emps[], int count)//calculate the total payroll then proceed to print the total
{
	double total = 0;
	for(int i = 0; i < (count-1); i++)
		total +=all_emps[i].salary;

	cout << endl << endl << "Total Payroll: $" << total << endl;
}

void sort_id(Employee all_emps[], int count)//sorts by id
{
	Employee temp[1];
	for(int i = 0;i < count; i++)
	{
		for(int m = 0;m<(count-1);m++)
		{
			if (all_emps[m].id > all_emps[m+1].id)
			{
				temp[0] = all_emps[m+1];
				all_emps[m+1]= all_emps[m];
				all_emps[m]= temp[0];
			}
		}
	}
}

void sort_name(Employee all_emps[], int count)//sorts by name
{
	Employee temp[1];
	for(int i = 0;i < count; i++)
	{
		for(int m = 0;m<(count-1);m++)
		{
			if (all_emps[m].last_name[0] > all_emps[m+1].last_name[0])
			{
				temp[0] = all_emps[m+1];
				all_emps[m+1]= all_emps[m];
				all_emps[m]= temp[0];
			}
		}
	}
}

void sort_salary(Employee all_emps[], int count)//sorts by salary
{
	Employee temp[1];
	for(int i = 0;i < count; i++)
	{
		for(int m = 0;m<(count-1);m++)
		{
			if (all_emps[m].salary > all_emps[m+1].salary)
			{
				temp[0] = all_emps[m+1];
				all_emps[m+1]= all_emps[m];
				all_emps[m]= temp[0];
			}
		}
	}	
}


