#include <iostream>
#include <stack>
#include "ClassicBst.h"

/* search tree supports: search, minimum, maximum, predecessor, successor, insert, and delete */
// search tree can be used as both dictionary and as a priority queue
// in a tree with unique values, successor and predecessor are the next largest/smallest values repectively

//Binary Search Tree class (with parent pointer)
template <class T>
class Bstp {
	struct Node {
		Node* left;
		Node* right;
		Node* p; //parent
		T val;
		Node(T value) : left{ nullptr }, right{ nullptr }, p{ nullptr }, val{ value } {}
		Node(T value, Node* parent) : left{ nullptr }, right{ nullptr }, p{ parent }, val{ value } {}
		Node(const Node& n) : left{ n.left }, right{ n.right }, p{ n.p }, val{ n.val }{}
};
	Node* root;

	void inOrderTreeWalk(Node*);
	void deleteSubTree(Node*&);
	void insertNewNode(Node*&, Node*&);
	void iterativeInsert(Node*&, Node*&);
	bool nodeSearch(Node*, T);
	Node* npSearch(Node*, T);
	Node* successor(Node*);
	Node* predecessor(Node*);
	Node* minimumNode(Node*);
	Node* maximumNode(Node*);
public:
	Bstp() : root{ nullptr } {}
	bool search(T);
	void inOrderTreeWalk(); 
	void insert(T);
	void iterativeInsert(T);
	T minimum();
	T maximum();
	void successorTest(T);
	void predecessorTest(T);
	~Bstp();
};

template <class T>
void Bstp<T>::iterativeInsert(T value) {
	Node* newNode{ new Node{value} };
	iterativeInsert(root, newNode);
}

template <class T>
void Bstp<T>::iterativeInsert(Node*& nodePtr, Node*& newNode) {
	if (nodePtr == nullptr) {
		nodePtr = newNode;
		return;
	}
	Node* parent{ nullptr };
	Node* n = nodePtr;
	Node** par{nullptr};
	while (n) {
		parent = n;
		if (n->val < newNode->val) {
			par = &(n->left);
			n = n->left;
		
		}
		else {
			par = &(n->right);
			n = n->right;		
		}
			
	}
	newNode->p = parent;
	*par = newNode;
	//alternative version without the par variable:
	/*if (newNode->val < parent->val)
		parent->left = newNode;
	else
		parent->right = newNode;*/
}

template <class T>
void Bstp<T>::predecessorTest(T value) {
	Node* p{ predecessor(npSearch(root, value)) };
	if (p)
		std::cout << "predecessor: " << p->val << '\n';
	else
		std::cout << "invalid predecessor arg\n";

}

template <class T>
typename Bstp<T>::Node* Bstp<T>::maximumNode(Node* nodePtr) {
	while (nodePtr->right)
		nodePtr = nodePtr->right;
	return nodePtr;
}

template <class T>
typename Bstp<T>::Node* Bstp<T>::predecessor(Node* nodePtr) {
	if (nodePtr == nullptr)
		return nullptr;
	else if (nodePtr->left)
		return maximumNode(nodePtr->left);
	
	Node* y = nodePtr->p;
	while (y && nodePtr == y->left) {
		nodePtr = y;
		y = y->p;
	}
	return y;
}

template <class T>
void Bstp<T>::successorTest(T value) {
	Node* p = successor(npSearch(root, value));
	if (p)
		std::cout << "successor: " << p->val << '\n';
	else
		std::cout << "invalid successor arg\n";
}

template <class T>
typename Bstp<T>::Node* Bstp<T>::npSearch(Node* nodePtr, T value) {
	if (nodePtr == nullptr || nodePtr->val == value)
		return nodePtr;
	else if (value < nodePtr->val)
		return npSearch(nodePtr->left, value);
	else
		return npSearch(nodePtr->right, value);
}

template <class T>
typename Bstp<T>::Node* Bstp<T>::successor(Node* x) {
	if (x == nullptr)
		return nullptr;
	if (x->right)
		return minimumNode(x->right);
	Node* y = x->p;
	while (y != nullptr && x == y->right) {
		x = y;
		y = y->p;
	}
	return y;
}

template <class T>
T Bstp<T>::minimum() {
	Node* ptr = minimumNode(root);
	return ptr->val;
}

