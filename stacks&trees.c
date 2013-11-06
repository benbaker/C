#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 200

/// This program makes a balanced binary search tree from a stack.

typedef struct N{int num;struct N *next;} data;

data * createNode 	( int );
data * insertNode	( data* , data* );
data * buildStack	( char* ); 
void   printStack 	( data * ); 
void   sortStack	( data * );
void   swap 		( data *x, data *y );
int    stackLength	( data * );
int*   storeNumbers	( data *head );

typedef struct M{int n;struct M* left;struct M* right;} tree;

tree * createTreeNode	( int n );
tree * addTreeNode		( tree * root, tree * branch );
void   printPreorder	( tree * root );
tree * buildTree		( int*a, int start, int end );
int    searchTree		( tree*, int );
void   printTree		( tree *root );


int main( int argc, char * argv[] ) {

	if (argc != 2) { printf("need more arguments\n"); return 0; } 

	printf("\nPrinting stack\n");
	data *head = buildStack( argv[1] );
	if (!head) { printf("unable to open the specified file"); return 0; }
	printStack (head);

	printf("Printing sorted stack\n");
	sortStack  (head); 
	printStack (head);

	int *nums = storeNumbers( head );
	printf("Printing balanced binary tree\n");
	tree *root; root = buildTree(nums, 0, stackLength( head ));
	printPreorder( root );
	int findMe = getSearchParameters();

	searchTree( root, findMe ) ?
	printf("Number %d was present in the tree.\n\n", findMe):
	printf("Number %d was NOT present in the tree.\n\n", findMe);

	return 0;

}


// Create new node
data * createNode( int number ) {
	data *newNode    	= (data *)malloc(sizeof(data));
	newNode->next = NULL; newNode->num  = number;
	return newNode;
}

// Add to stack
data * insertNode(data * head, data * node) {
	return !head ? node : (node->next = head, node);
}

// Build stack
data * buildStack( char *fileName ){
	data *head = NULL; int fileSize, i, first =1; FILE *f; 
	f=fopen(fileName,"r"); if (!f) return NULL; 
	fscanf(f, "%d", &fileSize);
	for(i=0;i<fileSize;i++) {
		int n; fscanf(f, "%d", &n );
		head = insertNode( head, createNode( n ) );
	} fclose(f); return head;
}

// Print stack
void printStack( data *nd ){
	nd ? (printf("%d->", nd->num),
	printStack(nd->next)): 
	printf("\n\n"); 
}

// Sort stack
void sortStack( data* head ) {
	data *node1, *node2;
	for(node1 = head;node1 != NULL ;node1 = node1->next) {
        for(node2 = node1; node2 != NULL; node2 = node2->next) {
            if(node1->num > node2->num) {
            	swap(node1, node2);
          	}
      	}
    }
}

// Swap nodes
void swap( data *a, data *b ) {
	intSwap(&(b->num), &(a->num));
} int intSwap( int *pa, int *pb ) { 
	int t = *pa; *pa = *pb; *pb = t; 
} 

// Get length of stack
int stackLength( data *nd ) {
    int i;  if (nd == NULL) return(0);  
    i = 1 + stackLength(nd->next); 
    return(i);                                
}

// Store numbers in array
int* storeNumbers(data *head) {

 	int *nums = malloc(sizeof(int)*MAX);
 	int i = 0;
	while (head) {
		nums[i] = head->num;
		head=head->next;
    	i++;
	} return nums;
}

// Build balanced tree from array
tree * buildTree(int*a, int start, int end ) {
	int middle = (end - start) / 2; tree *root;
	int i; for (i=0; i<middle; i++) {
		root = addTreeNode( root, createTreeNode( a[middle+i] ) );
		root = addTreeNode( root, createTreeNode( a[middle-i-1] ) );
	}
	return root;
}


// Create node
tree * createTreeNode( int data ) {
	tree *newBranch     = (tree *)malloc(sizeof(tree));
	newBranch->left		= newBranch->right = NULL;
	newBranch->n		= data;
	return newBranch;
}

// Add node to tree
tree * addTreeNode(tree * root, tree * branch) {
	return !root ? branch : 
	(root->n  > branch->n) ?
	(root->left   = addTreeNode(root->left, branch), root):
	(root->n  < branch->n) ?
	(root->right   = addTreeNode(root->right, branch), root):
	branch;
}

// Print tree
void printPreorder(tree * root) {
    if (root) {
        printf("%d ",root->n);
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

// get number from user
int getSearchParameters() {
	printf("\n\nEnter the number for which you want to search: ");
	int findMe; scanf("%d", &findMe); return findMe;
}

// Search the tree
int searchTree( tree * node, int target ) {
	return !node ? 0 : 
	target==node->n ? 1 : 
	target< node->n ? searchTree(node->left, target) : 
	searchTree(node->right, target);
}