#ifndef _ADTH_
#define _ADTH_

typedef struct treeNode {
	int key;
	struct treeNode* left;
	struct treeNode* right;
} treeNode;

treeNode* createTree(void);
// Creates an empty tree.
// Returns a tree with value NULL.

treeNode* searchNode(treeNode* tree, int key);
// Searchs for a node in a tree with the same info of the one passed through argument.
// If the node exists, returns a pointer for the node.
// If it doesn't exist, returns NULL. 

treeNode* insertNode(treeNode* tree, int key);
// Insert a node in the binary search tree if and only if the node doesn't currently exists in the tree.
// Returns a tree.

treeNode* removeNode(treeNode* tree, int key);
// Insert a node in the binary search tree if and only if the node doesn't currently exists in the tree.
// Returns a tree.


void destroyTree(treeNode* tree);
// Destroy a tree and clear all the memory used by it.
// Returns nothing.
int height(treeNode* tree);

int balance(treeNode* tree);

int leafCounter(treeNode* tree);

#endif
