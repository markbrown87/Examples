//Mark Brown
#include <iostream>

using namespace std;

int main(){
	int *ptr;
	ptr = new int;
	*ptr=2401;
	for(int i=0;i<100000;i++){
		--(ptr); 
		cout<<*ptr<<"is stored at " <<ptr<<endl;
	}
}
