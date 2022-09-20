#include "Node.h"

int Node::getData() const{
	return data;
}
NodeInterface * Node::getLeftChild() const{
	return leftChild;
}
NodeInterface * Node::getRightChild() const{
	return rightChild;
}
Node *& Node::getRight(){
	return rightChild;
}
Node *& Node::getLeft(){
	return leftChild;
}
