
/*
 * Mark Brown
 * mb899115
 * 19.10.2016
 * 
 * All code provided by D.S. Malik from the book
 * "Data Structures Using C++ 2nd Edition". Only changes made were to 
 * place a class variable of inputCount and compareCount for raw
 * data used in the assignment and creation of print() function. 
 * I do not claim any sort of ownership over the code provided 
 * by D.S. Malik
 * 
 */

#include <iostream>
#include <cassert>


using namespace std;

template <class elemType>
class arrayListType
{
public:
	const arrayListType<elemType>& operator=
	(const arrayListType<elemType>&);

	int seqSearch(const elemType& item);
	void insert(const elemType& insertItem);
	arrayListType(int size = 100);
	arrayListType(const arrayListType<elemType>& otherList);

	~arrayListType();

	void heapSort();
	void print() const { cout << compareCount << " by " << inputCount << endl;};

protected:
	elemType *list; //array to hold the list elements
	int length; //to store the length of the list
	int maxSize; //to store the maximum size of the list
	int inputCount; //records the amount of inserted elements
	int compareCount; //records the amount of compared elements

	void heapify(int low, int high);
	void buildHeap();
};

template<class elemType>
void arrayListType<elemType>::heapify(int low, int high)
{
	int largeIndex;

	elemType temp = list[low]; //copy the root node of the subtree

	largeIndex = 2 * low + 1; //index of the left child

	while (largeIndex <= high)
	{
		if (largeIndex < high)
			compareCount++;
			if (list[largeIndex] < list[largeIndex + 1]){
				largeIndex = largeIndex + 1; //index of the largest child
				compareCount++;
			}
		if (temp > list[largeIndex]){ //subtree is already in a heap
			compareCount++;
			break;
		}
		else
		{
			list[low] = list[largeIndex]; //move the larger child to the root
			low = largeIndex; //go to the subtree to restore the heap
			largeIndex = 2 * low + 1;
		}
	}//end while

	list[low] = temp; //insert temp into the tree, that is, list

} //end heapif


template<class elemType>
void arrayListType<elemType>::buildHeap()
{
	int index;

	for (index = length / 2 - 1; index >= 0; index--)
		heapify(index, length - 1);
}

template<class elemType>
void arrayListType<elemType>::heapSort()
{
	int lastOutOfOrder;
	elemType temp;

	buildHeap();

	for (lastOutOfOrder = length - 1; lastOutOfOrder >= 0;lastOutOfOrder--)
	{
		temp = list[lastOutOfOrder];
		list[lastOutOfOrder] = list[0];
		list[0] = temp;
		heapify(0, lastOutOfOrder - 1);
	}//end for
}//end heapSort

template <class elemType>
int arrayListType<elemType>::seqSearch(const elemType& item)
{
	int loc;
	bool found = false;

	for (loc = 0; loc < length; loc++)
	if (list[loc] == item)
	{
		found = true;
			break;
	}

	if (found)
		return loc;
	else
		return -1;
} //end seqSearch

template <class elemType>
void arrayListType<elemType>::insert(const elemType& insertItem)
{
	int loc;

	if (length == 0){ //list is empty
		list[length++] = insertItem; //insert the item and increment the length
		inputCount++;
	}
	else if (length == maxSize)
		cout << "Cannot insert in a full list." << endl;
	else
	{
		loc = seqSearch(insertItem);

		if (loc == -1){//the item to be inserted does not exist in the list
			list[length++] = insertItem;
			inputCount++;
		}
		else
		cout << "No duplicates are allowed." << endl;
	}
} //end insert

template <class elemType>
arrayListType<elemType>::arrayListType(int size)
{
	if (size < 0)
	{
		cout << "The array size must be positive. Creating "
		<< "an array of size 100. " << endl;

		maxSize = 100;
	}
	else
	maxSize = size;
	inputCount = 0;
	compareCount = 0;
	length = 0;

	list = new elemType[maxSize];
	assert(list != NULL);
}//end of constructor

template <class elemType>
arrayListType<elemType>::~arrayListType()
{
	delete[] list;
}//end of destructor


template <class elemType>
arrayListType<elemType>::arrayListType
(const arrayListType<elemType>& otherList)
{
	maxSize = otherList.maxSize;
	length = otherList.length;
	list = new elemType[maxSize]; //create the array
	assert(list != NULL); //terminate if unable to allocate memory space

	for (int j = 0; j < length; j++) //copy otherList
	list[j] = otherList.list[j];
} //end copy constructor

template <class elemType>
const arrayListType<elemType>& arrayListType<elemType>::operator=
(const arrayListType<elemType>& otherList)
{
	if (this != &otherList) //avoid self-assignment
	{
		delete[] list;
		maxSize = otherList.maxSize;
		length = otherList.length;

		list = new elemType[maxSize]; //create the array
		assert(list != NULL); //if unable to allocate memory space, terminate the program
		for (int i = 0; i < length; i++)
		list[i] = otherList.list[i];
	}

	return *this;
}
