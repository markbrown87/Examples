/*
Mark Brown
30/11/2015
Description: Design claess, search strings, tokenizing strings, and separate compilation
*/

#ifndef DVD_H
#define DVD_H
using namespace std;

//class
class DVD{
public:
	//constructors
	DVD();
	DVD(string new_title, int new_year, string new_actor);
	DVD(string all_data);
	
	//setters
	void set_title(string new_title);
	void set_year(int new_year);
	void set_actor(string new_actor);
	
	//getters
	string get_title();
	int get_year();
	string get_actor();
	
	//helpers
	bool match_title (string target_title);
	bool match_year (int target_year);
	bool match_actor (string target_actor);
	bool match (string target);
	
	//output
	void output();
	
private:
	string title;
	int year;
	string actor;
};

#endif
