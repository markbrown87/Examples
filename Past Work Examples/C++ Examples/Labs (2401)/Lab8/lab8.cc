/*
* Created by Mark Brown
* Date: 16/03/2016
* Description: This lab is designed to get the basic understanding of multiset
* how to work with external iterators
*
*/


#include <set>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;



int main(){
	multiset<string> names;//declared an array of strings
	string tmp;
	int count = 0;
	//opening the file
	ifstream fin;
	fin.open("names.txt");
    if(!fin.fail()){
		fin >> tmp;
		names.insert(tmp);
		while (fin >> tmp){
			names.insert(tmp);
		}
	}
	else 
		cout << "failure to open";
	fin.close();
	//declaring forward iterator (f_it) and reverse iterator (r_it)
	multiset<string>::iterator f_it, r_it;
	//inputing the list of names into the names multiset
	for(f_it = names.begin(); f_it != names.end(); ++f_it){
		cout << *f_it << " ";
	}
	cout << endl;
	
	//iterates through the list until M and then begins counting
	for(f_it = names.begin(); (*f_it).at(0) != 'M';++f_it);
	r_it = f_it;
	for(;(*r_it).at(0) != 'N'; r_it++)
		count++;
	//outputing the names in reverse
	cout << "There are " << count << " M names in the list.\n";
	cout << "They are: ";
	while(r_it != f_it){
		--r_it;
		cout << *r_it << " ";
	}
	cout << endl;
	
	count = 0;
	//iterates through the list until C and then begins counting
	for(f_it = names.begin(); (*f_it).at(0) != 'C';++f_it);
	r_it = f_it;
	for(;(*r_it).at(0) != 'D'; r_it++)
		count++;
	//outputing the names in reverse
	cout << "There are " << count << " C names in the list.\n";
	cout << "They are: ";
	while(r_it != f_it){
		--r_it;
		cout << *r_it << " ";
	}
	cout << endl;
	
	count = 0;
	//iterates through the list until Q and then begins counting
	f_it = names.begin();
	while (f_it != names.end()&&(*f_it).at(0) != 'Q') ++f_it;
	if(f_it == names.end()) cout << "There were no Q names\n";
	else {
		r_it = f_it;
		for(;(*r_it).at(0) != 'R'; r_it++)
			count++;
		//outputing the names in reverse
		cout << "There are " << count << " Q names in the list.\n";
		cout << "They are: ";
		while(r_it != f_it){
			--r_it;
			cout << *r_it << " ";
		}
	}
}

