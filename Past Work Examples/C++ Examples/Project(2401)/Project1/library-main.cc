/*
Mark Brown
28/01/2016
This program is designed store all the data from 200 different books. It can sort the 
books, search the books by title or author. After closing the menu it saves the data.
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include "book.h"
#include "library.h"

using namespace std;

void menu(Library& mylibrary);//menu

//beginning of program
int main ()
{
	Library mylibrary;
	ifstream fin;
	fin.open("books.txt");//opens the file
	
	if (!fin.fail()){
		mylibrary.load_from_file(fin);//loads from the file
		fin.close();
		menu(mylibrary);
		
	}
	else
		menu(mylibrary);//skips if nothing is in the file
	
	ofstream outs;
	outs.open("books.txt");//saves to the file shown there
	mylibrary.save_to_file(outs);
	outs.close();
	
	
	return EXIT_SUCCESS;
}
void menu(Library& mylibrary){
	int num;
	string target;
	Book tmp;
	
	cout << "Welcome to your digitial book storage." << endl;
	while(num !=9){
	cout << "Below you will find the options and their corresponding number to type for said option." << endl;
	cout << "1. Add a book to your digitial collection" << endl
		 << "2. Output total number of pages between all stored books" << endl
		 << "3. Output your stored books in list form" << endl
		 << "4. Sort your collection via title" << endl
		 << "5. Sort your collection via author" << endl
		 << "6. Search for a book by title" << endl
		 << "7. Search for books by a particular author" << endl
		 << "8. Remove a book from the collection" << endl
		 << "9. Quit" << endl;
	
	cin >> num;
	 switch (num){
		case 1:
			if (cin.peek() == '\n')
				cin.ignore();
			cin >> tmp;
			mylibrary.add_book(tmp);
			break;
		case 2:
			mylibrary.output_pages();
			break;
		case 3:
			mylibrary.output_list();
			break;
		case 4:
			mylibrary.sort_title();
			break;
		case 5:
			mylibrary.sort_copyright();
			break;
		case 6:
			cout << "What title are you searching for?";
			if (cin.peek() == '\n')
				cin.ignore();
			getline(cin,target);
			mylibrary.search_title(target);
			break;
		case 7:
			cout << "What is the name of the author you want to search?";
			if (cin.peek() == '\n')
				cin.ignore();
			getline(cin,target);
			mylibrary.search_authors(target);
			break;
		case 8:
			cout << "What is the title of the book you wish to erase?";
			if (cin.peek() == '\n')
				cin.ignore();
			getline(cin,target);
			mylibrary.remove_book(target);
			break;
		case 9:
			cout << "(saving your data) Thank you, have a nice day." << endl;
			break;
		default :
			cout << "Sorry invalid entry. Try again." << endl;
			break;
		}
	}
}


