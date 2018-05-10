
#include "func.h"

using namespace std;

int main(){
	Heap heap;
	heap.inputData();
	buildHeap(heap);
	heap.displayData();
}