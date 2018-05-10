/*
 * program name:
 *    Author:
 *      Date: 
 * Description: 
 *     <Add description here>
 */

#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main (int argc, char const *argv[])
{
	int scores[5];
	
	cout << "Enter 5 scores" << endl;
	for(int i = 0; i < 5; ++i)
	{
		cin >> scores[i];
	}
	
	for(int i = 0; i < 5; ++i)
	{
		cout << scores[i] << endl;
	}
	return EXIT_SUCCESS;
}