#pragma once
#include "NodeInterface.h"

class Node : public NodeInterface{
public:
	Node* leftChild;
	Node* rightChild;
	int val;
	int height;
	
	Node(int value){
		val = value;
		leftChild = nullptr;
		rightChild = nullptr;
		height = 0;
	}
	~Node(){}
	
	int getData() const{
		return val;
	}
	
	NodeInterface* getLeftChild() const{
		return leftChild;
	}
	
	NodeInterface* getRightChild() const{
		return rightChild;
	}
	
	int getHeight(){
		int leftHeight = 0;
		int rightHeight = 0;
		if(leftChild != nullptr){
			leftHeight = leftChild->getHeight();
		}
		if(rightChild != nullptr){
			rightHeight = rightChild->getHeight();
		}
		if(leftHeight > rightHeight){
			return leftHeight + 1;
		}
		else{
			return rightHeight + 1;
		}
	}
	
	int getBalance(){
		int rightHeight;
		int leftHeight;
		if(rightChild != nullptr){
			rightHeight = rightChild->getHeight();
		}
		else{
			rightHeight = 0;
		}
		if(leftChild != nullptr){
			leftHeight = leftChild->getHeight();
		}
		else{
			leftHeight = 0;
		}
		return rightHeight - leftHeight;
	}
};
