#include "adt.h"
#include <stdlib.h>
#include <stdio.h>
treeNode* createTree(void) {
  return NULL;
}

// Algorithm:
// 1. If tree is not empty,
//// 2. If key of the current node is greater than the key the algorithm is searching for,
////// 3. Returns a call for this algorithm using the left-child of the current tree as an argument.
//// 4. Else if the key of the current node is smaller than the key the algorithm is searching for,
////// 5. Returns a call for this algorithm using the right-child of the current tree as an argument.
// 6. Returns tree.

treeNode* searchNode(treeNode* tree, int key) {
  if (tree != NULL) {
    if (tree->key > key) {
      printf("left\n");
      return searchNode(tree->left, key);
    } else if (tree->key < key) {
      printf("right\n");
      return searchNode(tree->right, key);
    }
  }
  return tree;
}

// Algorithm:
// 1. If tree is empty, insert key in tree.
// 2. Else
//// 3. If the key we're inserting is smaller than the current key,
////// 4. Call this algorithm using the left-child of the current tree as an argument and assign the return to left-child.
//// 5. Else if the key we're inserting is higher than the current key,
////// 6. Call this algorithm using the right-child of the current tree as an argument and assign the return to right-child.
// 7. Return tree.

treeNode* insertNode(treeNode* tree, int key) {
  if (tree == NULL) {
    tree = (treeNode*)malloc(sizeof(treeNode));
    tree->key = key;
    tree->left = NULL;
    tree->right = NULL;
  } else {
    if (tree->key > key) {
      tree->left = insertNode(tree->left, key);
    } else if (tree->key < key) {
      tree->right = insertNode(tree->right, key);
    }
  }
    return tree;
}

treeNode* removeNode(treeNode* tree, int key) {
  treeNode* auxTree;
  if (tree == NULL) {
    return NULL;
  } else if (tree->key != key) {
    tree->left = removeNode(tree->left, key);
    tree->right = removeNode(tree->right, key);
  } else if (tree->key == key) {
    if (tree->left == NULL && tree->right == NULL) {
      free(tree);
      return NULL;
    } else if (tree->left == NULL || tree->right == NULL) {
      if (tree->left == NULL) {
        auxTree = tree->right;
      } else {
        auxTree = tree->left;
      }
      free(tree);
      return auxTree;
    } else {
      auxTree = tree->right;
      while (auxTree->left != NULL) {
        auxTree = auxTree->left;
      }
      tree->key = auxTree->key;
      tree->right = removeNode(tree->right, auxTree->key);
    }
  }
  return tree;
}

void destroyTree(treeNode* tree) {
  if (tree != NULL) {
    destroyTree(tree->left);
    destroyTree(tree->right);
    free(tree);
  }
}
