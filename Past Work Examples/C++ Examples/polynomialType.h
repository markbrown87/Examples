 
#ifndef H_polynomial
#define	H_polynomial

#include <iostream>
#include "arrayListType.h"

using namespace std;

class polynomialType: public arrayListType<double>
{
	friend ostream& operator<<(ostream&, const polynomialType&);
		//overload stream insertion operator
	friend istream& operator>>(istream&, polynomialType&);
		//overload stream extraction operator
public:
	polynomialType operator+(const polynomialType&);
		//overload the operator +
	polynomialType operator-(const polynomialType&);
		//overload the operator -

	polynomialType operator*(const polynomialType&);
		//overload the operator *
	
	polynomialType operator~();
		//overload the operator~

	double operator() (double x);
		//overload the operator () to evaluate the
		//polynomial at a given point
		//Postcondition: The value of the plynomial at x
		//		         is calculated and returned
	
	polynomialType(int size = 100);
		//constructor
	
	double evaluate(double x);
		//Function to evaluate a poynomial at a given
		//point

	int min(int x, int y) const;
		//Function to return the smaller of x and y
	int max(int x, int y) const;
		//Function to return the larger of x and y
};

#endif

