/*
* Mark Brown
* 04/01/2016
* The program is designed to take input regarding the dimensions of either a circle, rectangle, or trapizoid
* then output the price depending on the cubic dimensions.
*
*/

#include <iostream>
#include <string>
#include <cmath>


class Shape{
	public:
		Shape(){thickness = 1; cost_per = 1;}; //set the default to 1's
		double cost()
		{std::cout << "Please provide cubic cost(default is 1$ per cubic measurement): ";
		 std::cin >> cost_per;
		 return thickness*cost_per*area();};//asks for the cost per cubic measurement then outputs the values
		virtual double area()=0;//purely virtual functions used to access child's function
		virtual void input()
		{std::cout << "Please provide thickness: ";
		 std::cin >> thickness;
		 std::cout << "Now the cost_per: ";
		 std::cin >> cost_per;};
		
	private:
		double thickness;
		double cost_per;
};

class Circle:public Shape{
	public:
		Circle(){radius = 0;};
		double area(){return M_PI*radius*radius;};
		void input()
		{std::cout << "Please input the radius: ";
		 std::cin >> radius;};
	private:
		double radius;
};

class Rectangle:public Shape{
	public:
		Rectangle(){length = 0; width = 0;};
		double area(){return length*width;};
		void input()
		{std::cout << "Please input the length: ";
		 std::cin >> length;
		 std::cout << "Now input the width: ";
		 std::cin >> width;};
	private:
		double length, width;
};

class Trapezoid:public Shape{
	public:
		Trapezoid(){base1=0; base2=0;height=0;};
		double area(){return height*(base1+base2)/2.0;}
		void input()
		{std::cout << "Please input the base1: ";
		 std::cin >> base1;
		 std::cout << "Now input the base2: ";
		 std::cin >> base2;
		 std::cout << "Finally, input the height: ";
		 std::cin >> height;};
	private:
		double base1, base2, height;
};

//functions found below