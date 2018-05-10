/**************************************************
	Mark Brown
	mb899115
	26/09/2016
	Template with missing member functions 
	search and destroy filled in and completed
***************************************************/


#ifndef H_circularLinkedList
#define H_circularLinkedList
 
#include <iostream>
#include <cassert>
using namespace std;

template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type> *link;
};
 
template <class Type>
class circularLinkedList
{
public:
    const circularLinkedList<Type>& operator=
          			      (const circularLinkedList<Type>&); 
		//Overloads the assignment operator.
    void initializeList(); 
 		//Initializes the list to an empty state.
	    //Postcondition: first = NULL, last = NULL,
		//                count = 0
    bool isEmptyList();
 		//Function to determine whether the list is empty. 
		//Postcondition: Returns true if the list is empty;
		//               otherwise, returns false.

    void print() const;

	int length();
		//Function to return the number of nodes in the 
		//list.
		//Postcondition: The value of count is returned.
    void destroyList();
 		//Function to delete all the nodes from the list.
  		//Postcondition: first = NULL, last = NULL, 
		//               count = 0
    Type front(); 
 		//Function to return the first element of the list.
 		//Precondition: The list must exist and must not be
		//empty.
  		//Postcondition: If the list is empty, then the 
 		//               program terminates; otherwise, 
	    //               the first element of the list is 
		//               returned.
    Type back(); 
       //Function to return the last element of the
       //list.
		//Precondition: The list must exist and must not
		//be empty.
		//Postcondition: If the list is empty, then the 
		//               program terminates; otherwise,
		//               the last element of the list is 
		//               returned.

	bool search(const Type& searchItem);
		//Function to determine whether searchItem is in 
		//the list.
		//Postcondition: Returns true if searchItem is found
		//               in the list; otherwise, it returns
		//               false.

    void insertNode(const Type& newitem);

    void deleteNode(const Type& deleteItem);
  		//Function to delete deleteItem from the list.
 		//Postcondition: If found, the node containing 
   		//               deleteItem is deleted from the 
		//                list, first points to the first
		//                node, and last points to the last 
		//                node of the updated list. 

    circularLinkedList(); 
   		//Default constructor
 		//Initializes the list to an empty state.
 		//Postcondition: first = NULL, last = NULL, 
		//               count = 0 

    circularLinkedList(const circularLinkedList<Type>& otherList); 
         //Copy constructor

    ~circularLinkedList();   
    	//Destructor
   		//Deletes all the nodes from the list.
    	//Postcondition: The list object is destroyed. 

protected:
    int count;		//variable to store the number of 
 					//elements in the list
    nodeType<Type> *first; //pointer to the first node of 
                           //the list
    nodeType<Type> *last;  //pointer to the last node of 
                           //the list 
private:
    void copyList(const circularLinkedList<Type>& otherList); 
		//Function to make a copy of otherList.
		//Postcondition: A copy of otherList is created 
		//               and assigned to this list.
};

template <class Type>
bool circularLinkedList<Type>::isEmptyList()
{
	return (first == NULL);
}

template <class Type>
circularLinkedList<Type>::circularLinkedList() // default constructor
{
	first = NULL;
	count = 0;
}

template <class Type>
void circularLinkedList<Type>::destroyList()
{
	nodeType<Type> *temp;    
	nodeType<Type> *current; 
						
	if (first != NULL)
	{
		current = first->link;
		first->link = NULL;
	}

	while (current != NULL)    
	{
        temp = current;        
        current = current->link; 
        delete temp;         
	}

	last = NULL;	//initialize last to NULL; first has already
                   //been set to NULL by the while loop
 	count = 0;
}

	
template <class Type>
void circularLinkedList<Type>::initializeList()
{
	destroyList(); //if the list has any nodes, delete them
}

template <class Type>
int circularLinkedList<Type>::length()
{
 	return count;
}  // end length

template <class Type>
Type circularLinkedList<Type>::front()
{   
    assert(first != NULL);
   	return first->link->info; //return the info of the first node	
}//end front


template <class Type>
Type circularLinkedList<Type>::back()
{   
    assert(first != NULL);
    return first->info; //return the info of the first node	
}//end back


/************************************************************************************************************/
//changed this area for question 13 from given template


template <class Type>
bool circularLinkedList<Type>::search(const Type& searchItem)
{
    nodeType<Type> *current; //pointer to traverse the list
    bool found = false;

	current = first->link;

	if(isEmptyList())
		return found;
	if(first->info == searchItem) //if first is searchItem then true else remain false
		found = true;

	while (current != first){ //traverse list looking for searchItem if found then true else remain false
		if(current -> info == searchItem)
			found = true;
		current = current->link;
	}

    return found;
}//end search
/*************************************************************************************************************/


