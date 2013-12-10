#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct N{
	int value; 		// integer value of a node
	int visited; 	        // flag 0/1 - for DFS
	int index;		// order of the inserted number
	struct N* left;
	struct N* right;
} tree;

void readContent( char *fileName );
tree *createNode( int value, int index );
tree *addNode( tree *, tree * );
void treeDFS( tree *root);
void levelOrderTraversal(tree *root);
int search(tree *root, int target);
void displayTree(tree *root);
int tracePath( tree *node, int target, int count);


tree *root;


// main
int main( int argc, char * argv[] ) {
	argc != 2 ? printf("No file specified.\n") :
	readContent( argv[1] );
	printf("\n\nDepth First Search: ");
	treeDFS( root);
	printf("\n\nLevel Order Traversal: ");
	levelOrderTraversal(root);
	printf("\n\nTree in sorted order: ");
	displayTree(root);

	int findMe=1;
	findMe = getSearchParameters();

	while (findMe > 0) {
		int found = search(root, findMe);
		found ? (printf("Target node %d found through the following path: \n", findMe)
		, tracePath(root, findMe, 0)):
		printf("Target node %d not found", findMe);
		findMe = getSearchParameters();
	}
}

// read file
void readContent( char *fileName ){

	FILE *f; f=fopen(fileName,"r"); int i = 0;
	while(!feof(f)) {
		char *word = malloc(sizeof(char)*20);
		fscanf(f, "%s", word);
		
		char *sc = strrchr(word, ';');
		if (sc != NULL)
			*sc = '\0';
		if (atoi(word))
			root = addNode( root, createNode( atoi(word), i++ ) );
	} fclose(f);
} 


// create node
tree * createNode( int value, int index ) {

	printf("Adding node: %d\n", value);
	tree *newBranch     = (tree *)malloc(sizeof(tree));
	newBranch->left		= newBranch->right = NULL;
	newBranch->value	= value;
	newBranch->index	= index;
	newBranch->visited	= 0;
	return newBranch;

}


// add node
tree * addNode( tree * root, tree * branch ) {

	return !root  ? branch : 
	(root->value  > branch->value) ?
	(root->left   = addNode(root->left, branch), root):
	(root->value  < branch->value) ?
	(root->right  = addNode(root->right, branch), root):
	branch;

}


// print tree sorted
void displayTree(tree * root) {
    if (root) {

        displayTree(root->left);
        printf("(%d)",root->index);
        printf("[%d]  ",root->value);
        displayTree(root->right);

    }
}

// get number from user
int getSearchParameters() {
	printf("\n\nEnter the number for which you want to search: ");
	int findMe; scanf("%d", &findMe); return findMe;
}

// Search the tree
int search( tree * node, int target ) {
	return !node ? 0 : 
	target==node->value ? 1 : 
	target< node->value ? search(node->left, target) : 
	search(node->right, target);
}

//trace path of search
int tracePath( tree *node, int target, int count) {

	if (target < node->value) {
		printf("(%d) hop to the left\n", count);
		tracePath(node->left, target, ++count);
	} else if (target > node->value) {
		printf("(%d) hop to the right\n", count);
		tracePath(node->right, target, ++count);
	}
}

// print depth first
void treeDFS( tree *root) {

    if (root) {
        printf("(%d) ",root->index);
        printf("[%d] ",root->value);
        treeDFS(root->left);
        treeDFS(root->right);
    }

}

// print
void levelOrderTraversal( tree *root) {

    if (root) {
    	levelOrderTraversal(root->left);
    	levelOrderTraversal(root->right);
    	if (root->visited == 0) {
	        printf("(%d)",root->index);
	        printf("[%d] ",root->value);
	        root->visited=1;
    	}
    }
}


