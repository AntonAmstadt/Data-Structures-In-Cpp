#include <iostream>
#include "GenericLinkedList.h"


int main() {
	LinkedList<int> myList{};
	myList.prependNode(9);
	myList.prependNode(8);
	myList.displayList();
	myList.appendNode(7);
	myList.displayList();
	myList.insertNode(5);
	myList.displayList();
	myList.insertNode(5);
	myList.displayList();
	myList.insertNode(6);
	myList.displayList();
	myList.insertNode(11);
	myList.displayList();
	myList.insertNode(10);
	myList.displayList();
}