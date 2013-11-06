#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NODES 10


int i;





typedef struct _data data;
struct _data{
	int number;		//integer field in the node
	struct _data *next;	//link to the next node
};


data* buildLinkedList();
void printLinkedList(data *head);




int main( int argc, char * argv[] ) {


	data* list = buildLinkedList();

	printLinkedList( list );


} // end main()  






data* buildLinkedList() {

	// malloc for first node
	data * firstNode;
	firstNode = (data *)malloc(sizeof(data));

	// assign number to node
	firstNode->number = rand() % 10;	


	// mark this as start of linked list
	data *head ;
	head = firstNode;
	head->next = NULL;

	// create x more nodes
	int nodes = NODES;

	data *nextPtr = firstNode;

	while (nodes--) {

		// malloc for a new node
		data * node;
		node = (data *)malloc(sizeof(data));

		// assign number to node
		node->number = rand() % 10;	
		node->next = nextPtr;

		nextPtr = node;

	}
	return  head;
}



void printLinkedList(data *head) {

	int nodes = NODES;

	data *currentNode = head;

	while(nodes--) {

		printf("%d", currentNode->number);
		currentNode = currentNode->next;

	}
}




// Handle and print errors
int throwError(int err) {
  if (err == 1) {  printf( "\nerr 1\n" ); }
  if (err == 2) {  printf( "\nerr 2\n" ); }
} // end throwError()







