#ifndef GENERICLINKEDLIST_H
#define GENERICLINKEDLIST_H

#include <iostream>

template <class T>
class LinkedList {
	struct ListNode {
		T val;
		struct ListNode* next;
		ListNode() : val{}, next{ nullptr }{}
		ListNode(T newValue) : val{ newValue }, next{ nullptr }{}
	};
	ListNode* head;
public:
	LinkedList() : head{ nullptr } {}
	~LinkedList();
	void prependNode(T); 
	void appendNode(T);
	void insertNode(T); //uses operator< to insert in proper location
	void deleteNode(T); //uses operator==
	void displayList() const; //uses std::cout << (value of type T)
};

template <class T>
void LinkedList<T>::prependNode(T newValue) {
	ListNode* newNode = new ListNode{};
	newNode->val = newValue;
	if (head) {
		newNode->next = head;
		head = newNode;
	}
	else {
		head = newNode;
		newNode->next = nullptr;
	}
}

template<class T>
void LinkedList<T>::displayList() const {
	ListNode* nodePtr = head;
	while (nodePtr) {
		std::cout << nodePtr->val << ' ';
		nodePtr = nodePtr->next;
	}
	std::cout << '\n';
}

template <class T>
void LinkedList<T>::appendNode(T newValue) {
	ListNode* newNode;
	ListNode* nodePtr; //to move thru list
	newNode = new ListNode{ newValue };
	if (!head)
		head = newNode;
	else {
		nodePtr = head;
		while (nodePtr->next) //nodePtr will = last node in list
			nodePtr = nodePtr->next;
		nodePtr->next = newNode;
	}
}

template <class T>
void LinkedList<T>::insertNode(T newValue) {
	ListNode* newNode{ new ListNode{newValue} };
	ListNode* nodePtr;
	if (!head) 
		head = newNode;
	else {
		if (newValue < head->val) {
			newNode->next = head;
			head = newNode;
		}
		else {
			nodePtr = head;
			while (nodePtr->next && nodePtr->next->val < newValue) //nodePtr becomes node before insertion point
				nodePtr = nodePtr->next;
			ListNode* temp = nodePtr->next;
			nodePtr->next = newNode;
			newNode->next = temp;
		}	
	}
}

template <class T> 
void LinkedList<T>::deleteNode(T value) {
	if (!head) {
		return;
	}
	bool found{ false };
	ListNode* prev{ nullptr };
	ListNode* nodePtr{ head };
	while (nodePtr && !found) {
		if (nodePtr->val == value)
			found = true;
		else {
			prev = nodePtr;
			nodePtr = nodePtr->next;
		}
	}
	if (found) {
		if (!prev && nodePtr->next) {
			head = nodePtr->next;
			delete nodePtr;
		}
		else if (!prev && !nodePtr->next) {
			head = nullptr;
			delete nodePtr;
		}
		else if (nodePtr){
			prev->next = nodePtr->next;
			delete nodePtr;
		}
	}
}

template <class T>
LinkedList<T>::~LinkedList() {
	ListNode* nodePtr{ head };
	ListNode* nextNode;

	while (nodePtr) {
		nextNode = nodePtr->next;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

#endif
