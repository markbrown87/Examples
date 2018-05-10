/*
Mark Brown
03/12/2015
This program is designed 
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
	//void output();
	//double price(int r, int h, double g, string t) const;

	friend ostream& operator <<(ostream &out, const Computer &computer);
	friend istream& operator >>(istream &in, Computer &computer);
	friend bool operator ==(Computer &computer1, Computer &computer2);
	friend bool operator <(Computer &computer1, Computer &computer2);
	
private:
	//private variables
	int ram;
	int hd;
	double speed_ghz;
	string type;

	double price(int r, int h, double g, string t) const;
};

//beginning of program
int main ()
{
	

	Computer comp; //use default constructor
	Computer comp1(16, 1000, 1.6, "Laptop");
	cout << comp << endl; //output defaults
	cout << endl;
	cout << comp1 << endl;
	cout << endl;

	comp1.set_ram(32);
	comp1.set_hd(2000);


	cout << "The computer ram was changed to " << comp1.get_ram() << endl;
	cout << "The computer hd was changed to " << comp1.get_hd() << endl << endl;
	cout << "Updated info" << endl << endl;
	cout << comp1 << endl;
	cout << endl;
	comp1.set_type("Desktop");
	cout << "Computer type was changed to Desktop" << endl;
	cout << comp1 << endl;

	Computer comp2;
	cout << "Enter specs of a computer (Ram, HD, Speed, Type)" << endl;
	cin >> comp2;
	cout << comp2 << endl;
	if (comp1 < comp2)
	{
		cout << "Computer 2 is more expensive" << endl;
	}
	if (comp1 == comp2)
	{
		cout << "comp1 and comp2 have the same specifications" << endl;
	}

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

double Computer::price(int r, int h, double g, string t) const//function used to calculate price
{
	if (t == "Laptop")
	{
		return (600.00 + (r * 5.00) + (h * .15) + ((g - 1.6)*200));
	}
	else
		return (400.00 + (r * 4.00) + (h * .10) + ((g - 1.6)*200));
}

/*void Computer::output()//the output
{
	cout << fixed << showpoint;
	cout.precision(2);

	cout << "Computer: " << type << endl;
	cout << "RAM:      " << ram << "GB" << endl;
	cout << "H. Drive: " << hd << "GB" << endl;
	cout << "Speed:    " << speed_ghz << "GHz" << endl;
	cout << "Price:   $" << price(ram, hd, speed_ghz, type) << endl;
}*/

ostream& operator <<(ostream &out, const Computer &computer)
{
	out << "Computer: " << computer.type << endl;
	out << "RAM:      " << computer.ram << "GB" << endl;
	out << "H. Drive: " << computer.hd << "GB" << endl;
	out << "Speed:    " << computer.speed_ghz << "GHz" << endl;
	out << "Price:   $" << computer.price(computer.ram, computer.hd, computer.speed_ghz, computer.type) << endl;

	return out;
}

istream& operator >>(istream &in, Computer &computer)
{
	in >> computer.ram >> computer.hd >> computer.speed_ghz >> computer.type;
	
	return in;
}

bool operator ==(Computer &computer1, Computer &computer2)
{
	if (computer1.hd == computer2.hd && computer1.ram == computer2.ram && computer1.speed_ghz == computer2.speed_ghz && computer1.type == computer2.type)
		return true;
	else
		return false;
}

bool operator <(Computer &computer1, Computer &computer2)
{
	if (computer1.price(computer1.ram, computer1.hd, computer1.speed_ghz, computer1.type) < computer2.price(computer2.ram, computer2.hd, computer2.speed_ghz, computer2.type))
		return true;
	else
		return false;
}




