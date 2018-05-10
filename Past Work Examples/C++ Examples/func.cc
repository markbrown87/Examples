#include <iostream>
#include "func.h"

using namespace std;
//
void Heap::inputData(){
	cout<<"Enter the size of Array : ";
	cin>>size;
	cout<<"\nEnter "<<size<<" Elements\n";
	for(int i=0;i<size;++i)
		cin>>index[i];
}
//
void buildHeap(Heap &heap){
	int q,i,j,key;
	for(q=2;q<=heap.size;q++){
		i=q;
		key=heap.index[i];
		j=i/2;
		
		while(i>1 && key>heap.index[j]){
			heap.index[i]=heap.index[j];
			i=j;
			j=i/2;
			if(j<1)
				j=1;
		}
    heap.index[i]=key;
    }
}
//
void Heap::displayData(){
	cout<<"\n\nHeap Function Output\n\n";
	for(int i=0;i<=size;++i)
		cout<<index[i]<<endl;
}