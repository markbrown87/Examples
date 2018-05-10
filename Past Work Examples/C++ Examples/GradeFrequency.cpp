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

//prototypes
double get_score();
char get_grade(double score);

int main ()
{
	double score;
	int a_count = 0, b_count = 0, c_count = 0,  d_count = 0, f_count = 0;

	
	score = get_score();
	while (score >= 0)
	{
		char grade = get_grade(score);
		switch (grade)
		{
			case 'A':
			a_count++;
			break;

			case 'B':
			b_count++;
			break;

			case 'C':
			c_count++;
			break;

			case 'D':
			d_count++;
			break;

			case 'F':
			f_count++;
			break;
		}
		//output the score and the grade
		cout << "Score: " << score << ", Grade: " << grade << endl;
		score = get_score();

	}

	cout << "Grade  Frequency" << endl << "________________" << endl << "A\t" << a_count << endl << "B\t" << b_count << 		endl << "C\t" << c_count << endl << "D\t" << d_count << endl << "F\t" << f_count << endl;
}

//functions below 

double get_score()
{
	double score;
	cout << "Enter a positive score (negative to quit): ";
	cin >> score;
	return score;
}

char get_grade(double score)
{
	char grade;
	if(score >= 90)
		grade = 'A';
	else if(score >= 80 && score < 90)
		grade = 'B';
	else if(score >= 70 && score < 80)
		grade = 'C';
	else if(score >= 60 && score < 70)
		grade = 'D';
	else
		grade = 'F';
	return grade;
}
