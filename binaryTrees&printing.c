
/* Ben Baker
Lab7
LAB CODE: 

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct N{
	int data;
	struct N* left;
	struct N* right;
}tree;


tree * createBranch( int data );
tree * addBranch(tree * root, tree * branch);
tree * buildList( char *fileName );

void print_preorder(tree * root);
void print_inorder(tree * root);


int main( int argc, char * argv[] ) {

	tree *root = buildList( argv[1] );
	print_preorder(root);
	print_inorder(root);


}


tree * buildList( char *fileName ){

	tree *root = NULL;
	int fileSize, i, first =1; 
	FILE *f; f=fopen(fileName,"r"); 
	fscanf(f, "%d", &fileSize);

	for(i=0;i<fileSize;i++) {

		int data;
		fscanf(f, "%d", &data );
		root = addBranch( root, createBranch( data ) );

	} fclose(f); return root;
}


tree * createBranch( int data ) {

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

void print_preorder(tree * root) {
    if (root) {
        printf("%d\n",root->data);
        printf(".");
        print_preorder(root->left);
        printf(".");
        print_preorder(root->right);
    }
}

void print_inorder(tree * root) {
    if (root) {
        print_inorder(root->left);
        printf("%d\n",root->data);
        print_inorder(root->right);
    }
}




