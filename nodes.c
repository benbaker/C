#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _data node;
struct _data{ int ID; char *name; double GPA; int year; struct _data *next; };

typedef struct _data2 tree;
struct _data2 { int ID; char *name; double GPA; int year; struct _data2 *left; struct _data2 *right; };


node *createNode(int , char *, double , int);
node *insertNode(node *head, node *new);
node *buildList(char *filename);
node *updateList( char *fileName, node *head);


void deleteNode(int, node *);
void printList(node *head);
int  intSwap (int *pa, int *pb);
int  floatSwap (double *pa, double *pb);
int  charSwap(char** a, char** b);

void swap(node *a, node *b);
void sortList(node *head);

void writeOutput( char * , node *);
char *itoy( int year );

// Main

int main( int argc, char * argv[] ) {

	if (argc != 4) { printf("need more arguments\n"); return 0; } 

	node *head = buildList( argv[1] );

	printf("Linked List\n");
	printList(head);

	printf("Updated Linked List\n");
	head = updateList( argv[2], head );

	printf("Sorted Linked List\n");
	sortList(head);
	printList(head);


	writeOutput( argv[3] , head);

}

// Read in file

node * buildList( char *fileName ){

	node *head = NULL;
	int fileSize, i, first =1; 
	FILE *f; f=fopen(fileName,"r"); 
	fscanf(f, "%d", &fileSize);
	for(i=0;i<fileSize;i++) {

		int ID, year; char *name=malloc(sizeof(char)*20); double GPA; 
		fscanf(f, "%d%s%lf%d", &ID, name, &GPA, &year );
		head = insertNode( head, createNode( ID, name, GPA, year ) );

	} fclose(f); return head;
}

// Read in udpate file

node * updateList( char *fileName, node *head ){

	int fileSize, i, first =1; 
	FILE *f; f=fopen(fileName,"r"); 
	fscanf(f, "%d", &fileSize);
	char *task = malloc(sizeof(char));
	for(i=0;i<fileSize;i++) {

		int ID, year; char *name=malloc(sizeof(char)*20); double GPA; 
		fscanf(f, "%s%d%s%lf%d", task, &ID, name, &GPA, &year );

		if (strcmp("a", task) == 0) {

		printf("adding %d { %s %f %d }\n", ID, name, GPA, year);
		head = insertNode( head, createNode( ID, name, GPA, year ) );
		printf("..............................................\n");
		printList(head);

		} else {
		
			printf("attempting to delete %d { %s %lf %d }\n", ID, name, GPA, year);
			deleteNode(ID, head);
			printf("..............................................\n");
			printList(head);
		}

	} fclose(f); return head;
}

// Create nodes

node * createNode( int ID, char *name, double GPA, int year) {

	node *newNode     = (node *)malloc(sizeof(node));
	newNode->ID			= ID;
	newNode->name		= name;
	newNode->GPA		= GPA;
	newNode->year		= year;

	return newNode;
}

// Link nodes

node * insertNode( node *head, node *new ){

	return !head ? new : 
	(strcmp(new->name, head->name)<0) ? 
	(new->next = head, new) : 
	(head->next = insertNode(head->next, new), head);
}

// delete node

void deleteNode(int deleteMe, node *head) {

	node *this, *last; this = head;

	while (this->next != NULL && this->ID != deleteMe ) {
		last=this;
		this=this->next;
	}
	if (!this) { 
		notFound(); 
	} else if (this == head) { 
		printf("Deleting %d\n", this->ID);
		head = this->next; 
	} else if (this != head) { 
		printf("Deleting %d\n", this->ID);
		last->next = this->next;
	}
}


// display error

int notFound() { printf("\nDid not find that word.\n\n"); }



// Print nodes

void printList( node *nd ){
	nd ? (printf("%-7d%-10s%-8.2lf%-10s\n"
        , nd->ID, nd->name, nd->GPA, itoy(nd->year)),
		  printList(nd->next)): printf("\n"); 
}


// Write struct to a file

void writeOutput( char *fileName, node *head) {
	
	node *nd;nd=head;
   // Open & point to file
   FILE *fout;
   fout = fopen(fileName, "w");

   // Format and print each player
   while(nd){
		fprintf(fout, "%-7d%-10s%-8.2lf%-10s\n"
		, nd->ID, nd->name, nd->GPA, itoy(nd->year));
      nd=nd->next;
   }
   fclose(fout);
}


// Get string for class year

char *itoy( int year ) {

	return 
	year == 1 ?  "freshman":
	year == 2 ?  "sophomore":
	year == 3 ?  "junior":
	"senior";
}

// Count nodes

int getLength(node *head) {
	int count=1; while(head->next) { 
		head=head->next; count++; 
	} return count;
}

// swap nodes

void swap( node *a, node *b ) {

	intSwap(&(b->ID), &(a->ID));
	intSwap(&(b->year), &(a->year));
	floatSwap(&(b->GPA), &(a->GPA));
	charSwap(&(b->name), &(a->name));

}

// sort list

void sortList( node *head ) {

	node *node1, *node2;

	for(node1 = head;node1 != NULL ;node1 = node1->next) {
        for(node2 = node1; node2 != NULL; node2 = node2->next) {
            if(node1->ID > node2->ID) {
            	swap(node1, node2);
          	}
      	}
    }
}	

// Swap contents

int intSwap   (int *pa, int *pb) { int t = *pa; *pa = *pb; *pb = t; } 
int floatSwap (double *pa, double *pb){ float t = *pa;*pa = *pb;*pb = t;} 
int charSwap  (char** a, char** b){ char *t = *a;*a = *b;*b = t; }

// sort recursively

node *bigger(node *n1, node *n2) {

	return n1 ? n1 : n2 ;

}
