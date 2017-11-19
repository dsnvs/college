#include <stdio.h>
#include "adt.h"

void main(void) {
  treeNode* tree;
  treeNode* searched;
  int option, info, info2;
  do{
    do {
      printf("Options: 1. Create a tree.\n2. Search a node.\n3. Insert root.\n4. Insert left.\n5. Insert right.\n6. Destroy tree.\n7. Quit!\n");
      scanf("%i", &option);
    } while (option > 7 || option < 1);
    switch(option) {
      case 1:
        tree = createTree();
        break;
      case 2:
        scanf("%i", &info);
        searched = searchNode(tree, info);
        if (searched != NULL) {
          printf("%i\n", searched->info);
        }
        break;
      case 3:
        scanf("%i", &info);
        tree = insertRoot(tree, info);
        break;
      case 4:
        scanf("%i", &info);
        scanf("%i", &info2);
        insertLeft(tree, info, info2);
        break;
      case 5:
        scanf("%i", &info);
        scanf("%i", &info2);
        insertRight(tree, info, info2);
        break;
      case 6:
        destroyTree(tree);
        break;
    }
  } while (option != 7);
};
