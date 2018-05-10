/*********************************************************************
     Lab Assignment 6: This is another lab assignment in working with
     linked lists. We will be using a struct node, for its simplicity,
     and working with non-member functions here. The main point is to
     work with the logic of a linked list. Do not be afraid to make
     drawings on scrap paper.
     The prototypes for the functions that you are to implement are
     included. You should uncomment them when you are ready to write
     the implementation.
     John Dolan Spring 2016 *********************************************************************/ 
//Modified by Mark Brown on 24/02/2016

#include<iostream> 
#include<cstdlib> 
#include<ctime>

using namespace std; 

struct node{
     int data;
     node * link;
};
// These are the three I have written for you 
void build_list(node* & head); 
// note that we are passing by reference 
void show_list(const node* head); 

int size(const node* head); //These are the two that you are to write, as described in the 
			    //instructions page. 



void remove_repeats(node*& head);
void split_list(node* original, node*& lesser,node*& greater,int split_value); 


int main(){
	int start, stop;
    	int split;
    	node* head = NULL;
    	node *lesser;
    	node * greater;

    	start = time(NULL);
    	build_list(head);
    	stop = time(NULL);
    	cout<<"Time to build list = "<<stop - start <<"seconds.\n";
    	start = time(NULL);
    	show_list(head);
    	stop = time(NULL);
    	cout<<"Time to print list = "<<stop - start<<"seconds.\n";
    	cout<<"Size of the list = "<<size(head)<<endl;
	start=time(NULL); 
	remove_repeats(head);
	stop=time(NULL);
	cout<<"Time it took to remove duplicates: "<<stop-start<<"seconds.\n";
	show_list(head);
	cout<<"The list size is now: " << size(head) << endl;
	cout<<"Please enter a value to divide the list: " << endl;
 	cin >> split;
	start=time(NULL);
	split_list(head, lesser, greater, split);
	stop=time(NULL);
	cout<<"Time it took to split the lists: " <<stop - start<<"seconds.\n";
	cout<<"All values that are below split value are: " << endl;
	show_list(lesser);
	cout<<"Size of lesser list is: " <<size(lesser)<<endl;
	cout<<"All values that are above split value are: " << endl;
	show_list(greater);
	cout<<"Size of greater list is: "<<size(greater)<<endl;
    	return 0;
}
// builds a linked list of 2000 random integers, all in the 1 to 500 range 
void build_list(node*& head){
     node* cursor;
     head = new node;
     head->data = rand()%500 + 1;
     cursor = head;
     for(int i = 0; i < 2000; ++i){
	cursor->link = new node;
        cursor = cursor->link;
        cursor->data = rand()%500 + 1;
     }
     cursor->link = NULL;
}
// outputs the contents of a linked list to the screen 
void show_list(const node* head){
      const node * cursor = head;
      while(cursor != NULL){
   	cout<<cursor->data<<" ";
	cursor = cursor->link;
      }
     cout<<endl;
}
// returns the number of nodes in a linked list 
int size(const node* head){
	const node* cursor = head;
	int count = 0;
	while(cursor != NULL){
  	    count++;
	    cursor = cursor->link;
	}
	return count;
}
//removes all duplicated values in the list
void remove_repeats(node*& head){
	node *cursor, *nxt, *prv;
	cursor = head;

	while(cursor != NULL){
		nxt = cursor->link;
		prv = cursor;
            	while(nxt != NULL){
               		if(nxt->data == cursor->data){
                  		prv->link = nxt->link;
                  		delete nxt;
                  		nxt = prv->link;
               		}
               		else{
                  		prv = nxt;
                  		nxt = nxt->link;
               		}
            	}
	cursor = cursor->link;
	}
}
//splits the list into two halves by a value selected by the user
void split_list(node* original, node*& lesser, node*& greater, int split_value){

    node **pplhs = &lesser;
    node **pprhs = &greater;

    for (;original; original = original->link)
    {
        node **& pp = (original->data < split_value) ? pplhs : pprhs;
        *pp = original;
        pp = &(*pp)->link;
    }
    *pplhs = *pprhs = NULL;	
/*Disclaimer: The above work is a modified version of an example found online. My previous
design had me in circles and I just couldn't figure out why. The above works correctly but it's
not in the style that I had been taught. Just wanted to give credit, where credit was due.*/
}
