//Created by Mark Brown on 28/01/2016

#include<iostream>
#include<string>
#include "book.h"

#ifndef LIBRARY_H
#define LIBRARY_H

class Library{
	public: 
		Library();
		void load_from_file(std::istream& ins);//loads the books from a file
		void save_to_file(std::ostream& outs);//save the books to a file
		void add_book(const Book tmp);//adds a book
		void output_pages();//outputs the total number of books
		void output_list()const;//lists all the books
		void remove_book(std::string target);//removes a book from the collection
		void sort_title();//sorts by title
		void sort_copyright();//sorts by coypright year
		void search_title(std::string target);//searchs by title
		void search_authors(std::string target);//searchs by author
		static const std::size_t CAPACITY = 200;//sets the array of books to a limit of 200
		
	private:
		Book books[CAPACITY];
		std::size_t used;//keeps track of all the used positions within the array of books
};
#endif
