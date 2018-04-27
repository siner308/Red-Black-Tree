/*
** rbtree.h
** red-black-tree
** 20180124 siner
*/

#ifndef _REDBLACK_H_
#define _REDBLACK_H_

#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#define CREATE_NEW_NODE malloc(sizeof(node));

typedef struct Node node;
struct Node{
	int key;
	node *left;
	node *right;
	node *parent;
	char color;
};

node *insertNode(node *root, int key);
node *insertCase1(node *root, node *n);
node *insertCase2(node *root, node *n);
node *insertCase3(node *root, node *n);
node *uncle(node *n);
node *grandparent(node *n);
node *insertCase4(node *root, node *n);
node *rotateLeft(node *root, node *n);
node *rotateRight(node *root, node *n);
node *insertCase5(node *root, node *n);
node *deleteNode(node *root, int key);
void searchNode(node *root, int key);
void printTree(node *root);
void freeTree(node *root);

// n : new node
// p : parent (parent of new)
// g : grandparent (parent of parent and uncle)
// u : uncle (another child of grandparent)

node *insertNode(node *root, int key){
	node *n = CREATE_NEW_NODE;
	node *leafL = CREATE_NEW_NODE;
	node *leafR = CREATE_NEW_NODE;
	node *tempRoot = root;
	node *temp = root;

	// init new
	n->key = key;
	n->color = 'R';

	// init leaves
	// left leaf
	n->left = leafL;
	leafL->parent = n;
	leafL->left = NULL;
	leafL->right = NULL;
	leafL->key = INT_MAX;
	leafL->color = 'B';

	// right leaf
	n->right = leafR;
	leafR->parent = n;
	leafR->left = NULL;
	leafR->right = NULL;
	leafR->key = INT_MAX;
	leafR->color = 'B';


	// first insert
	if (temp == NULL){
		root = n;
	}

	// not first insert
	else{
		// find leaf
		while (temp->key != INT_MAX){
			// go to left
			if (n->key < temp->key){
				temp = temp->left;
			}

			// go to right
			else if (n->key > temp->key){
				temp = temp->right;
			}

			else if (n->key == temp->key){
				printf("%d is already exist\n", temp->key);
				free(leafL);
				free(leafR);
				free(n);
				return root;
			}

			else{
				printf("wrong access (insert key)\n");
			}
		}

		// link to parent
		n->parent = temp->parent;

		// link to left
		if (temp->parent->left == temp){
			temp->parent->left = n;
		}

		// link to right
		else{
			temp->parent->right = n;
		}

		free(temp);

	}

	tempRoot = insertCase1(root, n);

	while (tempRoot->parent != NULL){
		tempRoot = tempRoot->parent;
	}

	root = tempRoot;

	return root;
} // end of insertNode

node *insertCase1(node *root, node *n){
	//printf("1 ");
	// n is root
	if (n->parent == NULL){

		// root is black
		n->color = 'B';
	}

	// n is not root
	else{
		insertCase2(root, n);
	}

	return root;
} // end of insertCase1

node *insertCase2(node *root, node *n){
	//printf("2 ");
	// p is red (grandparent is exist)
	if (n->parent->color == 'R'){
		insertCase3(root, n);
	}

	return root;
} // end of insertCase2

node *insertCase3(node *root, node *n){
	//printf("3 ");
	node *u = uncle(n);
	node *g = grandparent(n);

	// u is red
	if (u->color == 'R'){
		n->parent->color = 'B';
		u->color = 'B';
		g->color = 'R';
		insertCase1(root, g);
	}

	// u is black (or leaf)
	else{
		insertCase4(root, n);
	}

	return root;
} // end of insertCase3

node *uncle(node *n){
	//printf("u ");
	node *g = grandparent(n);

	// p is not root
	if (g != NULL){

		// p is left from g
		if (g->left == n->parent){
			return g->right;
		}

		// p is right from g
		else{
			return g->left;
		}
	}

	// parent is root
	else{
		return NULL;
	}
} // end of uncle

node *grandparent(node *n){
	//printf("g ");
	// n is not root
	if (n->parent != NULL){
		return n->parent->parent;
	}

	// n is root
	else{
		return NULL;
	}
} // end of grandparent

node *insertCase4(node *root, node *n){
	//printf("4 ");
	node *p = n->parent;
	node *g = grandparent(n);

	// p is left from g && n is right from p
	if ((g->left == p) && (p->right == n)){
		rotateLeft(root, n);
		n = n->left;
	}

	else if ((g->right == p) && (p->left == n)){
		rotateRight(root, n);
		n = n->right;
	}

	insertCase5(root, n);

	return root;
} // end of insertCase4

node *rotateLeft(node *root, node *n){
	//printf("rL ");
	node *g = grandparent(n);
	node *p = n->parent;

	p->right = n->left;
	n->left->parent = p;

	n->left = p;
	p->parent = n;

	g->left = n;
	n->parent = g;

	return root;
} // end of rotateLeft

node *rotateRight(node *root, node *n){
	//printf("rR ");
	node *g = grandparent(n);
	node *p = n->parent;

	p->left = n->right;
	n->right->parent = p;

	n->right = p;
	p->parent = n;

	g->right = n;
	n->parent = g;

	return root;
} // end of rotateRight

node *insertCase5(node *root, node *n){
	//printf("5 ");
	node *g = grandparent(n);
	node *u = uncle(n);
	node *p = n->parent;
	node *temp = 0;

	// rotate right
	if (p->left == n){
		// g is not root
		if (g->parent){

			// p <- g's parent
			if (g->parent->left == g){
				g->parent->left = p;
			}

			else{
				g->parent->right = p;
			}

			// p -> g's parent
			p->parent = g->parent;
		}

		else{
			p->parent = NULL;
		}

		// g -> p's right (leaf)
		g->left = p->right;
		// g <- p's right (leaf)
		p->right->parent = g;
		// g -> p
		g->parent = p;
		// g <- p
		p->right = g;
	}

	// rotate left
	else{
		// g is not root
		if (g->parent){

			// p <- g's parent
			if (g->parent->left == g){
				g->parent->left = p;
			}

			else{
				g->parent->right = p;
			}

			// p -> g's parent
			p->parent = g->parent;
		}
		else{
			p->parent = NULL;
		}

		// g -> p's right (leaf)
		g->right = p->left;
		// g <- p's right (leaf)
		p->left->parent = g;
		// g -> p
		g->parent = p;
		// g <- p
		p->left = g;
	}

	g->color = 'R';
	p->color = 'B';
	u->color = 'B';
	n->color = 'R';

	return root;
} // end of insertCase5


node *deleteNode(node *root, int key){
	printf("you are not prepared\n");
}

void searchNode(node *root, int key){
	node *temp = root;

	while (temp->key != INT_MAX){
		if (key < temp->key){
			temp = temp->left;
		}
		else if (key > temp->key){
			temp = temp->right;
		}
		else{
			printf("there is %d\n", temp->key);
			break;
		}
	}

	if (temp->key == INT_MAX){
		printf("there is no %d\n", key);
	}
}

void printTree(node *root){
	if (root->key != INT_MAX){
		printTree(root->left);
		printTree(root->right);
		printf("%d ", root->key);
	}
}

void freeTree(node *root){
	if (root){
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

#endif