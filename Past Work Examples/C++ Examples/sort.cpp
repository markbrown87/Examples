#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstddef>
#include <vector>
#include <string>
#include "sort.h"

using namespace std;

//fills the vector element with provided variables needed to be sorted
void sortBag::fill(){
	int temp;
	while (cin >> temp){
		if (temp == -999)
		break;
		element.push_back(temp);
	}
}

//self explanatory -> prints out elements within vector element
void sortBag::print() const{
	for (int i = 0; i < element.size(); ++i)
	cout << element[i] << ' ';
	cout << endl;
	cout << compare << endl;
}

//insertionsort for vector element
//code burrowed from "Data Structures Using C++ 2nd edition" by D.S. Malik
void sortBag::insertionSort(){
	fill();
	
	int firstOutOfOrder, location;
	int temp;

	for(firstOutOfOrder = 1; firstOutOfOrder < element.size(); firstOutOfOrder++){
		if(element[firstOutOfOrder] < element[firstOutOfOrder-1]){
			temp = element[firstOutOfOrder];
			location = firstOutOfOrder;
			
			compare++;

			do{
				element[location] = element[location-1];
				location--;
			} while (location > 0 && element[location-1] > temp);
			
			element[location] = temp;
		}
	}
}

//shellsort for vector element
void sortBag::shellSort(){
	fill();
	int j;

	for (int gap = element.size() / 2; gap > 0; gap /= 2){
		for (int i = gap; i < element.size(); ++i){
			int temp = element[i];
			for (j = i; j >= gap && temp < element[j - gap]; j -= gap){
				element[j] = element[j - gap];
				compare++;
			}
			element[j] = temp;
		} 
	}			
}

//calls quicksort function that sorts the elements based on pivots
void sortBag::quickSort_l(){
	fill();
	
	quicksort(0, element.size()-1);
}
//the function that sorts the array of int's based on pivots
void sortBag::quicksort(int first, int last){
	int pivotLocation;
	
	if (first < last){
		pivotLocation = partition(first, last);
		quicksort(first, pivotLocation - 1);
		quicksort(pivotLocation + 1, last);
	}
}
//splits the array and swaps if need be
int sortBag::partition(int first, int last){
	int pivot, index, smallIndex;
	
	swap (first, (first + last)/2);
	
	pivot = element[first];
	smallIndex = first;
	
	for (index = first + 1; index <= last; index++)
	if(element[index] < pivot){
		compare++;
		smallIndex++;
		swap(smallIndex, index);
	}
	
	swap(first, smallIndex);
	
	return smallIndex;
}
//swap function used to swap the values within the vector element
void sortBag::swap(int first, int second){
	int temp;
	
	temp = element[first];
	element[first] = element[second];
	element[second] = temp;
}

//quickSort function that calls mergesort which sorts based on the median as pivot
void sortBag::quickSort_m(){
	fill();

	mergeSort(0, element.size()-1);
}
//mergeSort function that uses the median as pivot for sorting
void sortBag::mergeSort(int l, int r){
	if(l < r){
		int m =l+(r-l)/2;
		mergeSort(l, m);
		mergeSort(m+1, r);
		merge(l, m, r);
	}
}
//merge function that merges the vector element once it's been sorted
void sortBag::merge(int low, int mid, int high){
	int h,i,j,k;
	int blist[1000];
	h=low;
	i=low;
	j=mid+1;

	while((h<=mid)&&(j<=high)){
		if(element[h]<=element[j]){
			compare++;
			blist[i]=element[h];
			h++;
		}
		else{
			blist[i]=element[j];
			j++;
		}
		i++;
	}
	if(h>mid){
		for(k=j;k<=high;k++){
			blist[i]=element[k];
			i++;
		}
	}
	else{
		for(k=h;k<=mid;k++){
			blist[i]=element[k];
			i++;
		}
	}
	for(k=low;k<=high;k++) 
		element[k]=blist[k];
}




