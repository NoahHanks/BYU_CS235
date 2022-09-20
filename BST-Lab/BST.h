#include "BSTInterface.h"
#include "Node.h"

using namespace std;

class BST : public BSTInterface {
	private:
		Node* root;
		bool addHelper(Node *&node, int data);
		void clearHelper(Node *node);
		bool removeHelper(Node *&node, int data);
		int traverseTree(Node *node);

	public:
		BST();
		~BST();

		NodeInterface * getRootNode() const;
		bool add(int data);
		bool remove(int data);
		void clear();
};