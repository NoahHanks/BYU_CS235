#include "NodeInterface.h"

class Node : public NodeInterface {
public:
	Node(int value, Node* l = nullptr, Node* r = nullptr){
		data = value;
		leftChild = l;
		rightChild = r;
	}
	~Node(){}

	int getData() const;

	NodeInterface * getLeftChild() const;
	NodeInterface * getRightChild() const;

	Node *&getRight();
	Node *&getLeft();

	Node* leftChild;
    Node* rightChild;
    int data;
};