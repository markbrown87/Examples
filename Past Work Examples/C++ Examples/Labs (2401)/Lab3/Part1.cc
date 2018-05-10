/*
Mark Brown
03/02/2016
*/

#include <iostream>


using namespace std;

void pretty(){
	auto int x=0;
	x++;
	for(int i = 0; i <x; ++i){cout<<'*';}
	cout<<endl;
}

int main(){
	for(int i =0;i<6;++i)
		pretty();
}
