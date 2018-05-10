/*************************************************************
    Project 2 CS2401 Spring 2014
    This is the main for your second project, a project which
    works with the concepts of a sequence class, an internal
    iterator, and a dynamic array.
    In order to make this main work you will need to write two
    classes, one called Friend and one called FBFriends. Going
    through the code below you should be able to figure out what
    member functions are needed for each.
    Also, since FBFriends is holding dynamic memory you will need
    to write the Big 3 for this class.
    	John Dolan	Ohio University	School of EECS **************************************************************/
    
#include<iostream>
#include<fstream> 
#include<cstdlib> 
#include<string> 
#include "friend.h" 
#include "fbfriends.h"
using namespace std; 
    int menu(); 
    int menu2(); 

int main(){
    Friend myfriend;
    FBFriends myfb;
    string friendname;
    int choice,choice2;
    string username, filename;
    ifstream fin;
    ofstream fout;
    bool cutout;
	cout<<"Welcome to Friends Management.\n\n";
	cout<<"Begin by entering your username: ";
	getline(cin,username);
	filename = username + ".txt";
	fin.open(filename.c_str());
    if(!fin.fail())
	myfb.load(fin);
	fin.close();
	choice = 0;
	choice2 = 0;
	cutout = false;
        FBFriends original(myfb);
	while(choice != 9){
	    choice = menu();
	    switch(choice){
		case 1:	cin>>myfriend;
		       	myfb.start();
			myfb.insert(myfriend);
			break;
		case 2: myfb.show_all(cout);
			break;
		case 3: {myfb.start();
			choice2 = 0;
			while(myfb.is_item()&& choice2 <= 5){
			    cout<<myfb.current();
			    choice2 = menu2();
			    if(choice2 == 1)
				myfb.remove_current();
			    else if(choice2 == 2){
				if(!cutout)
				cin>>myfriend;
				if(myfb.is_friend(myfriend))
				cout<<"Already in list.\n";
				else
				myfb.insert(myfriend);
				cutout = false;
			    }
			    else if(choice2 == 3){
				if(!cutout)
				cin >> myfriend;
                               if(myfb.is_friend(myfriend))
                                cout<<"Already in list.\n";
                                else
				myfb.attach(myfriend);
				cutout = false;
			    }
			    else if (choice2 == 4){
				myfriend = myfb.current();
				myfb.remove_current();
				cutout = true;
				}
			    else if(choice2 == 5){
				myfb.advance();
			    }
			    else
				cout<<"Going back to main menu.\n";
			}
			break;
			}
		case 4: myfb.bday_sort();
			break;
		case 5:{
			cout<<"Enter the name of your friend:\n";
			if(cin.peek() == '\n') cin.ignore();
			getline(cin, friendname);
			myfriend = myfb.find_friend(friendname);
			cout<<myfriend<<endl;
			break;
			}
		case 6:	original.show_all(cout);
			break;
		default: break;
		} // bottom of the switch
	} // bottom of the while
	fout.open(filename.c_str());
        if(!fout.fail())
	    myfb.save(fout);
	else
	    cout<<"Unable to save data.\n";
	fout.close();
	cout<<"Come visit your friends again soon.\n"; return 0;
}
	
int menu(){
	int ans;
	cout<<"Choose from the options below:\n";
	cout<<"1 - Add a friend to the beginning of the list.\n";
	cout<<"2 - See all your friends.\n";
	cout<<"3 - Walk through the list, one friend at a time.\n";
	cout<<"4 - Sort your friends by birthday.\n";
	cout<<"5 - Find a friend so you can learn when they were born.\n";
	cout<<"6 - See the list you started with in today's session. \n";
	cout<<"9 - Leave the program.\n";
	cin>>ans;
    return ans;
}
int menu2(){
	int ans;
	cout<<"What would like to do with this friend?\n";
	cout<<"1 - Remove from the list.\n";
	cout<<"2 - Insert a new friend or cut-out friend before this friend.\n";
	cout<<"3 - Put a new friend or cut-out friend after this friend.\n";
	cout<<"4 - Cut this friend from the list to be inserted elsewhere.\n";
	cout<<" If you want the friend earlier in the list you will need to start a new walk-through.\n";
	cout<<"5 - Advance to the next friend.\n";
	cout<<"6 - Return to main menu.\n";
	cin>>ans;
    return ans;
}
