/*
* Mark Brown
* 04/04/2016
* The program is designed to supply "homes" for animals using the list container with pointers.
* The basic idea is to demanstrate polymorphism containers.
*/

#include "homes.h"
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

//menu for selecting the homes for the pokemon
int menu();

int main(){
	list<homes*> box;
	list<homes*>::iterator it;
	homes *tmp;
	string username, filename, test;
    ifstream fin;
    ofstream fout;
	
	cout<<"Welcome to Pokemon Self Building (PSB) automated system.\n"
		<<"I will be here to assist you and help with any issues you may have. You may refer to me as Pete.\n"
		<<"Now lets begin, shall we?.\n"
		<<"Beta version only includes six different Pokemon - Charmander, Bulbasaur, Squirtle, Pidgey, Caterpie, and Arcanine.\n"
		<<"Let's build them a nice home depending on their type.\n\n\n";
		
	cout<<"Please enter a file name (.txt excluded): ";
	getline(cin,username);
	filename = username + ".txt";
	fin.open(filename.c_str());
    if(!fin.fail()){
		getline(fin, test);
		while(!fin.eof()){
			if(fin.peek() == '\n')
				fin.ignore();
			if(test == "Charmander"){
				tmp = new charmander(fin);
				box.push_back(tmp);
			}
			else if (test == "Bulbasaur"){
				tmp = new bulbasaur(fin);
				box.push_back(tmp);
			}
			else if (test == "Squirtle"){
				tmp = new squirtle(fin);
				box.push_back(tmp);
			}
			else if (test == "Pidgey"){
				tmp = new pidgey(fin);
				box.push_back(tmp);
			}
			else if (test == "Caterpie"){
				tmp = new caterpie(fin);
				box.push_back(tmp);
			}
			else if (test == "Arcanine"){
				tmp = new arcanine(fin);
				box.push_back(tmp);
			}
			else{
				cout << "No Data found in file.\n";
			}
			getline(fin, test);
		}
		
	}
	fin.close();
	
	int choice;
     choice = menu();
     while(choice != 9){
	if(choice == 1){//creates a new charmander class and inserts it
		tmp = new charmander;
		tmp ->input();
		box.push_back(tmp);
	}
	else if(choice == 2){//creates a new bulbasaur class and inserts it
		tmp = new bulbasaur;
		tmp ->input();
		box.push_back(tmp);
	}
	else if(choice == 3){//creates a new squirtle class and inserts it
		tmp = new squirtle;
		tmp ->input();
		box.push_back(tmp);
	}
	else if (choice == 4){//creates a new pidgey class and inserts it
		tmp = new pidgey;
		tmp ->input();
		box.push_back(tmp);
	}
	else if (choice == 5){//creates a new caterpie class and inserts it
		tmp = new caterpie;
		tmp ->input();
		box.push_back(tmp);
	}
	else if (choice == 6){//creates a new arcanine class and inserts it
		tmp = new arcanine;
		tmp ->input();
		box.push_back(tmp);
	}
	else if (choice == 7){//iterator show all function
		it = box.begin();
		while(it != box.end()){
			(*it)->output(cout);
			++it;
		}
	}
	else if (choice == 8){//save and close
		fout.open(filename.c_str());
        if(!fout.fail()){
			it = box.begin();
			while(it != box.end()){
				(*it)->output(fout);
				++it;
			}
			cout << "Saving...\n"
				 << "Closing program.";
		}
		else
			cout<<"Unable to save data.\n";
		fout.close();
		break;
	}
	else if(choice == 9)//testing # to close without saving to file
		break;
	choice = menu();
	}
	
}

int menu(){
	int ans;
		cout <<"Which Pokemon would you like to build a home for now? (Charmander[1], Bulbasaur[2], Squirtle[3], Pidgey[4], Caterpie[5], or Arcanine[6]?\n([7] to show all and [8] to save and close)";
	cin>>ans;
	return ans;
}