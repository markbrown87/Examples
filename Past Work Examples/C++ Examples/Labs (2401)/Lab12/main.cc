/*
* Mark Brown
*	->14/04/2016
* Description: The program is designed to use recursion and become more fimiliar with recurive functions
*
*/

#include <iostream>
#include <string>


using namespace std;

int counting(int n);
string reversing(string& s, int start, int end);

int main(){
	int x;
	for(int j=0;j<3;++j){
		cout <<"Enter a number: ";
		cin>>x;
		cout<<"The even numbers counting to there:\n";
		counting(x);
		cout << endl;
	}
	//main for part two will go here
	string s;
	int start, end;
	cout<<"Enter a string: ";
	if(cin.peek() == '\n')
		cin.ignore();
	getline(cin, s);
	cout<<"Now enter two numbers that are within the bounds of the string: ";
	cin >> start>> end;
	cout <<"This is how your words look now:\n";
	reversing(s, start, end);
	cout << s <<endl;
	return 0;
}

int counting (int n){
	if(n < 0) return 0;
	if(n == 0){
		cout << n << " ";
		return 0;
	}
	if(n%2 ==0){
		counting(n - 2);
		cout << n << " ";
		return n;
	}
	if(n%2 != 0){
		counting(n - 1);
		return n;
	}
}

string reversing(string& s, int start, int end){
	char holder;
	if(start >= end) return s;
	if(start < end){
		holder = s[start];
		s[start] = s[end];
		s[end]=holder;
		reversing(s,(start+1), (end-1));
		return s;
	}	
}