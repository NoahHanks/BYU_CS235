#pragma once
#include "AVLInterface.h"
#include "Node.h"

using namespace std;

class AVL : public AVLInterface {
	private:
		Node* root;
        Node* traverseTree(Node* &node);
		void clearHelper(Node* node);
		int getHeightInt(Node* node);
		bool addHelper(Node* &node, int val);
		void rotateLeft(Node* &node);
		void rotateRight(Node* &node);
		void rotateLeftRight(Node* &node);
		void rotateRightLeft(Node* &node);
		bool rebalance(Node* &node, int val);
		bool removeHelper(Node* &node, int val);

	public:
		AVL();
		~AVL();

		NodeInterface* getRootNode() const;
		bool add(int data);
		bool remove(int data);
		void clear();
};
