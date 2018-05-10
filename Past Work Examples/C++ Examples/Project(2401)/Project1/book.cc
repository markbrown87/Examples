/*****************************************************
	This is the implementation file for the book class declared in
	book.h
	    John Dolan Ohio University January 2016 
********************************************************/
#include<iostream> 
#include<string>
#include "book.h"

using namespace std;
 Book::Book(){
   pages = 0;
   year = 1454; //Date of the first Gutenberg Bible
}
string Book::get_title(){return title;}
string Book::get_author(){return author;} 
int Book::get_copyright(){return year;}
int Book::get_pages(){return pages;} 
// STUDENT IS REQUIRD TO WRITE THE IMPLEMENTATION OF THIS FUNCTION 
void Book::input(istream& ins){
    if(&ins == &cin){
	// input will be coming from the keyboard
		cout << "Please provide the title: ";
		if (cin.peek() == '\n')
			cin.ignore();
		getline(cin, title);
		cout << "Please provide the author: ";
		if (cin.peek() == '\n')
			cin.ignore();
		getline(cin, author);
		cout << "Please provide the year of the book: ";
		if (cin.peek() == '\n')
			cin.ignore();
		cin >> year;
		cout << "Finally, please provide the number of pages: ";
		if (cin.peek() == '\n')
			cin.ignore();
		cin >> pages;
    }
    else{
	//input will be coming from a file
		getline(ins, title);
		getline(ins, author);
		ins >> year;
		ins.ignore();
		ins >> pages;
		ins.ignore();
    }
}
// STUDENT IS REQUIRD TO WRITE THE IMPLEMENTATION OF THIS FUNCTION 
void Book::output(ostream& outs)const{
    if(&outs == &cout){
	//output is being written to the console
		cout << "Title: " << title << endl << "Author: " << author << endl;
		cout << "Year: " << year << endl << "Number of pages: " << pages << endl;
    }
    else{
	//output is being written to a file
		outs << title << endl << author << endl << year << endl << pages << endl;
    }
}
istream& operator >>(istream& ins, Book& b1){
    b1.input(ins);
    return ins;
}
ostream& operator <<(ostream& outs, const Book& b1){
    b1.output(outs);
    return outs;
}
