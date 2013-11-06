#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Ben Baker


int i;

typedef struct N { 
	int number; 
	char * name; 
	struct N *next; 
}  Queue; 

// **************
//  Prototypes
// **************

Queue * 	createNode( char *s, int n);
Queue * 	insertNode( Queue *head, Queue *node );
Queue * 	buildQueue( char *);
void 		printList ( Queue *head);
Queue * 	deleteLastNode(Queue *head);
Queue * 	sortQueue(Queue *head);



// *******
//  MAIN
// *******

int main( int argc, char * argv[] ) {

	// Verify filename
	if (argc != 2) { err("Not enough arguments."); return 0; } 

	Queue *head = buildQueue( argv[1] );

	printList( head );


} // end main()  




// **************
//  BUILD QUEUE
// **************

Queue * buildQueue(char *fileName) {

	// in: filename
	// out: pointer to first node

	// get filesize
	FILE *f; 		f = fopen(fileName, "r");
	int fileSize; 	fscanf(f, "%d", &fileSize);

	// instantiate variables towards struct
	int number; int first =1;
	Queue *firstNodePtr;
	Queue *head;

	// walk file
	for(i=0;i<fileSize;i++) {

		char *name; 
		name = malloc(sizeof(char)*20);

		// read element
		fscanf(f, "%s%d", name, &number);

		// create node from element
		Queue *thisNodePtr;
		thisNodePtr = createNode( name, number );

		// hold pointer to first node
		if (first) { 
			firstNodePtr = thisNodePtr; 
			head = thisNodePtr; 
			first=0; 
		}

		// put node in queue
		head = insertNode(head, thisNodePtr);

	} fclose(f); return firstNodePtr;
} // end buildQueue()



// ********************
//  CREATE A NEW NODE
// ********************

Queue * createNode( char *s, int n ) {

	// in:  name and number
	// out: pointer to new node

	Queue *newNodePtr;
	newNodePtr = (Queue *)malloc(sizeof(Queue));
	newNodePtr->name	=	s;
	newNodePtr->number=	n;
	return newNodePtr;

} // end createNode()



// ***********
//  QUEUE UP
// ***********

Queue * insertNode(Queue * head, Queue * node ) {
	head->next = node;
	node->next = NULL;
	return node;
}



// ********
//  PRINT 
// ********

void printList( Queue *head ) {

	Queue *currentNode;
	currentNode = head;

	printf("\n\nPrinting Queue \n\n");

	while (currentNode->next != NULL) {

		printf("%-10s%-8d\n"
		       , currentNode->name
		       , currentNode->number);

		currentNode = currentNode->next;
	} // end while()
	printf("\n");

} // end printList()




Queue * deleteLastNode( Queue *head ) {

	Queue *tmp;
	tmp = head->next;
	free(head);
	return tmp;
}





// HANDLE ERRORS
int err(char *err) {
  printf("%s\n", err);
} // end err()







