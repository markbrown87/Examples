/*
 * Mark Brown
 * mb899115
 * 19.10.2016
 * 
 * A quick main created to test buildHeap and heapify as well as 
 * print() raw data to the screen for analysis of the buildHeap and
 * heapify function
 * 
 */


#include "HeapCode.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
	int element;
	arrayListType<int> heap;

	cin >> element;

	while (value != -9)
	{
		heap.insert(element);
		cin >> element;
	}

	heap.heapSort();
	heap.print();
	
	return 0;
};
