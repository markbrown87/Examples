# include <iostream>
#include <string>

using namespace std;

int main()
{
	double n, c = 0;
	double i = 0, k = 5;
	//a comment
	cout << "Enter a positive integer: ";
	cin >> n >> i;
	if(n < 0 && n == true)
	{
		cout << "Must be pos\n";
	}
	while(i < n)
	{
		n *= i;
		++i;
	}
	cout << "Factorial of " << n << " = " << fact << endl;

	return EXIT_SUCCESS;
}