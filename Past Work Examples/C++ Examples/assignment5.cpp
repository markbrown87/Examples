/*
Name: Mark Brown
Date: 05/10/2015
Description: The progream encrypts/decrypts a file using the Caeser
cypher.
NOTE: If you need more help just review the slide/page during Monday's
(05/10/2015) class regarding calling and writting to external files
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;

//prototypes
void displayMenu();
void getShiftKey(int &shiftKey);
void getFileNames(const char *& inputFileName);

//declartion
const char* inputFileName[16];
//char  outputFileName[16];
ifstream inputFile;
ofstream outputFile;
string test = "test";

int main ()
{
        int choice;
        int shiftKey = 1;
        do
        {
                displayMenu();
                cin >> choice;
                if (choice == 1)
                {
                        //shift value choice
                        //can also ask to set the amount for rotation (when the cypher cycles back to the orginal k$
                        getShiftKey(shiftKey);
                }
                else if (choice == 2)
                {
                        //encryption choice
                        //do stuff
                        getFileNames(inputFileName[16]);
                        inputFile.open(inputFileName);
                        if (inputFile.fail())
                        {
                                cout << "Error opening input file\n";
                                exit(1);
                        }
                        outputFile.open("tester.txt");
                        outputFile << test;
                        inputFile.close();
              outputFile.close();
                }
                else if (choice == 3)
                {
                        //decryption choice
                        //do stuff
                }
        }while (choice != 4);
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

void getFileNames (const char*& inputFileName)
{
		cout << "Please enter the name of the file you would like to encrypt. Remember - file must be in the same locatiomn as this program:  ";
        cin >> inputFileName;
        //cout << "Please enter a name for the output file: ";
        //cin >> outputFileName;
}

