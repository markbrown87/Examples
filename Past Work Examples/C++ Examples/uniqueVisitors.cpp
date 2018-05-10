/*
Mark Brown
21/10/2015
Description: The program reads a file of website names and removes all duplicate IP addresses. The
program outputs each site with the number of total visitors, number of unique visitors, and the
unique IP addresses into a separate file.
*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

/*Hints and notes:
-DON'T use global variables
-don't forget to find out how to correct your indentations because 
well... I lost points because of the transfer from putty to notepad... 
fucking stupid...

*/

//prototypes
void getFileNames(string &inFileName, string &outFileName);


//file streams



int main ()
{
	string inFileName, outFileName;
	ifstream inFile;
	ofstream outFile;
	string siteName[5], trash[1];
	string ipAddress[60];
	int count = 0;
	int  i = 0;
	getFileNames(inFileName, outFileName);
	
	inFile.open(inFileName.c_str());
	outFile.open(outFileName.c_str());	
	if (inFile.fail() || outFile.fail())
	{
		cout << "Error opening file(s). Exiting program.";
		exit(1);
	}
	//while (!inFile.eof())
	//{
		getline(inFile, siteName[0]);
		while (ipAddress != "-")
		{
			inFile >> ipAddress[i];
			count++;
			i++;
		}

		getline(inFile, trash[0]);
		outFile << siteName[0] << endl << ipAddress [0] << " " << ipAddress[3];
	//}
	
	inFile.close();
	outFile.close();
}

//Functions below
void getFileNames(string &inFileName,string &outFileName)
{
	cout << "Please provide the input and output file names in that order: ";
	cin >> inFileName >> outFileName;
}
