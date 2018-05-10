/*
* Mark Brown
* 04/04/2016
* The program is designed to supply "homes" for animals using the list container with pointers.
* The basic idea is to demanstrate polymorphism containers.
*/

#include <string>
#include <iostream>
#include <fstream>


#ifndef HOMES_H
#define HOMES_H

class homes{//parent class (homes) used to house the connection to the child classes
	public:
		homes();
		virtual void input()=0;
		virtual void output(std::ostream& outs){};
	private:
		double price;
};

class charmander:public homes{//charmander child class
	public:
		charmander();
		charmander(std::istream& ins);
		void input();
		void output(std::ostream& outs);
	private:
		double width, length, base;
		bool bed,lavaPool,mailbox;
		std::string material, post_code,post_region;
};

class bulbasaur:public homes{//bulbasaur child class
	public:
		bulbasaur();
		bulbasaur(std::istream& ins);
		void input();
		void output(std::ostream& outs);
	private:
		double feed_lbs, length, width;
		int id_num;
		std::string colourL,favPark;
};


class squirtle:public homes{//squirtle child class
	public:
		squirtle();
		squirtle(std::istream& ins);
		void input();
		void output(std::ostream& outs);
	private:
		double card_limit;
		int pin;
		bool glasses, crew;
		std::string phone_num;
};

class pidgey:public homes{//pidgey child class
	public:
		pidgey();
		pidgey(std::istream& ins);
		void input();
		void output(std::ostream& outs);
	private:
		double radius, tree_height;
		char item1, item2;
		std::string tree_type, mig_loc;
		bool gps, call;
};

class caterpie:public homes{//caterpie child class
	public:
		caterpie();
		caterpie(std::istream& ins);
		void input();
		void output(std::ostream& outs);
	private:
		double ip_tele;
		char item;
};

class arcanine:public homes{//arcanine child class
	public:
		arcanine();
		arcanine(std::istream& ins);
		void input();
		void output(std::ostream& outs);
	private:
		double base, peak, height, width;
		bool namePlate, firePit, perAst;
		std::string nickName, post_code, post_region;
};

#endif
