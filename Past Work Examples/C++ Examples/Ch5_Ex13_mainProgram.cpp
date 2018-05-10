
//Data: 45 67 23 89 -999

#include <iostream>
#include "circularLinkedList.h"

using namespace std;

void testCopyConstructor(circularLinkedList<int> oList);

int main()
{
	circularLinkedList<int> list1;
	int num;

	cout << "Enter number ending with -999"
		 << endl;
	cin >> num;

	while (num != -999)
	{
		list1.insertNode(num);
		cin >> num;
	}

	cout << endl;

	cout << "List: ";
	list1.print();
	cout << endl;

	cout << "Length List: " << list1.length() << endl;

	cout << "Enter the number to be searched:  ";
	cin >> num;
	cout << endl;

	if (list1.search(num))
		cout << num << " found in the list" << endl;
	else
		cout << num << " not in the list" << endl;

	cout << "Enter the number to be deleted: ";
	cin >> num;
	cout << endl;

	list1.deleteNode(num);

	cout << "After deleting the node, "
	     << "List: ";

	list1.print();
	cout << endl;

	cout << "Length List is: " << list1.length() << endl;

	return 0;
}

void testCopyConstructor(circularLinkedList<int> oList)
{
}

