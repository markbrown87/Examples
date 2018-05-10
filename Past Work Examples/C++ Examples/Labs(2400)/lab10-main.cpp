/*
Mark Brown
29/10/2015
This program is designed to...
*/

#include <cstdlib>
#include <fstream>
#include <iostream>


using namespace std;

//prototypes
void print_array(const int data[], int count);
void sort (int data[], int count);
int array_total(const int data[], int count);
bool equal_total(const int data[], const int data2[], int count, int count2);
int count_occurrences (const int data[], int count, int target);
bool more_than_3(const int data[], int count, int target);
void swap (int &x, int &y);
int index_of_smallest(const int data[], int start_index, int end_index);


int main (int argc, char const *argv[])
{
	int first[] = {22, 33, 44, 10, 34, 67, 56, 98, 20, 19};
	int second[] = {99, 18, 45, 23, 33, 63, 67, 55 };
	int third[] = {40, 50, 20, 40, 30, 90, 40, 30, 40};

	cout << "Array first" << endl;
	print_array(first, 10);
	cout << endl << "-----------------" << endl;
	cout << "Array second" << endl;
	print_array(second, 8);
	cout << endl << "-----------------" << endl;
	cout << "Sorted array first" << endl;
	sort(first, 10);
	print_array(first, 10);
	cout << endl << "-----------------" << endl;
	
	if(equal_total(first, second, 10, 8)) //two arrays and their element count
		cout << "Totals are the same in arrays first and second.\n";
	else
		cout << "Totals are NOT the same in arrays first and second.\n";
	
	if(equal_total(second, third, 8, 9)) //two arrays and their element count
		cout << "Totals are the same in second and third.\n";
	else
		cout << "Totals are NOT the same in second and third.\n";
	
	int target = 30;
	int occurrences = count_occurrences(third, 9, target);
	cout << target << " occurs " << occurrences << " times in the array third.\n";
	target = 40;
	if(more_than_3(third, 9, target))
		cout << target << " occurs more than 3 times in the array third.\n";
	
	return EXIT_SUCCESS;
}

//functions
void print_array(const int data[], int count)
{
	for(int i=0;i<count;i++)
		cout << data[i] << " ";
}

void sort (int data[], int count)
{
	int min_index;
	for(int i=0; i< (count - 1); i++)
	{
		min_index = index_of_smallest(data, i, count);
		swap(data[i], data[min_index]);
	}
}

void swap (int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}

int index_of_smallest(const int data[], int start_index, int end_index)
{
	int min = data[start_index];
	int min_index = start_index;
	
	for (int i = (start_index + 1); i < end_index;i++)
	{
		if (data[i] < min)
		{
			min = data[i];
			min_index = i;
		}
	}
	return min_index;
}

int array_total(const int data[], int count)
{
	int sum=0;
	for(int i=0;i<count;i++)
		sum += data[i];
	return sum;
}

bool equal_total(const int data[], const int data2[], int count, int count2)
{
	int sum, sum2;
	sum = array_total(data, count);
	sum2 = array_total(data2, count2);
	if (sum == sum2)
		return true;
	else
		return false;
}

int count_occurrences (const int data[], int count, int target)
{
	int occur=0;
	for(int i=0;i<count;i++)
	{
		if(data[i]==target)
			occur++;
	}
	return occur;
}

bool more_than_3(const int data[], int count, int target)
{
	int occur=0;
	for(int i=0;i<count;i++)
	{
		if(data[i]==target)
			occur++;
	}
	if(occur >= 3)
		return true;
	else
		return false;
}
				









