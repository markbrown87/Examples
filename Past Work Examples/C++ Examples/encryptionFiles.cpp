/*
Name: Mark Brown
Date: 05/10/2015
Description: The progream encrypts/decrypts a file using the Caeser
cypher.
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;

//prototypes
void displayMenu();
void getShiftKey(int &shiftKey);
void getFileNames_encryption ();
void getFileNames_decryption ();
void encryption(ifstream &inputFile, ofstream &outputFile, int shiftKey);
void decryption(ifstream &inputFile, ofstream &outputFile, int shiftKey);

//declartions
string inputFileName;
string outputFileName;
ifstream inputFile;
ofstream outputFile;
string tester_string;

int main ()
{
        int choice;
        int shiftKey = 1; //setting the shiftkey
        do
        {
			displayMenu();
            cin >> choice;
            if (choice == 1)
            {
                getShiftKey(shiftKey); // calls function getShiftKey
            }
            else if (choice == 2)
            {
                getFileNames_encryption(); //encryption stage
				cin >> inputFileName >> outputFileName;
                inputFile.open(inputFileName.c_str()); // opens files
				outputFile.open(outputFileName.c_str());// opens files
                if (inputFile.fail() || outputFile.fail()) // tests files to see if they open correctly - if not then exit the program
                { 
                    cout << "Error opening file\n";
                    exit(1);
                }
				encryption(inputFile, outputFile, shiftKey);
				inputFile.close();
				outputFile.close();				
            }
            else if (choice == 3)
            {
				getFileNames_decryption(); //decryption stage
				cin >> inputFileName >> outputFileName; 
                inputFile.open(inputFileName.c_str());// opens files
				outputFile.open(outputFileName.c_str());// opens files
                if (inputFile.fail() || outputFile.fail())// tests files to see if they open correctly - if not then exit the program
                {
                    cout << "Error opening file\n";
                    exit(1);
                }
				decryption(inputFile, outputFile, shiftKey);
				inputFile.close();
				outputFile.close();	
            }
        }while (choice != 4); // closes the program 
        return EXIT_SUCCESS;
}

//functions
void displayMenu()
{
        cout << "1. Set the shift key value\n2. Encrypt a message\n3. Decrypt a message\n4. Quit\nEnter your choice: ";
}

void getShiftKey(int &shiftKey)
{
        do
        {
			cout << "Please input the shift key(1 - 10): ";
			cin >> shiftKey;
			if (shiftKey > 10 || shiftKey < 1)
                cout << "Error: Wrong value have been entered. Input again." << endl;
        }while(shiftKey < 1 || shiftKey > 10);
}

void getFileNames_encryption ()
{
		cout << "Please enter the name of the file you would like to encrypt and the name of the output file. Remember - file must be in the same locatiomn as this program: ";
}

void getFileNames_decryption ()
{
		cout << "Please enter the name of the file you would like to decrypt and the name of the output file. Remember - file must be in the same locatiomn as this program: ";
}

void encryption (ifstream &inputFile, ofstream &outputFile, int shiftKey)
{
	char data;
	char result;
	int count = 0;
	while (!inputFile.eof())
    {
		inputFile.get(data);
		if (data == '\n')
		{
			shiftKey++;
			count++;
			data -= shiftKey;
		}
		if (count == 5) //used to count through the rotations before cycling back
		{
			count = 0;
			shiftKey -= 5;
			data = '\n' - shiftKey;
		}
		if (inputFile.eof()) //this was added to stop from printing an extra character at the end of the line (not sure the reason but this solved it)
			break;
		result = data + shiftKey; //shifts the character over by a set number of characters
		outputFile << result;//prints to output file
    }
}

void decryption (ifstream &inputFile, ofstream &outputFile, int shiftKey)
{
	char data;
	char result;
	int count = 0;
	while (!inputFile.eof())
    {
		inputFile.get(data);
		result = data;
		if (result == '\n')
		{
			shiftKey++;
			count++;
		}
		if (count == 5)//used to count through the rotations before cycling back
		{
			count = 0;
			shiftKey -= 5;
		}
		if (result != '\n')
			result = data - shiftKey;//shifts the character over by a set number of characters
		if (inputFile.eof()) //this was added to stop from printing an extra character at the end of the line (not sure the reason but this solved it)
			break;
		outputFile << result; //prints to output file
    }
}