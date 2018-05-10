//Test program: Polynomial Operations

#include <iostream>

#include "polynomialType.h"

using namespace std;

int main()
{
	polynomialType p(3);                            //Line 1
	polynomialType q(2);                            //Line 2
	polynomialType t;                               //Line 3

	cin >> p;                                       //Line 4
	cout << endl << "Line 5: p(x): " << p << endl;  //Line 5

	cout << "Line 6: p(5): " << p(5) << endl;       //Line 6
	
	cin >> q;                                       //Line 7
	cout << endl << "Line 8: q(x): " << q << endl;  //Line 8

	t = p + q;                                      //Line 9

	cout << "Line 10: p(x) + q(x): " << t << endl;  //Line 10
	
	cout << "Line 11: p(x) - q(x): " << p - q << endl;  //Line 11

	cout << "Line 12: p(x) * q(x): " << p * q << endl;  //Line 12

	cout << "Line 13: p'(x): " << ~p << endl;       //Line 13

	return 0;
}
