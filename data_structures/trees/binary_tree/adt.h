#ifndef _ADTH_
#define _ADTH_

typedef struct treeNode {
	int info;
	struct treeNode* left;
	struct treeNode* right;
} treeNode;

treeNode* createTree(void);
// Creates an empty tree.
// Returns a tree with value NULL.

treeNode* searchNode(treeNode* tree, int info);
// Searchs for a node in a tree with the same info of the one passed through argument.
// If the node exists, returns a pointer for the node.
// If it doesn't exist, returns NULL. 

treeNode* insertRoot(treeNode* tree, int info);
// Inserts a node as the root of a tree if the tree is empty.
// Returns 0 if success or 1 if the function fails, but modifies the tree.

int insertLeft(treeNode* tree, int newInfo, int parentInfo);
// Inserts a node on the left side of a parent passed through argument.
// Returns 0 if success or 1 if the function fails, but modifies the tree.

int insertRight(treeNode* tree, int newInfo, int parentInfo);
// Inserts a node on the right side of a parent passed through argument.
// Returns 0 if success or 1 if the function fails, but modifies the tree.

void destroyTree(treeNode* tree);
// Destroy a tree and clear all the memory used by it.
// Returns nothing.

#endif
