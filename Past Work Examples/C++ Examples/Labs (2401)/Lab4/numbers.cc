/*
Mark Brown
10/02/2016
Designed for class numbers and used within the quiz/answers sections
*/


#include "numbers.h"
using namespace std;

Numbers::Numbers(){
	unsigned long data[capacity];
	capacity = 5;
	used = 0;
}

void Numbers::add(unsigned long var1){
	
