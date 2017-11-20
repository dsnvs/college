#include "adt.h"
#include <stdlib.h>
#include <stdio.h>
treeNode* createTree(void) {
  return NULL;
}

// Algorithm:
// 1. If passed tree is empty, returns NULL and stop. Else:
// 2. If the root of the tree have the value for which the algorithm is looking, returns the tree pointer. Else:
// 3. Searchs (recursively) for the info starting by the left subtree of the tree passed through argument.
//// 3.1 If the node is found, returns the pointer. Else:
//// 3.2 Searchs the right subtree and returns the pointer if it founds the node. Else:
//// 3.3 Returns NULL.


treeNode* searchNode(treeNode* tree, int info) {
  treeNode* left;
  treeNode* right;
  if (tree == NULL) {
    printf("NULL");
    return NULL;
  } else if (tree->info == info) {
    printf("INFO");
    return tree;
  } else {
    printf("BRANCH");
    left = searchNode(tree->left, info);
    if (left != NULL) {
      return left;
    } else {
      right = searchNode(tree->right, info);
      if (right != NULL) {
        return right;
      } else {
        return NULL;
      }
    }
  }
}


treeNode* insertRoot(treeNode* tree, int info) {
  if (tree == NULL) {
    tree = (treeNode*)malloc(sizeof(treeNode));
    tree->info = info;
    tree->left = NULL;
    tree->right = NULL;
  } 
  return tree;
}

// Algorithm:
// 1. Searchs for a node with the same value passed through "parentInfo".
// 2. If the value is found, check if the left subtree of that value is NULL.
// 2.1 If yes,  creates a new node with "newInfo", assigns it as the left node of the subtree found and returns 0. Else:
// 2.2 return 1.

int insertLeft(treeNode* tree, int newInfo, int parentInfo) {
  treeNode* parent;
  parent = searchNode(tree, parentInfo);
  if (parent != NULL) {
    if (parent->left == NULL) {
      parent->left = (treeNode*)malloc(sizeof(treeNode));
      parent->left->info = newInfo;
      parent->left->left = NULL;
      parent->left->right = NULL;
      return 0;
    } else {
      return 1;
    }
  } else {
    return 1;
  }
}

// Algorithm:
// 1. Searchs for a node with the same value passed through "parentInfo".
// 2. If the value is found, check if the right subtree of that value is NULL.
// 2.1 If yes,  creates a new node with "newInfo", assigns it as the right node of the subtree found and returns 0. Else:
// 2.2 return 1.

int insertRight(treeNode* tree, int newInfo, int parentInfo) {
  treeNode* parent;
  parent = searchNode(tree, parentInfo);
  if (parent != NULL) {
    if (parent->right == NULL) {
      parent->right = (treeNode*)malloc(sizeof(treeNode));
      parent->right->info = newInfo;
      parent->right->left = NULL;
      parent->right->right = NULL;
      return 0;
    } else {
      return 1;
    }
  } else {
    return 1;
  }
}

void destroyTree(treeNode* tree) {
  if (tree != NULL) {
    destroyTree(tree->left);
    destroyTree(tree->right);
    free(tree);
  }
}

treeNode* removeLeaf(treeNode* tree, int info) {
  treeNode* newTree;
  if (tree != NULL) {
    if (tree->info == info) {
      if (tree->left == NULL && tree->right == NULL) {
        free(tree);
        return NULL;
      } else {
        return tree;
      }
    } else {
      tree->left = removeLeaf(tree->left, info);
      tree->right = removeLeaf(tree->right, info);
    }
  }
  return tree;
}

