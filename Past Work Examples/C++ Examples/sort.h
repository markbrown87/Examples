#ifndef SORT_H
#define SORT_H


class sortBag{
	public:
		sortBag() {compare = 0;}; //constructor
		~sortBag() {}; //deconstructor
		void fill(); //fills the vector array
		void print() const; //prints the vector array

		void insertionSort(); //sorts vector element by means of insertionSort
		void shellSort(); //sorts vector element by means of shellSort
		void quickSort_l(); //quicksort that uses the last element as pivot
		void quickSort_m(); //quicksort using the median as pivot

	private:
		
		void quicksort(int first, int last); //helper function for quicksort_l for recursion
		int partition(int first, int last); //helper function to split vector element
		void swap(int first, int second); //swaps two different vector locations
		void mergeSort(int l, int r); //helper function for quicksort_m for recursion
		void merge(int low, int mid,  int high); //merges the array after it's been sorted and placed into vector element
			
		std::vector<int> element; //vector of elements
		int compare; //holds the number of comparisons made
};

#endif
