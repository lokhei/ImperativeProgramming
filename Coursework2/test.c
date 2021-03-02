#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> 


node *create(){
  node *create(){
    char x[10];
    int i = 0, input; 
	node *p = NULL;
	input = fgetc(stdin);
    while (input != EOF && input != '\n') {
            x[i] = input;
            i++;
            input = fgetc(stdin);

    }
	
    p = (node*) malloc(sizeof(node));
    for(int j = 0;j < i;j++){
		if (x[j] == '\n') return p;
        p-> key = atoi(&x[j]);
	    p->left = NULL;


    }
    p->right = NULL;
    return p;
}




////
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> 


/* A binary tree node has data, pointer to left child 
and a pointer to right child */
typedef struct node { 
	int key; 
	struct node *left; 
	struct node *right; 
} node;

// naturally sorted binary tree
typedef struct tree {
  node *root;
} tree;

// Calculate depth of tree
int treeDepth(struct node* node) { 
if (node == NULL) //if empty tree return 0
	return 0; 
else { 
	// calculate depth of each subtree */
	int leftDepth = treeDepth(node->left); 
	int rightDepth = treeDepth(node->right); 

	//use the larger one 
	if (leftDepth > rightDepth) return(leftDepth + 1); 
	else return(rightDepth + 1); 
  } 
} 

// Count the number of nodes in tree
int numOfNodes(node *p) {
  int n = 0;
  if (p != NULL) n += numOfNodes(p->right) + numOfNodes(p->left) + 1;
  return n;
}

// create a new node with key value and no left or right node
// node *newNode(int value) { 
// 	node *p = malloc(sizeof(node)); 
// 	*p = (node){value, NULL, NULL};
// 	return(p); 
// }


	
int main(int n, char *args[n]) {
	if (n < 2){
		printf("Not enough arguments. Pease input like this:./network 1-2,1-3,2-4.\n");
		return 0;
	}
	int i = 0;
	const char s[2] = ",";
	char *token;

	// get the first token
	token = strtok(args[1], s);

	// walk through other tokens
	while( token != NULL ) {
		printf( " %s\n", token );
		i ++;
		token = strtok(NULL, s);
	}
	
	
	// printf("Tree depth: %d \n", treeDepth(root));
	// printf("Number of Nodes: %d \n", numOfNodes(root));

	
	return 0; 
} 
