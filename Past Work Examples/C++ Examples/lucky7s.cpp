/*
Name: Mark Brown
Date: 15/09/2015
Description: The game is called Lucky Sevens - the player rolls a pair of dice. 
If the face values of the dice add up to 7, the player wins $4; otherwise, the player loses $1.
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>

using namespace std;

//declare variables
//int random_int = rand();
int max_reached;
int round;
int die1, die2;
double maximum;
double money_amount;

//declare constants


//declare characters
char play_again;

//main program begin
int main()
{
	srand(time(NULL));
	do
	{
		int rolls = 0;
		std::cout << std::fixed << std::showpoint; //allowing for 2 precision places after the decimal place
		std::cout << std::setprecision(2);
		//input
		cout << "Enter the amount of money you have: "; 
		cin >> money_amount;
		cout << endl;
		maximum = money_amount;
	
		//mathematical calculations
		do
		{
			rolls ++; //keeps track of which roll it is on
			//below is the random_int rand() generator for the dice. Each dice is rolled and it will have a max of 6 and a min of 1 (as seen within the code)
			die1 = (rand() % 6) + 1;
			die2 = (rand() % 6) + 1;
			round = die1 + die2;
			if (round == 7) //if the two dice equal 7 you win 4 dollars
			{
				money_amount += 4;
				if (money_amount >= maximum)
				{
					max_reached = rolls; //keeps track of when your dice rolled the highest amount of money (wins)
					maximum = money_amount; //this is the max amount of money you won 
				}
			}
			else if (round != 7)
			{	
				money_amount --; //if you did not roll a 7 you lose a dollar
			}
		} while (money_amount > 0); //keep the loop running until there is no more money
		
		//output
		cout << "It took " << rolls << " rolls to loose all your money.\nYour maximum was $" << maximum << " and was reached after " << max_reached << " rolls." << endl;
	
		//end while condition
		cout << "Play again? (y/n)";
		cin >> play_again;
	} while (play_again == 'y' || play_again == 'Y');
	return EXIT_SUCCESS;
}
