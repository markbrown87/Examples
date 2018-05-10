//By Mark Brown and created on 10/02/2016

#include <iostream>
#include <cstdlib>

class Numbers{
	public:
		Numbers();
		void add(unsigned long var);
		void resize();
		void remove_last();
		void display();
	private:
		unsigned long *data;
		std::size_t used;
		std::size_t capacity;
};
