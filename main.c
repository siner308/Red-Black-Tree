#include <stdio.h>
#include "rbtree.h"


int main(void){
	int nMenu = 0;
	int key = -999;
	node *root = 0;

	while (nMenu != 5){
		printf("1.insert 2.delete 3.search 4.print 5.exit : ");
		scanf("%d", &nMenu);
		key = -999;

		if ((nMenu >= 1) && (nMenu <= 3)){
			
			while (key == -999){
				printf("enter key : ");
				scanf("%d", &key);
			}

			if (nMenu == 1){
				root = insertNode(root, key);
			}

			else if (nMenu == 2){
				root = deleteNode(root, key);
			}

			else if (nMenu == 3){
				searchNode(root, key);
			}

			else{
				printf("wrong access {nMenu is not an integer (1 < nMenu < 3)}\n");
			}
		}

		else if (nMenu == 4){
			printTree(root);
			printf("\n");
		}

		else if (nMenu == 5){
			freeTree(root);
		}

		else{
			printf("wrong access (nMenu is not in range 1 to 5)\n");
		}
	}

	return 0;
}