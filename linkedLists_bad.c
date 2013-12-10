#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// -----------------------------------------------------------------------|
// DEFINE STRUCT 
// -----------------------------------------------------------------------|

int i;

typedef struct struct_bank { 
	int accountNumber; 
	char *name; 
	float amount; 
	struct struct_bank *next; 
}bank; 


// -----------------------------------------------------------------------|
// FUNCTION HEADERS
// -----------------------------------------------------------------------|

bank * buildList( char* );
bank * createNode( char * s, int acct, float amt ); 
bank * deleteNode( bank* head );
bank * insertNode( bank* head, bank* node ); 
bank * updateList( char *str, bank* head ); 

int 	 checkList( bank* head, char * s, int acct, float amt ); 
int 	 writeOutput( char * fileName, bank *head );
void 	 printList( bank *head );
void 	 err( char *);

// -----------------------------------------------------------------------|
// MAIN
// -----------------------------------------------------------------------|

int main( int argc, char * argv[] ) {

	// Verify args
	if (argc != 4) { 
		err("Not enough arguments."); 
		return 0; 
	} 

	// Build linked list form accounts file
	bank *head = buildList( argv[1] );
	printf("\nCreated linked list");
	printList(head);

	// update linked list from update file
	head = updateList(argv[2], head);
	printf("\nLinked list after update operation");
	printList(head);

	// delete all the negative accounts
	head = deleteNode(head);
	printf("\nLinked list after delete operation");
	printList(head);

 	int wroteToFile = writeOutput(argv[3], head); 	
 	wroteToFile ? printf("File written\n"): printf("File not written\n");

} 

// -----------------------------------------------------------------------|
// LIST STUFF
// -----------------------------------------------------------------------|

bank * buildList( char *fileName ){

	// Open file & get size
	FILE *f; int fileSize; f=fopen(fileName,"r"); 
	fscanf(f, "%d", &fileSize);
	// Instantiate variables for struct
	int first =1; bank *firstNodePtr; bank *head;
	// Walk file & make nodes
	for(i=0;i<fileSize;i++) {
		int acct; char *name; float amt; 
		name = malloc(sizeof(char)*20);
		// Read element properties
		fscanf(f, "%d%s%f", &acct, name, &amt);
		// Create node from element properties
		bank *thisNodePtr;
		thisNodePtr = createNode( name, acct, amt );
		// Hold pointer to first node
		if (first) { 
			firstNodePtr = thisNodePtr; 
			head = NULL; 
			first=0; 
		}
		// Put node in linked list
		head = insertNode(head, thisNodePtr);
	}
	fclose(f); 
	return firstNodePtr;
}

bank * updateList( char *updateFile, bank *head ){

	// Open file & get size
	FILE *f2; int fileSize; f2=fopen(updateFile,"r"); 
	fscanf(f2, "%d", &fileSize);
	// Walk file & make nodes
	for(i=0;i<fileSize;i++) {
		int acct; char *name; float amt; 
		name = malloc(sizeof(char)*20);
		// Read element properties
		fscanf(f2, "%d%s%f", &acct, name, &amt);
		int nodeFound = 0;
		nodeFound = checkList(head, name, acct, amt);
		if (nodeFound) { 
			// printf("Updated %s\n", name);
		}  else {
			// printf("Creating %s\n", name);
			// Create node from element properties
			bank *newNode;
			newNode = createNode( name, acct, amt );
			// Put node in linked list
			head = insertNode(head, newNode);
		}
	} 
	fclose(f2); 
	return head;
}

int checkList( bank *head, char * s, int acct, float amt ){
	bank * currentNode;
	currentNode = head;
	int found =0;
	while (currentNode->next != NULL) {
		// printf("Node: %s\n", s);
		// printf("%-6d%-6d\n", acct, currentNode.accountNumber);
		if(currentNode->accountNumber == acct) {
			currentNode->amount += amt;
			return 1;
		}
		currentNode = currentNode->next;
	}
	return 0;
}

void printList( bank *head ){
	bank *currentNode;
	currentNode = head;
	printf("\n\n");
	while (currentNode->next) {
		printf("%-7d%-10s%-8.2f\n"
		       , currentNode->accountNumber
		       , currentNode->name
		       , currentNode->amount);
		currentNode = currentNode->next;
	} printf("\n");
}

// -----------------------------------------------------------------------|
// NODES 
// -----------------------------------------------------------------------|

bank * createNode( char * s, int acct, float amt ){

	bank *newNodePtr;newNodePtr 	= (bank *)malloc(sizeof(bank));
	newNodePtr->name					= s;
	newNodePtr->accountNumber  	= acct;
	newNodePtr->amount  				= amt;
	// printf("New: %s\t%f\t%d\n", s, amt, acct);

	return newNodePtr;
}

bank * insertNode( bank* head, bank* node ){

	bank *thisNode, *lastNode;
	thisNode = head;
	if (head == NULL){ return node;  }
	while (thisNode->next) {
		if (strcmp( thisNode->name, node->name ) > 0){
			if (thisNode == head){
			node->next = head;
			return node;
			} else {
			node->next = thisNode;
			lastNode->next = node;
			return head;
			}
		}
		lastNode = thisNode;
		thisNode=thisNode->next;
	}
	printf(" \t");
	node->next=NULL;
	thisNode->next = node;
	return head;
}


bank * deleteNode( bank* head ){

	bank *thisNode, *lastNode;
	thisNode = head;
	// Delete all nodes with negative balances
	while (thisNode->next) {
		if (thisNode->amount < 0 ) {
	
			if (thisNode->accountNumber == head->accountNumber) {
				// is it the head?
				bank *tmp;
				tmp = head;
				head = thisNode->next;
				// free(tmp);
			}
			// Not the head
			lastNode->next = thisNode->next;
			free(thisNode);
		}
		lastNode = thisNode;
		thisNode=thisNode->next;
	}
	// return new head
	return head;
}

// -----------------------------------------------------------------------|
// OUTPUT STUFF
// -----------------------------------------------------------------------|

// Write a struct to a file
int writeOutput( char *fileName, bank *head) {

	bank *thisNode;
	thisNode=head;

   	// Open & point to file
	FILE *fout;
	fout = fopen(fileName, "w");

   	// Format and print each player
   	while(thisNode->next){

		fprintf(fout, "%-7d%-10s%-8.2f\n"
		       , thisNode->accountNumber
		       , thisNode->name
		       , thisNode->amount);

      thisNode=thisNode->next;
   }
    fclose(fout);
    return 1;
}

// -----------------------------------------------------------------------|
// UTILITIES 
// -----------------------------------------------------------------------|

void err( char *s ) { printf("\n%s\n", s);}
