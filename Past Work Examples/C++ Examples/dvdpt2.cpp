/*
Mark Brown
30/11/2015
Description: Design claess, search strings, tokenizing strings, and separate compilation - Part 2
*/

#include <iostream>//for use of cout and cin 
#include <fstream>//need this for input, output file
#include <string>//need for converting numerical value into string, and for string functions
#include <algorithm>//need this for transform function
#include <sstream>//used to stream a string into another string
#include "DVD.h"
#include "DVD.cpp"


using namespace std;

class DVDLibrary
{
public:
	DVDLibrary();
	
	//void search_title(string title);
	//void search_actor(string actor);
	//void search_year(int year);
	//void search(string target);
	//int get_numDVDs();
	//void add_DVD(string title, int year, string actor);
	/*void save();
	void remove_DVD(string exact_title);*/
	
	//friend ostream& operator <<(ostream &out, const DVDLibrary library);
	
private:
	void get_data();
	int count;
	DVD dvd[100];
};

void display_menu();

int main(int argc, char const *argv[])
{
	DVDLibrary library;
	string actor, title, search_string;
	int year, choice;
	do
	{
		display_menu();
		cin >> choice;
		cin.ignore(100, '\n');

		switch(choice){
			case 1:	
			//cout << library << endl;
			break;
			
			case 2:
			{
				cout << "Enter a title: ";
				getline(cin, title);
				//library.search_title(title);
				break;
			}
			case 3:
			{
				cout << "Enter an actor: ";
				getline(cin, actor);
				//library.search_actor(actor);
				break;
			}
			case 4:
			{
				cout << "Enter a year: ";
				cin >> year;
				cin.ignore(100, '\n');
				//library.search_year(year);
				break;
			}
			case 5:
			{
				cout << "Enter an search string: ";
				getline(cin, search_string);
				//library.search(search_string);
				break;
			}
			case 6:
			{
				cout << "Enter a title: ";
				getline(cin, title);
				cout << "Enter a year: ";
				cin >> year;
				cin.ignore(100, '\n');
				cout << "Enter an actor name: ";
				getline(cin, actor);
				//library.add_DVD(title, year, actor);
				break;
			}
			case 7:
			{
				cout << "Enter the DVD title to remove: ";
				getline(cin, title);
				//library.remove_DVD(title);
				break;
			}
			case 8:
			{
				//library.save();
				cout << "Library saved..." << endl;
				break;
			}
			case 9:
			{
				cout << "Changes are not saved..." << endl;
				break;
			}
			default:
				cout << "Illegal choice.";
		}
	} while (choice != 9);


	return 0;
}

void display_menu(){
	cout << "1. Display all DVDs" << endl
	<< "2. Search by title" << endl
	<< "3. Search by actor" << endl
	<< "4. Search by year" << endl
	<< "5. Match anything" << endl
	<< "6. Add DVD" << endl
	<< "7. Remove DVD" << endl
	<< "8. Quit and Save DVDs" << endl
	<< "9. Quit and Ignore changes" << endl
	<< "Enter a choice: ";
}


DVDLibrary::DVDLibrary ()
{
	get_data();
}

void DVDLibrary::get_data()
{
	ifstream inFile;
	inFile.open("Library.txt");
	if (inFile.fail())//fail testing the files
	{
		cout << "Error opening file. Exiting program.";
		exit(1);
	}
	
	string dvd_line;
	do {
		getline(inFile, dvd_line);
		DVD dvd1(dvd_line);
		dvd[count].set_title(dvd1.get_title());
		dvd[count].set_year(dvd1.get_year());
		dvd[count].set_actor(dvd1.get_actor());
		count++;
	}	while (!inFile.eof());
	
	
	inFile.close();
}

/*void DVDLibrary::search_title(string title)
{	
	for(int i; i < count; i++)
	{
		bool found = dvd[i].match_title(title);
		if(found == true)
		{
			cout << dvd[i].get_title() << ", " << dvd[i].get_year() << ", " << dvd[i].get_actor() << endl;
		}
	}
}
void DVDLibrary::search_actor(string actor)
{
	for(int i; i < count; i++)
	{
		bool found = dvd[i].match_actor(actor);
		if(found == true)
		{
			cout << dvd[i].get_title() << ", " << dvd[i].get_year() << ", " << dvd[i].get_actor() << endl;
		}
	}
}
void DVDLibrary::search_year(int year)
{
	for(int i; i < count; i++)
	{
		bool found = dvd[i].match_year(year);
		if(found == true)
		{
			cout << dvd[i].get_title() << ", " << dvd[i].get_year() << ", " << dvd[i].get_actor() << endl;
		}
	}
}
void DVDLibrary::search(string target)
{
	for(int i; i < count; i++)
	{
		bool found = dvd[i].match(target);
		if(found == true)
		{
			cout << dvd[i].get_title() << ", " << dvd[i].get_year() << ", " << dvd[i].get_actor() << endl;
		}
	}
}*/
/*int DVDLibrary::get_numDVDs()
{
	return count;
}*/
/*void DVDLibrary::add_DVD(string title, int year, string actor)
{
	count++;
	dvd[count].set_title(title);
	dvd[count].set_year(year);
	dvd[count].set_actor(actor);
}*/
/*void DVDLibrary::save()
{
	
}
void DVDLibrary::remove_DVD(string exact_title)
{
	
}*/

/*ostream& operator <<(ostream &out, const DVDLibrary library)
{
	for(int i=0 ; i < library.count; i++)
	{	
		out << "(Title: " << ", Year: "  << ", Actor: "  << ")" << endl;
	}
	return out;
}*/
