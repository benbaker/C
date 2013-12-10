#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NODES 10

int i;


typedef struct _date date;
struct _date{

	int day;
	int month;
	int year;
	struct _date *next;

};

int err(char *err);


date* newNode( int d, int m, int y ); // creates a single linked list and return address to the node.

date* buildList( date *currentHead, date *new ); // build linked list from addresses returned by newNode. Built as a stack FILO. every new node is the new head. In: current head, Out: New head.

date* buildListOld( date *currentHead, date *new );

int deleteNode( date *head, int d, int m, int y ); //  Prompt users for ints day month year. If item is head, delete the head in main() and move the head to the next node, else call this function. return 1 only if search params met.
// gotta keep track of the last thing.


void printList( date *n ); // pass in head, walk the content of all nodes, format to sample, order will be reverse.





int main( void ) {

	// PPROMPT FOR COUNT
	printf("Number of items in linked list: ");
	int nodeCount; scanf("%d", &nodeCount);

	date* head;
	head = (date *)malloc(sizeof(date));
	head->next = NULL;

	// PROMPT AND MAKENODE FOR EACH
	int nodeCounter = nodeCount; while (nodeCounter--) {

		int m,d,y; 

		// PROMPT FOR DATE
		printf("\nMonth:");		scanf("%d", &m);
		printf("Day:"  ); 		scanf("%d", &d);
		printf("Year:" ); 		scanf("%d", &y);


		// MAKE NEW NODE
		date *justCreated;
		justCreated = newNode( d, m, y );


		// ADD NODE TO LIST
		head = buildList( head, justCreated );
		

	}
		

		// PRINT THE LIST CONTENTS
		printList( head );



		
		// prompt for delete.
		printf("\nDate to delete:\n");
		int delM, delD, delY;
		printf("Month: ");	scanf("%d", &delM);
		printf("Day: "	 );	scanf("%d", &delD);
		printf("Year: " );	scanf("%d", &delY);
		// create node for deletion comparison.


		// TEST FOR HEADER


		if (delD == head->day
		    && delM == head->month
		    && delY == head->year) { 

			head=head->next;

		} else {
		
		int deleteMe = deleteNode( head, delD, delM, delY );


		if (deleteMe == 1) {

			printf("Deleted item from linked List\n");

		}



		if (deleteMe == 0) {

			printf("Item not found in list\n");

		}


		}





		printList( head );

	


} // end main()  


// DELETE A NODE

int deleteNode( date *head, int d, int m, int y){

	date *currentNode;
	currentNode = head;

	date *tmp;
	tmp = currentNode;

	while (currentNode->next != NULL) {


		if (d == currentNode->day
		    && m == currentNode->month
		    && y == currentNode->year) { 

			tmp->next = currentNode->next;

			free(currentNode);
			return 1;

			currentNode->next = tmp->next;


		} // if found
	
	tmp = currentNode;
	currentNode = currentNode->next;


	}

return 0;

}




// PRINT THE LINKED LIST

void printList( date *head ) {

	date *currentNode;
	currentNode = head;

	printf("Linked List: \n");

	while (currentNode->next != NULL) {

	printf("%d-%d-%d -> "
	       , currentNode->month
	       , currentNode->day
	       , currentNode->year);

	currentNode = currentNode->next;

	}
}





// BUILD LIST OF NODES

date* buildList ( date *currentHead, date *newHead) {

	newHead->next = currentHead;

	return newHead;

}



// CREATE A NEW NODE

date* newNode( int d, int m, int y ) {

	date *newNodePtr;
	newNodePtr = (date *)malloc(sizeof(date));

	newNodePtr->day=d;
	newNodePtr->month=m;
	newNodePtr->year=y;

	return newNodePtr;

}






// HANDLE ERRORS

int err(char *err) {

  printf("%s\n", err);

} // end throwError()