template <class Type>
void circularLinkedList<Type>::insertNode(const Type& newitem)
{
	nodeType<Type> *current; //pointer to traverse the list
	nodeType<Type> *trailCurrent; //pointer just before current
	nodeType<Type> *newNode;  //pointer to create a node

	bool  found;

	newNode = new nodeType<Type>; //create the node

	newNode->info = newitem;   //store newitem in the node
	newNode->link = NULL;      //set the link field of the node
                                 //to NULL

	if (first == NULL)  //Case 1	
	{	
	   first = newNode;
	   first->link = newNode;
	   count++;
 	}
	else
	{
		if (newitem >= first->info)
		{
			newNode->link = first->link;
			first->link = newNode;
			first = newNode;
		}
		else
		{
			trailCurrent = first;
			current = first->link;
			found = false;

			while (current != first && !found)		
				if (current->info >= newitem)			
					found = true;
				else
				{
					trailCurrent = current;
					current = current->link;
				}
	   		  
			trailCurrent->link = newNode;
			newNode->link = current;
		}

		count++;
	}//end else
}//end insertNode

/************************************************************************************************************/
//changed this area for question 13 from given template

template <class Type>
void circularLinkedList<Type>::deleteNode(const Type& deleteItem)
{
	nodeType<Type> *current; //pointer to traverse the list
	nodeType<Type> *trailCurrent; //pointer just before current
	nodeType<Type> *temp; //point for temp holding


	current = first->link;
	trailCurrent = first;

	if(search(deleteItem)){//check list for deleteItem
		for (; current != first; current=current->link){//traverse list for item
			if(current->info == deleteItem){//if found then delete
				temp = current;
				current = current->link;
				delete temp;
				--count;
				trailCurrent->link = current;
			}
			trailCurrent = current;//step next
		}
		if(current->info == deleteItem){//checks first and deletes if first = deleteItem
			temp = current;
			current = current->link;
			delete temp;
			--count;
			trailCurrent->link = current;
			first = trailCurrent;
		}
	}	
} //end deleteNode

/************************************************************************************************************/



	//Overloading the stream insertion operator
template <class Type>
void  circularLinkedList<Type>::print() const
{
	nodeType<Type> *current; //pointer to traverse the list
	
    current = first->link;    
					   
    while (current != first) //while more data to print
    {
        cout << current->info << " ";
        current = current->link;
    }

    cout << first->info << " ";
}

template <class Type>
circularLinkedList<Type>::~circularLinkedList() // destructor
{
	destroyList(); 
}//end destructor


template <class Type>
void circularLinkedList<Type>::copyList
            	      (const circularLinkedList<Type>& otherList) 
{
   nodeType<Type> *newNode; 
   nodeType<Type> *current; 
   nodeType<Type> *tempFirst; 

   if (first != NULL)	
	  destroyList();

   if (otherList.first == NULL) 
   {
		first = NULL;
 		count = 0;
   }
   else
   {
		current = otherList.first->link;  //current points to the 
									//list to be copied
		count = otherList.count;

			//copy the first node
		tempFirst = new nodeType<Type>;  //create the node

		tempFirst->info = current->info; //copy the info
		last = tempFirst;    		     //make last point to the 
            						 //first node
		current = current->link;     //make current point to the 
           							 //next node

			//copy the remaining list
		while (current != otherList.first)
		{
			newNode = new nodeType<Type>;  //create a node
			newNode->info = current->info;	
			last->link = newNode; 		
			last = newNode;   			
										
			current = current->link;	
       									
		}//end while
	
		if (tempFirst == last)
		{
			first = tempFirst;
			first->link = first;
		}
		else
		{
			newNode = new nodeType<Type>;  //create a node
			newNode->info = current->info;	
			last->link = newNode; 		
			first = newNode;   		
			first->link = tempFirst;
		}

	}//end else
}//end copyList

	//copy constructor
template<class Type>
circularLinkedList<Type>::circularLinkedList
            	      (const circularLinkedList<Type>& otherList) 
{
	first = NULL;

	copyList(otherList);
	
}//end copy constructor

	//overload the assignment operator
template <class Type>
const circularLinkedList<Type>& circularLinkedList<Type>::operator=
   	 	 		(const circularLinkedList<Type>& otherList)
{ 
	if (this != &otherList) //avoid self-copy
	{
		copyList(otherList);
	}//end else

	return *this; 
}

#endif
