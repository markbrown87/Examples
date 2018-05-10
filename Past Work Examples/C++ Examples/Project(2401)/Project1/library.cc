//Created by Mark Brown on 28/01/2016

#include<iostream>
#include<string>
#include "library.h"

using namespace std;

Library::Library(){
	used = 0;
}
void Library::add_book(const Book tmp)//adds a book
{
	books[used] = tmp;
	++used;
	
}
void Library::output_pages(){//outputs the total number of books
	int tmp = 0;
	for (size_t i = 0; i < used; i++)
	{
		tmp += books[i].get_pages();
	}
	cout << tmp << " pages in total." << endl;
}
void Library::output_list()const{//lists all the books
	for (size_t i =0;i<used;i++)
		cout << books[i];
}
void Library::load_from_file(istream& ins){//loads the books from a file
	Book tmp;

	while(ins >> tmp)
		add_book(tmp);
}
void Library::save_to_file(ostream& outs){//save the books to a file
	for (size_t i = 0;i < used;i++)
		outs << books[i];
}
void Library::search_title(string target){//searchs by title
	bool fd = false;
	for(size_t i =0;i <used;i++){
		if(target==books[i].get_title()){
			cout << books[i];
			fd = true;
		}
	}
	if (!fd)
		cout << "Sorry but no title match was found." << endl;
}
void Library::search_authors(string target){//searchs by author
	bool fd = false;
	for(size_t i =0;i <used;i++){
		if(target==books[i].get_author()){
			cout << books[i];
			fd = true;
		}
	}
	if (!fd)
		cout << "Sorry but no author match was found." << endl;
}
void Library::remove_book(string target){//removes a book from the collection
	size_t i=0;
	
	while(i<used&&books[i].get_title()!=target)
		++i;
	if(i<used){
		books[i]=books[used-1];
		used--;
	}
}
void Library::sort_title(){//sorts by title
	bool done = false;
	Book tmp;
	while(!done){
		done = true;
		for(size_t i=0;i<used-1;i++){
			if(books[i].get_title() > books[i+1].get_title()){
				done = false;
				tmp = books[i];
				books[i] = books[i+1];
				books[i+1]=tmp;
			}
		}
	}
}
void Library::sort_copyright(){//sorts by copyright year
	bool done = false;
	Book tmp;
	while(!done){
		done = true;
		for(size_t i=0;i<used-1;i++){
			if(books[i].get_copyright() > books[i+1].get_copyright()){
				done = false;
				tmp = books[i];
				books[i] = books[i+1];
				books[i+1]=tmp;
			}
		}
	}
}
