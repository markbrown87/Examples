/********************************************************
			Mark Brown
			05/09/2016	
CS3610
  This short program determines prime numbers by using 
the Sieve of eratosthenes approach
********************************************************/

#include <list>
#include <iostream>

int main(){
	int holder, n;
	
	
	while(std::cin >> n){
	
	std::list<int> box; //a box of arranged numbers from 2 to n (input)
	std::list<int> prime; //a sorted list with only prime numbers
	
	for(int i = 2; i < (n+1); ++i)
		box.push_back(i); //fills the box
	prime = box;
	
	if (n < 1){ 
		std::cout << "0 is both a prime and not a prime number." << '\n'; //error message for input of 0
		break;
	}
	for(std::list<int>::iterator it1=box.begin();it1 != box.end();++it1){ //begins iteratoring the list starting at box.begin()
		holder = *it1;
		for(std::list<int>::iterator it2=box.begin();it2 != box.end(); ++it2){ //beings iteratoring the list within the list ie - (1,1)\(1,2)\(1,3)
			if(*it2%holder==0 && *it2 != holder)                           //where both numbers (positions) are within the same box
				prime.remove(*it2);  //removes the non-prime numbers
		}
	}
	
	for(std::list<int>::iterator it = prime.begin(); it !=prime.end(); it++)
		std::cout << *it << " "; //prints to the screen all prime numbers from 2 to n
	std::cout << endl;
	}
}