template <class T> 
typename Bstp<T>::Node* Bstp<T>::minimumNode(Node* nodePtr) {
	while (nodePtr->left)
		nodePtr = nodePtr->left;
	return nodePtr;
}

template <class T>
T Bstp<T>::maximum() {
	Node* nodePtr = root;
	while (nodePtr->right)
		nodePtr = nodePtr->right;
	return nodePtr->val;
}


template <class T>
bool Bstp<T>::search(T value) {
	if (root == nullptr)
		return false;
	else if (root->val == value)
		return true;
	else if (value < root->val) 
		return nodeSearch(root->left, value);
	else
		return nodeSearch(root->right, value);
}

template <class T>
bool Bstp<T>::nodeSearch(Node* nodePtr, T value) {
	if (nodePtr == nullptr)
		return false;
	else if (nodePtr->val == value)
		return true;
	else if (value < nodePtr->val)
		return nodeSearch(nodePtr->left, value);
	else
		return nodeSearch(nodePtr->right, value);
}

template <class T>
Bstp<T>::~Bstp() { deleteSubTree(root); }


template <class T>
void Bstp<T>::deleteSubTree(Node*& nodePtr) {
	if (nodePtr) {
		if (nodePtr->left)
			deleteSubTree(nodePtr->left);
		if (nodePtr->right)
			deleteSubTree(nodePtr->right);
		delete nodePtr;
	}
}

template <class T>
void Bstp<T>::insert(T value) {
	Node* newNode = new Node{ value };
	insertNewNode(root, newNode);
}

template <class T>
void Bstp<T>::insertNewNode(Node*& nodePtr, Node*& newNode) {
	if (nodePtr == nullptr) {
		nodePtr = newNode;
	}
	else {	
		newNode->p = nodePtr;
		if (newNode->val < nodePtr->val)
			insertNewNode(nodePtr->left, newNode);
		else
			insertNewNode(nodePtr->right, newNode);
	}
}

template <class T>
void Bstp<T>::inOrderTreeWalk(Node* x) {
	if (x) {
		inOrderTreeWalk(x->left);
		if (x->p)
			std::cout << "parent node value: " << x->p->val << '\n';
		else 
			std::cout << "parent node value: nullptr" << '\n';
		std::cout << "node value: " << x->val << '\n';
		std::cout << "left child value: ";
		if (x->left)
			std::cout << x->left->val;
		else
			std::cout << "nullptr";
		std::cout << " --- right child value: ";
		if (x->right)
			std::cout << x->right->val << '\n';
		else
			std::cout << "nullptr\n";
		
		inOrderTreeWalk(x->right);
	}
}

template <class T>
void Bstp<T>::inOrderTreeWalk() {
	inOrderTreeWalk(root);
}

int main() {
	//Bst<int> myTree{};
	//myTree.insertNode(10);
	//myTree.insertNode(5);
	//myTree.insertNode(16);
	//myTree.insertNode(7);
	//myTree.insertNode(3);
	//myTree.insertNode(11);
	//myTree.insertNode(18);
	//myTree.insertNode(1);
	//myTree.insertNode(2);
	//myTree.insertNode(6);
	//myTree.insertNode(8);
	//myTree.insertNode(17);
	//myTree.insertNode(12);
	//myTree.displayInOrder();
	//std::cout << '\n';
	//myTree.displayPreOrder();
	//std::cout << '\n';
	//myTree.displayPostOrder();
	//std::cout << '\n';
	Bstp<int> myTree2{};
	myTree2.insert(20);
	myTree2.insert(40);
	myTree2.insert(10);
	myTree2.insert(11);
	myTree2.insert(8);
	myTree2.insert(30);
	myTree2.insert(31);
	myTree2.iterativeInsert(1);
	myTree2.inOrderTreeWalk();
	
	int search1 = 1;
	int search2 = 10;
	std::cout << "\nsearch for " << search1 << ": " << myTree2.search(search1) << '\n';
	std::cout << "search for " << search2 << ": " << myTree2.search(search2) << '\n';
	std::cout << "max: " << myTree2.maximum() << " min: " << myTree2.minimum() << '\n';
	myTree2.successorTest(30);
	myTree2.predecessorTest(20);
}