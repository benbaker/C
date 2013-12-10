#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct N{
	int data;
	struct N* left;
	struct N* right;
}tree;

tree * createNode( int data );
tree * addBranch(tree * root, tree * branch);
tree * buildTree( char *fileName );

int searchTree( tree *, int);
int longestBranch(tree *);
int countNodes(tree *);
int countLeafNodes(tree *);

void printPreorder(tree * root);
void printInorder(tree * root);

int main( int argc, char * argv[] ) {

  if (argc != 2) { printf("Insufficient arguments"); return 0; } 

	tree *root = buildTree( argv[1] );
	if (!root) { printf("Unable to open the file %s\n", argv[1]); return 0; }
	
	printf("\nTree nodes in pre order traversal:\n");
	printPreorder(root);
	// printInorder(root);
	printf("\n\n");
	
	printf("Longest branch has the length: %d:\n", longestBranch(root));
	printf("Number of leaves in the tree %d:\n", countLeafNodes(root));
	printf("\n");

	int findMe = getSearchParameters();
	int found  = searchTree(root, findMe);
	
	found ? printf("Number %d is present in the tree.\n", findMe):
	printf("Number %d is not present in the tree.\n", findMe);
	
	printPreorder(root);
    	printf("\n");
}

tree * buildTree( char *fileName ){

	tree *root = NULL;
	int fileSize, i, first =1; 
	FILE *f; f=fopen(fileName,"r"); 
	if (!f) return NULL;

	fscanf(f, "%d", &fileSize);

	for(i=0;i<fileSize;i++) {

		int data;
		fscanf(f, "%d", &data );
		root = addBranch( root, createNode( data ) );
	} 
	
	fclose(f); 
	return root;
}

tree * createNode( int data ) {

	tree *newBranch     = (tree *)malloc(sizeof(tree));
	newBranch->left		= newBranch->right = NULL;
	newBranch->data		= data;
	return newBranch;

}

tree * addBranch(tree * root, tree * branch) {

	return !root ? branch : 
	(root->data  > branch->data) ?
	(root->left   = addBranch(root->left, branch), root):
	(root->data  < branch->data) ?
	(root->right   = addBranch(root->right, branch), root):
	branch;
}

int countNodes(tree *branch ) {

    int i;  
    if (branch == NULL)         
        return(0);  
    i = 1 + countNodes(branch->left) + countNodes(branch->right); 
    return(i);                                

}

int countLeafNodes(tree *node ) {

	if(node == NULL)       
		return 0;
	if(node->left == NULL && node->right==NULL)      
		return 1;            
	else return countLeafNodes(node->left)
		  + countLeafNodes(node->right);      
}

int longestBranch(tree *root ) {

    if(root->left==NULL && root->right==NULL) //leaf
        return 0;
    else if(root->left!=NULL && root->right==NULL) 
        return( max(longestBranch(root->left),0)+1);
    else if(root->left==NULL && root->right!=NULL) 
        return( max(0,longestBranch(root->right)+1));
    else if(root->left->left==NULL && root->left->right==NULL && root->right->left==NULL&&root->right->right==NULL)
        return 1; 
    else
        return( max(longestBranch(root->right),longestBranch(root->left))+1);

}

int max(int a, int b) { return a > b ? a : b; }

int getSearchParameters() {
	printf("Enter the number for which you want to search: ");
	int findMe; scanf("%d", &findMe); return findMe;
}

int searchTree( tree * node, int target ) {

	return !node ? 0 : 
	target==node->data ? 1 : 
	target< node->data ? searchTree(node->left, target) : 
	searchTree(node->right, target);

}

void printPreorder(tree * root) {
	
    if (root) {
        printf("%d ",root->data);
        printPreorder(root->left);
        printPreorder(root->right);

    }
}

void printInorder(tree * root) {
	
    if (root) {
        printInorder(root->left);
        printf("%d ",root->data);
        printInorder(root->right);
    }
}

