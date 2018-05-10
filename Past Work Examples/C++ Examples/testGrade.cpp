/*
Mark Brown
09/11/2015
Description: This program grades and determines the scores and letter grade of students' multiple-choice tests.
The number of test questions must be deteremined by reading the answer key string at the top of the input file.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;

//Structures
struct Student
{
	string first_name;
	string last_name;
	string answers;
	double grade;
	char grade_letter;
};

//prototypes
void getFileNames(string &inFileName);
void get_student_info(ifstream& inFile, Student all_students[], int i);
void printer(Student all_students[], int i, int length, string answer_key);
double grader(Student all_students[], int i, int length, string answer_key);
char letter_grader(double i);
void best_score(Student all_students[], int i);

int main ()
{
	cout.setf(ios::fixed);
	cout.precision(2);
	
	double average = 0;
	double sum = 0;
	string inFileName;
	string answer_key;
	ifstream inFile;
	Student all_students[100];
	
	getFileNames(inFileName);
	inFile.open(inFileName.c_str());
	if (inFile.fail())
	{
		cout << "Error opening file. Exiting program.";
		exit(1);
	}
	
	
	getline(inFile, answer_key);
	int length = 0;
	length = strlen(answer_key.c_str());
	for(int j=0;j<length;j++)
		answer_key[j] = tolower(answer_key[j]);
	
	int i = 0;
	while(!inFile.eof())
	{
		if(inFile.eof())
			break;
		
		get_student_info(inFile, all_students, i);
		i++;
	}
	
	for (int j=0;j<i;j++)
		all_students[j].grade = grader(all_students, j, length, answer_key);
	
	for (int j=0; j<i;j++)
	{
		all_students[j].grade_letter = letter_grader(all_students[j].grade);
	}
	for(int j=0; j < i; j++)
		printer(all_students, j, length, answer_key);
	
	for(int j=0;j<i;j++)
	{
		sum +=all_students[j].grade;
	}
	average = sum / i;
	
	cout << endl << "Class average: " << average << " " << letter_grader(average) << endl;	
	best_score(all_students, i);
	
}

//Functions below
void getFileNames(string &inFileName)
{
	cout << "Please provide the input file name: ";
	cin >> inFileName;
}

void get_student_info(ifstream& inFile, Student all_students[], int i)
{
	inFile >> all_students[i].first_name >> all_students[i].last_name;
	getline(inFile, all_students[i].answers);
}

double grader(Student all_students[], int i, int length, string answer_key)
{
	double score = 0;
	double correct = 0;
	for(int j = 0; j < (length + 1); j++)
	{
		all_students[i].answers[j] = tolower(all_students[i].answers[j]);
		
		if(all_students[i].answers[j] == answer_key[j-1])
			correct ++;
	}
	return score = 100 * (correct / length);
}

void printer(Student all_students[], int i, int length, string answer_key)
{
	int count = 0;
	
	cout << endl << all_students[i].first_name << " " << all_students[i].last_name << endl;
	cout << "__________________________________________________________________________" << endl;
	cout << "Answers, correct answers in parenthesis" << endl << endl;
	for(int j = 1; j <= length;j++)
	{	
		cout << setw(4) << j << ": " << all_students[i].answers[j] << "(" << answer_key[j-1] << ") ";
		count++;
		if(count == 5)
		{
			cout << endl;
			count = 0;
		}
	}
	cout << "Score: " << all_students[i].grade << "% " << all_students[i].grade_letter << endl;
	cout << "__________________________________________________________________________" << endl << endl;
	
}

char letter_grader(double i)
{
	if(i <= 100 && i >= 90)
		return 'A';
	else if(i < 90 && i >= 80)
		return 'B';
	else if(i < 80 && i >= 70)
		return 'C';
	else if(i < 70 && i >= 60)
		return 'D';
	else 
		return 'F';
}

void best_score(Student all_students[], int i)
{	
	double high_score[100];
	high_score[0] = all_students[0].grade;
	string first_name[100]; 
	first_name[0] = all_students[0].first_name;
	string last_name[100];
	last_name[0] = all_students[0].last_name;
	
	for(int j= 0;j<i;j++)
	{
		if(high_score[0] < all_students[j+1].grade)
		{
			high_score[0] = all_students[j+1].grade;
			first_name[0] = all_students[j+1].first_name;
			last_name[0] = all_students[j+1].last_name;
		}
	}
	
	int m=0;
	for(int k = 0; k<i; k++)
	{
		if(high_score[0] == all_students[k].grade)
		{
			first_name[m] = all_students[k].first_name;
			last_name[m] = all_students[k].last_name;
			m++;			
		}
	}
	
	cout << "Student(s) with the highest grade (" << high_score[0] << "):" << endl;
	for(int n=0;n<m;n++)
		cout << first_name[n] << " " << last_name[n] << endl;
}
