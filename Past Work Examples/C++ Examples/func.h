#ifndef FUNC_H
#define	FUNC_H

class Heap{
	public:
		void inputData();
		friend void buildHeap(Heap &);
		void displayData();
	
	private:
		int size;
		int index[100];
};

#endif