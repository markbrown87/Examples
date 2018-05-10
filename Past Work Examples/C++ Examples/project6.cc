#include <iostream>
#include <string>
#include <vector>


using namespace std;

//container holding the string (city) and the integers (distance)
struct Matrix{
	public:
		Matrix() {};
		void input();
		void display();
		//void calculator();
	private:
		vector<string> city;
		vector<string> product;
		int matDist[100][100];
		int numCity;
};



int main () {
	int space, checker;
	cin >> space;
	checker = space;
	
	Matrix container[space];
	
	for(int i = 0; i < checker; i++){
		container[i].input();
		//container[i].calculate();
		container[i].display();
	}
	
	return 0;
}

void Matrix::input(){
	int space;
	string tmp;
	
	cin >> space;
	numCity = space;
	cin.ignore();
	
	for (int i = 0; i < numCity; ++i){
		getline(cin, tmp);
		city.push_back(tmp);
	}
	for (int i = 0; i < numCity; ++i){
		for(int j = 0; j < numCity; ++j)
			cin >> matDist[i][j];
		cin.ignore();
	}
}

void Matrix::calculate(){
	/*
	fake code:
		Source or point of source is always the first city listed. 
		Destantion is always last city
		Anything that has a zero is not connected.
			Anything connected has a weight.
		Pick the shorted distance between connections.
			Then make the next locations the source and turn the previous source to 0.
			Add the previous source to the product for displaying.
		Repeat until source == destantion (spelled wrong).
	*/
}

void Matrix::display(){
	for (vector<string>::const_iterator i = product.begin(); i != product.end(); ++i)
		cout << *i << ' ';
}