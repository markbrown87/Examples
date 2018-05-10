/*
Mark Brown
19/11/2015
Description: Design claess, search strings, tokenizing strings, and separate compilation
*/

#include <iostream>//for use of cout and cin 
#include <fstream>//need this for input, output file
#include <string>//need for converting numerical value into string, and for string functions
#include <algorithm>//need this for transform function
#include <sstream>//used to stream a string into another string
#include "dvd.h"

using namespace std;

//contructors
DVD::DVD()
{
	title = "";
	year = 1800;
	actor = "";
}

DVD::DVD(string new_title, int new_year, string new_actor)
{
	title = new_title;
	year = new_year;
	actor = new_actor;
}

DVD::DVD (string all_data)
{
	string new_title;
	string step;
	int new_year;
	
	double breaker = all_data.find('|');
	for(int i = 0; i < breaker; i++)
	{
		new_title +=all_data[i];
	}
	title = new_title;
	all_data.erase(0, breaker + 1);
	
	breaker = all_data.find('|');
	for(int i = 0; i < breaker; i++)
	{
		step +=all_data[i];
	}
	istringstream stg (step);
	stg >> new_year;
	year = new_year;
	all_data.erase(0, breaker + 1);
	
	actor = all_data;
}

//getters
void DVD::set_title(string new_title)
{
	title = new_title;
}

void DVD::set_year(int new_year)
{
	year = new_year;
}

void DVD::set_actor(string new_actor)
{
	actor = new_actor;
}

//setters
string DVD::get_title()
{
	return title;
}

int DVD::get_year()
{
	return year;
}

string DVD::get_actor()
{
	return actor;
}

//helpers
bool DVD::match_title (string target_title)//search for title
{
	if(target_title == "" || target_title == " ") //safe guard against 'finding' a blank ("") or a space (" ")
		return false;
	
	string lower_title = title;
	
	transform(target_title.begin(), target_title.end(), target_title.begin(), ::tolower); 
	transform(lower_title.begin(), lower_title.end(), lower_title.begin(), ::tolower); 

	int found = lower_title.find(target_title);
	
	if (found > -1)
		return true;
	else
		return false;
}

bool DVD::match_year (int target_year)//search for year
{
	string t_year = to_string(target_year);
	string s_year = to_string(year);
	
	int found = s_year.find(t_year);
	
	if (found > -1)
		return true;
	else
		return false;
}

bool DVD::match_actor (string target_actor)//search for actor
{
	if(target_actor == "" || target_actor == " ")//safe guard against 'finding' a blank ("") or a space (" ")
		return false;
	
	string lower_actor = actor;
	
	transform(target_actor.begin(), target_actor.end(), target_actor.begin(), ::tolower); 
	transform(lower_actor.begin(), lower_actor.end(), lower_actor.begin(), ::tolower); 

	int found = lower_actor.find(target_actor);
	
	if (found > -1)
		return true;
	else
		return false;
}

bool DVD::match (string target)//search for any
{
	if(target == "" || target == " ")//safe guard against 'finding' a blank ("") or a space (" ")
		return false;
	
	string lower_title = title;
	string lower_actor = actor;
	string s_year = to_string(year);
	
	transform(target.begin(), target.end(), target.begin(), ::tolower); 
	transform(lower_title.begin(), lower_title.end(), lower_title.begin(), ::tolower); 
	transform(lower_actor.begin(), lower_actor.end(), lower_actor.begin(), ::tolower);

	int f_title = lower_title.find(target);
	int f_actor = lower_actor.find(target);
	int f_year = s_year.find(target);
	
	if (f_title > -1)
		return true;
	else if (f_actor > -1)
		return true;
	else if (f_year > -1)
		return true;
	else
		return false;
}

//output
void DVD::output()
{
	cout << "(Title: " << title << ", Year: " << year << ", Actor: " << actor << ")" << endl;
}
