#include "BST.h"

BST::BST(){
  root = nullptr; //sets root as empty
}

BST::~BST(){
  clear(); //clears tree
}

NodeInterface* BST::getRootNode() const {
  return root;
}

bool BST::add(int data){
	if(root == nullptr){ //adds root if none found
		Node* temp = new Node(data);
		root = temp;
		return true;
	} else if(addHelper(this->root, data)){ //base case if already found
		return true;
	} else{
		return false;
	}
}

bool BST::addHelper(Node *&node, int data){
	if(node == nullptr){ //adds node if empty
		node = new Node(data);
		return true;
	} else if(node->getData() < data){	//recursively move right
			return addHelper(node->rightChild, data);
	} else if(node->getData() > data){	//recursively move left
			return addHelper(node->leftChild, data);
	} else{
			return false;
	}
}

bool BST::remove(int data){
	return removeHelper(root,data); //call the helper function
}

bool BST::removeHelper(Node *&node, int data){
	if(node == nullptr){ //node cannot be removed bc it doesnt exist
		return false;
	} else if(node->data == data){ //if the ndoe exists
		if(node->rightChild == nullptr && node->leftChild == nullptr){ //if the node is leaf
			Node* tempNode = node;
			node = nullptr;
			delete tempNode;
			return true;
		} else if(node->rightChild != nullptr && node->leftChild == nullptr){ //if the node only has a right child
			Node* tempNode = node;
			node = node->rightChild;
			delete tempNode;
			return true;
		} else if(node->rightChild == nullptr && node->leftChild != nullptr){ //if the ndoe only has a left child
			Node* tempNode = node;
			node = node->leftChild;
			delete tempNode;
			return true;
		} else{	//if the node has both children
			node->data = traverseTree(node->leftChild);
      return removeHelper(node->leftChild, node->data);
		}
	} else if(data < node->data){ //if the data to be removed is less than the current node
		return removeHelper(node->leftChild, data);
	} else{ //if the data to be removed is more than the current node
    return removeHelper(node->rightChild, data);
  }
}

int BST::traverseTree(Node *node){
	if(node == nullptr){
    return -1;
  }
	int nodeIndex = node->data;
	Node* left = node->leftChild;
	if(left != nullptr){ //move left
		int leftVal = traverseTree(left);
		if(leftVal > nodeIndex){
			nodeIndex = leftVal;
		}
	}
	Node* right = node->rightChild;
	if(right != nullptr){ //move right
		int rightVal = traverseTree(right);
		if(rightVal > nodeIndex){
			nodeIndex = rightVal;
		}
	}
  return nodeIndex;
}

void BST::clear(){
	clearHelper(this->root);
	this->root = nullptr;
}

void BST::clearHelper(Node *node){
	if(node != nullptr){
		clearHelper(node->getLeft()); //move left
		clearHelper(node->getRight()); //move right
		delete node;
	}
}