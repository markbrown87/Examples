/*
* Mark Brown
*	11/04/2016
* Description: header file that houses the data for the space on the board
*
*/

#ifndef SPACES_H
#define SPACES_H

class spaces{
	public:
		int is_space()const{return item;};
		void set_space(int a){item = a;};
		bool is_red()const{return item == 0;};
		bool is_black()const{return item == 1;};
		bool is_eking()const{return item ==4;};
		bool is_gking()const{return item == 5;};
		bool is_good()const{return item == 3;};
		bool is_evil()const{return item == 2;};
		
	private:
		/*
		Table of contends for personal reference:
		
		
		0 = RED
		1 = BLACK
		2 = EVIL
		3 = GOOD
		4 = KING->EVIL
		5 = KING->GOOD
		*/
		int item;
};



#endif