#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
Queue * 	deleteNode(Queue *head, int n);
Queue * 	sortQueue(Queue *head);
Queue * 	mergeQueue(Queue *head, Queue *head1);
Queue * 	mergeSwap(Queue *head1, Queue *head2);
Queue *  reverseQueue( Queue * head);
void 		printList ( Queue *head);
int 		queueLength(Queue *head);



// *******
//  MAIN
// *******

int main( int argc, char * argv[] ) {

	// Verify filename
	if (argc != 3) { err("Not enough arguments."); return 0; } 

	Queue *head = buildQueue( argv[1] );
	printf("\nPrinting Queue \n");
	printList( head );

	Queue *head2 = buildQueue( argv[2] );
	printf("Second Queue \n\n");
	printList( head2 );

	head = mergeQueue(head2, head);
	printf("Merged Queue \n\n");
	printList( head );

	int n = getNodeToDelete(queueLength(head));

	head = deleteNode(head, n);
	printf("\nQueue after delete operation \n\n");
	printList( head );

	head = reverseQueue(head);
	printf("\nBonus part reversed queue\n\n");
	printList( head );


} // end main()  



// **************
//  QUEUE LENGTH
// **************

int queueLength(Queue *head) {

	int count=0;
	Queue *currentNode;
	currentNode = head;
	while (currentNode->next != NULL) {
		count++;
		currentNode = currentNode->next;
	}
	return count;
}


// **************
//  MERGE QUEUE
// **************

Queue * 	mergeSwap(Queue *head1, Queue *head2){
	head1->next = mergeQueue(head1->next, head2);
	return head1;
}

Queue * 	mergeQueue(Queue *head1, Queue *head2){
	return (head1 == NULL) ? head2 :
			 (head2 == NULL) ? head1 :
		 	 mergeSwap(head2, head1);
}



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
	while (currentNode) {
		printf("%-10s%-8d\n"
		       , currentNode->name
		       , currentNode->number);

		currentNode = currentNode->next;
	} // end while()
	printf("\n");

} // end printList()



// ********
//  DELETE 
// ********

Queue * deleteNode( Queue *head, int n ) {

	if (n==1) { return head->next; }

	Queue *currentNode;
	Queue *lastNode;
	currentNode = head;
	int i = 1;

	while (currentNode && n != i) {
		lastNode = currentNode;
		currentNode = currentNode->next; 
		i++;
	}

	lastNode->next = currentNode->next;
	free(currentNode);
	return head;
}


int getNodeToDelete(int l){
	int n; printf("Enter the node you want to delete: ");
	scanf("%d",&n); while (n <=0 || n > l) {
		printf("Invalid Node enter a different node: ");
		scanf("%d",&n);
	} return n;
}


// ********
//  BONUS 
// ********


Queue * reverseQueue( Queue * head) {
	Queue* newHead = 0;
	while (head) {
		Queue* next = head->next;
		head->next = newHead;
		newHead = head;
		head = next;
	} return newHead;
}



// HANDLE ERRORS
int err(char *err) {
  printf("%s\n", err);
} // end err()







