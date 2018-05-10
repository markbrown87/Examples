/*
Mark Brown
21/10/2015
Description: The program reads a file of website names and removes all 
duplicate IP addresses. The
program outputs each site with the number of total visitors, number of 
unique visitors, and the
unique IP addresses into a separate file.
*/



#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

//prototypes
void getFileNames(string &inFileName, string &outFileName);
int ip_address(ifstream inFile, int data[], int data2[]);

//file streams


int main ()
{
	string inFileName, outFileName;
	ifstream inFile;
	ofstream outFile;
	string siteName[4],ohio[20]; // yahoo[50], google[100], notInteresting[1];
	int ohio_count;
	
	
	getFileNames(inFileName, outFileName);
	
	
	inFile.open(inFileName.c_str());
	outFile.open(outFileName.c_str());
	if (inFile.fail() || outFile.fail())
	{
		cout << "Error opening file(s). Exiting program.";
		exit(1);
	}
	
	ohio_count = ip_address(inFile, siteName, ohio);
	
	cout << ohio_count << endl << siteName[0] << endl << ohio[0] << " " << ohio[1];
	
	inFile.close();
	outFile.close();
}


//Functions below
void getFileNames(string &inFileName,string &outFileName)
{
	cout << "Please provide the input and output file names in that order: ";
	cin >> inFileName >> outFileName;
}

int ip_address(ifstream &inFile, int data[], int data2[])
{
	int i = 0;
	inFile >> data[0];
	while (1)
	{
		inFile >> data2[i];
		if(data2[i] == "-----")
			break;
		i++;
	}
	return (i);
}
