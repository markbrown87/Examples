/*
Mark Brown
15/10/2015
This program is designed to add line numbers to a text file.
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;

//prototypes
void get_files(string &input_filename, string &output_filename);
void number_file(string input_filename, string output_filename);

//declarations


//beginning of program
int main ()
{
	string input_filename, output_filename;
	get_files (input_filename, output_filename);
	number_file(input_filename, output_filename);
	
	return EXIT_SUCCESS;
}

//functions

void get_files(string &input_filename, string &output_filename)
{
	cout << "Please enter the name of the files you wish to open: ";
	cin >> input_filename >> output_filename;
}

void number_file(string input_filename, string output_filename)
{
	ifstream inputFile;
	ofstream outputFile;
	int count = 0;
	string line;
	
	inputFile.open(input_filename.c_str());
	outputFile.open(output_filename.c_str());
	if (inputFile.fail() || outputFile.fail())
	{
		cout << "Error processing file(s): System exit.";
		exit(1);
	}
	do
	{
		getline(inputFile, line);
		if (inputFile.eof())
			break;
		if (!line.empty())
		{
			count++;
			outputFile << count << ": " << line << endl;
		}
	}while (1);
	cout << count << " line(s) processed" << endl;
	inputFile.close();
	outputFile.close();
}
	
	
