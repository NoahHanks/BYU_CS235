#include "AVL.h"

AVL::AVL(){
	root = nullptr;
}

AVL::~AVL(){
	clear();
}

NodeInterface* AVL::getRootNode() const{
	return root;
}

bool AVL::add(int val){
  return addHelper(root, val);
}

bool AVL::addHelper(Node* &node, int val){
	if(node == nullptr){
		node = new Node(val);
		node->height = 0;
		return true;
  }
	if(node->val == val){
		return false;
	}
	if(node->val < val){
		bool rebalanced = addHelper(node->rightChild, val);
		if(rebalanced == true){
			if(node->getBalance() > 1){
				rotateLeft(node);
			}
			if(node->getBalance() < -1){
				rotateRight(node);
			}
		}
		return rebalanced;
  }
	else if(node->val > val){
		bool rebalancedAgain = addHelper(node->leftChild, val);
		if(rebalancedAgain == true){
			if(node->getBalance() > 1){
				rotateLeft(node);
			}
			if(node->getBalance() < -1){
				rotateRight(node);
			}
		}
		return rebalancedAgain;
	}
	if(node->getBalance() > 1){
		rotateLeft(node);
	}
	if(node->getBalance() < -1){
		rotateRight(node);
	}
	return false;
}

bool AVL::remove(int data){
	bool tempBool =  removeHelper(root,data);
	rebalance(root,data);
	return tempBool;
}

bool AVL::removeHelper(Node* &node, int val){
	bool removeLeft;
	bool removeRight;
	if(node == nullptr){
		return false;
	}
	if(val < node->val){
		removeLeft = removeHelper(node->leftChild, val);
		rebalance(node, val);
		return removeLeft;
	}
	if(val > node->val){
		removeRight = removeHelper(node->rightChild, val);
		rebalance(node, val);
		return removeRight;
	}
	if(node->leftChild == nullptr && node->rightChild == nullptr){
		delete node;
		node = nullptr;
		return true;
	}
	if(node->rightChild != nullptr && node->leftChild == nullptr){
		Node* tempNode = node->rightChild;
		delete node;
		node = tempNode;
		rebalance(node, val);
		return true;
	}
	if(node->rightChild == nullptr && node->leftChild != nullptr){
		Node* tempNode = node->leftChild;
		delete node;
		node = tempNode;
		rebalance(node, val);
		return true;
	}
	Node* tempNode = traverseTree(node->leftChild);
	tempNode->leftChild = node->leftChild;
	tempNode->rightChild = node->rightChild;
	delete node;
	node = tempNode;
	return true;
}

Node* AVL::traverseTree(Node* &node){
	if(node->rightChild == nullptr){
		Node*  tempNode = node;
		node = node->leftChild;
		return tempNode;
	}
	Node* tempNode = traverseTree(node->rightChild);
	rebalance(node, node->val);
	return tempNode;
}

bool AVL::rebalance(Node* &node, int val){
	if(node == nullptr){
		return false;
	}
	if(node->getBalance() > 1){
		rotateLeft(node);
	}
	else if(node->getBalance() < -1){
		rotateRight(node);
	}
	rebalance(node->leftChild, val);
	rebalance(node->rightChild, val);
	return false;
}

void AVL::clear(){
	clearHelper(root);
  root = nullptr;
} 

int AVL::getHeightInt(Node* node){
	if(node == nullptr){
		return 0;
	}
	else{
		return node->getHeight();
	}
}

void AVL::clearHelper(Node* node){
	if(node == nullptr){
		return;
	}
	if(node->leftChild != nullptr){
    clearHelper(node->leftChild);
    }
    if(node->rightChild != nullptr){
        clearHelper(node->rightChild);
    }
    delete node;
    return;
}

void AVL::rotateLeft(Node* &node){
	if(node == nullptr){
		return;
	}
	if(node->rightChild->getBalance() <= -1){
		rotateRightLeft(node->rightChild);
	}
	rotateLeftRight(node);
}

void AVL::rotateRight(Node* &node){
	if(node == nullptr){
		return;
	}
	if(node->leftChild->getBalance() >= 1){
		rotateLeftRight(node->leftChild);
	}
	rotateRightLeft(node);
}

void AVL::rotateLeftRight(Node* &node){
	Node* newNode = node->rightChild;
	node->rightChild = newNode->leftChild;
	newNode->leftChild = node;
	node = newNode;
}

void AVL::rotateRightLeft(Node* &node){
	Node* newNode = node->leftChild;
	node->leftChild = newNode->rightChild;
	newNode->rightChild = node;
	node = newNode;
}