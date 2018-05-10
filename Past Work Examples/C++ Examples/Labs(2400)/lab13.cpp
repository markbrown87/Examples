/*
Mark Brown
19/11/2015
This program is designed to describe a computer's objects (ram, hd size, speed, type (laptop desktop)).
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;

class Computer{
public:
	//constructors
	Computer();
	Computer(int r, int h, double g, string t);

	//setters
	void set_ram(int r);
	void set_hd(int h);
	void set_speed(double g);
	void set_type(string t);

	//getters
	int get_ram();
	int get_hd();
	double get_speed();
	string get_type();
	void output();
	
private:
	//private variables
	int ram;
	int hd;
	double speed_ghz;
	string type;

	//private function
	double price(int r, int h, double g, string t);
};

//beginning of program
int main ()
{
	

	Computer comp; //use default constructor
	Computer comp1(16, 1000, 1.6, "Laptop");
	comp.output(); //output defaults
	cout << endl;
	comp1.output();
	cout << endl;

	comp1.set_ram(32);
	comp1.set_hd(2000);

	//int comp_ram = comp1.get_ram();
	cout << "The computer ram was changed to " << comp1.get_ram() << endl;
	cout << "The computer hd was changed to " << comp1.get_hd() << endl << endl;
	cout << "Updated info" << endl << endl;
	comp1.output();
	cout << endl;
	comp1.set_type("Desktop");
	cout << "Computer type was changed to Desktop" << endl;
	comp1.output();
	return 0;
}




Computer::Computer()//default constructor
{
	ram = 8;
	hd = 500;
	speed_ghz = 1.6;
	type = "Desktop";
}

Computer::Computer(int r, int h, double g, string t)//constructor to set all variables
{
	ram = r;
	hd = h;
	speed_ghz = g;
	type = t;
}

void Computer::set_ram(int r)//setter for ram
{
	ram = r;
}

void Computer::set_hd(int h)//setter for hd
{
	hd = h;
}

void Computer::set_speed(double g)//setter for speed
{
	speed_ghz = g;
}

void Computer::set_type(string t)//setter for type
{
	type = t;
}

int Computer::get_ram()//getter for ram
{
	return ram;
}

int Computer::get_hd()//getter for hd
{
	return hd;
}

double Computer::get_speed()//getter for speed
{
	return speed_ghz;
}

string Computer::get_type()//getter for type
{
	return type;
}

double Computer::price(int r, int h, double g, string t)//function used to calculate price
{
	if (t == "Laptop")
	{
		return (600.00 + (r * 5.00) + (h * .15) + ((g - 1.6)*200));
	}
	else
		return (400.00 + (r * 4.00) + (h * .10) + ((g - 1.6)*200));
}

void Computer::output()//the output
{
	cout << fixed << showpoint;
	cout.precision(2);

	cout << "Computer: " << type << endl;
	cout << "RAM:      " << ram << "GB" << endl;
	cout << "H. Drive: " << hd << "GB" << endl;
	cout << "Speed:    " << speed_ghz << "GHz" << endl;
	cout << "Price:   $" << price(ram, hd, speed_ghz, type) << endl;
}
