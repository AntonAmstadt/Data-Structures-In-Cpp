#ifndef CLASSICBST_H
#define CLASSICBST_H

#include <stack>

//Binary Search Tree class (with no parent pointer)
template <class T>
class Bst {
	struct Node {
		T val;
		Node* left;
		Node* right;
		Node(T value) : val{ value }, left{ nullptr }, right{ nullptr }{}
	};
	Node* root;

	void insert(Node*&, Node*);
	void destroySubTree(Node*);
	void deleteNode(T, Node*&);
	void makeDeletion(Node*&);
	void displayInOrder(Node*) const;
	void displayPreOrder(Node*) const;
	void displayPostOrder(Node*) const;
public:
	Bst() : root{ nullptr } {} 
	~Bst() { destroySubTree(root); }

	void insertNode(T);
	bool searchNode(T);
	void remove(T);

	void displayInOrder() const { displayInOrder(root); }
	void displayPreOrder() const { displayPreOrder(root); }
	void displayPostOrder() const { displayPostOrder(root); }

	//iterative in order tree walk
	void itInOrder();
};

template <class T>
void Bst<T>::insertNode(T val) {
	Node* newNode{ new Node{val} };
	insert(root, newNode);
}

template <class T>
void Bst<T>::insert(Node*& nodePtr, Node* newNode) { //void Bst<T>::insert(Node*& nodePtr, Node*& newNode) //reference didn't make sense to me
	if (!nodePtr)
		nodePtr = newNode;
	else if (newNode->val < nodePtr->val)
		insert(nodePtr->left, newNode);
	else
		insert(nodePtr->right, newNode);
}

template <class T>
void Bst<T>::displayInOrder(Node* nodePtr) const {
	if (nodePtr) {
		displayInOrder(nodePtr->left);
		std::cout << nodePtr->val << ' ';
		displayInOrder(nodePtr->right);
	}
}

template <class T>
void Bst<T>::displayPreOrder(Node* nodePtr) const {
	if (nodePtr) {
		std::cout << nodePtr->val << ' ';
		displayPreOrder(nodePtr->left);
		displayPreOrder(nodePtr->right);
	}
}

template <class T>
void Bst<T>::displayPostOrder(Node* nodePtr) const {
	if (nodePtr) {
		displayPostOrder(nodePtr->left);
		displayPostOrder(nodePtr->right);
		std::cout << nodePtr->val << ' ';
	}
}

template <class T>
void Bst<T>::destroySubTree(Node* nodePtr) {
	if (nodePtr) {
		if (nodePtr->left)
			destroySubTree(nodePtr->left);
		if (nodePtr->right)
			destroySubTree(nodePtr->right);
		delete nodePtr;
	}
}

template <class T>
void Bst<T>::remove(T value) {
	deleteNode(value, root);
}

template <class T>
void Bst<T>::deleteNode(T value, Node*& nodePtr) {
	if (!nodePtr) return;
	else if (value < nodePtr->val)
		deleteNode(value, nodePtr->left);
	else if (value > nodePtr->val)
		deleteNode(value, nodePtr->right);
	else
		makeDeletion(nodePtr);
}

//seems dubious
template <class T>
void Bst<T>::makeDeletion(Node*& nodePtr) {
	Node* temp{ nullptr };
	//nodePtr = nullptr handled by deleteNode, but I'll be extra safe
	if (!nodePtr)
		std::cout << "can't delete empty node\n";
	else if (nodePtr->right == nullptr) {
		temp = nodePtr;
		nodePtr = nodePtr->left;
		delete temp;
	}
	else if (nodePtr->left == nullptr) {
		temp = nodePtr->right;
		delete temp;
	}
	else {
		temp = nodePtr->right;
		while (temp->left)
			temp = temp->left;
		temp->left = nodePtr->left;
		temp = nodePtr;
		nodePtr = nodePtr->right;
		delete temp;
	}

}

template <class T>
bool Bst<T>::searchNode(T value) {
	Node* nodePtr{ root };
	while (nodePtr) {
		if (nodePtr->val == value)
			return true;
		else if (value < nodePtr->val)
			 nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return false;
}

template <class T>
void Bst<T>::itInOrder() {
	std::stack<Node*> s;
	Node* cur = root;
	while (cur || s.empty() == false) {
		while (cur) {
			s.push(cur);
			cur = cur->left; 
		}
		cur = s.top();
		s.pop();
		std::cout << cur->val << ' ';
		cur = cur->right;
	}
	
}


#endif
