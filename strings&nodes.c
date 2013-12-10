#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 200 

// Instantiation
typedef struct data {
  char *word;
  struct data *next;
} node;

node *head, *copy, *prev; int  _log; 

// Headers 
node *createWord(char *string); 
node *addWord(node *, node *, node *);
void readContent(char *filename);
void printWords(); 
void deleteWord(char *deleteMe);
void logThis(node *curr, node *next, int op); 
void menu(); void add(); void del(); void undo(); void bye();
void (*menuFunctions[4])() = { bye, add, del, undo };

// main
int main( int argc, char * argv[] ) {
	argc != 2 ? printf("No file specified.\n") :
	readContent( argv[1] );
	menu();
}

// read file 
void readContent( char *fileName ){

	FILE *f; f=fopen(fileName,"r"); 
	while(!feof(f)) {
		char *word = malloc(sizeof(char)*20);
		fscanf(f, "%s", word);
		head = addWord( head, createWord( word ), NULL );
	} fclose(f);
} 

// menu
void bye() { 
	printf("\nTerminating program. Have a nice day!\n\n"); 
	return; 
}
void add() {
	printf("Please enter a new word:");
	char *newWord = malloc(sizeof(char)*20);
	scanf("%s", newWord);
	head = addWord( head, createWord( newWord ), NULL );
}
void del() { 
	printf("Which word would you like to delete?:");
	char *deleteMe = malloc(sizeof(char)*20);
	scanf("%s", deleteMe); deleteWord( deleteMe);
}
void undo() { 
	_log ==  1 ? deleteWord( copy->word ): 
	_log == -1 ? copy == head ? (head = addWord( head, copy, head), logThis(copy, NULL, 1)):
	(head = addWord( head, copy, prev), logThis(copy, NULL, 1)):printf("Nothing to undo ?\n");
}

// show menu
void menu() {
	int option=1; while (option) {
		printWords(head); printf("Menu:\n ");
		printf("(1) Add new Word\n ");
		printf("(2) Delete Word\n ");
		printf("(3) Undo last action\n ");
		printf("(0) Exit\n Option: ");
		scanf("%d", &option);
		(option >= 0 && option < 4) ?
		(*menuFunctions[option])() : fail(); 
	} exit;
}

// create node for word
node *createWord( char *w ) {
	node *newNode = (node *)malloc(sizeof(node)); 
   	newNode->word = w; newNode->next = NULL; 
   	return newNode;
}

// add word to linked list
node *addWord( node *old, node *new, node *where ){
	if (where) { node *this = head; 
		do { if (this == where){
				new->next = where->next; where->next = new;
				logThis(new, where, 1); return head;
			 }
		} while (this=this->next);
	} logThis(new, old, 1);
	return !old ? new : 
	(old->next = addWord(old->next, new, NULL), old);
}

// delete word
void deleteWord(char *deleteMe) {
	node *this, *last; this = head;
	while (this != NULL && strcmp(this->word, deleteMe) != 0 ) {
		last=this;
		this=this->next;
	} if (!this) { 
		printf("\nCan\'t find %s, sorry. :(\n", deleteMe);
	} else if (this == head) { 
		logThis(NULL, head , -1); 
		head = this->next; 
	} else if (this != head) { 
		logThis(this, last , -1); 
		last->next = this->next;
	}
}

// print words
void printWords( node *nd ){
	nd ? (printf("%s ", nd->word),
	printWords(nd->next)): 
	printf("\n\n"); 
}

// get length
int getLength(node *head) {
	int count=1; while(head->next) { 
		head=head->next; count++; 
	} return count;
}

// log undo
void logThis( node *p1, node *p2, int n) {
	copy = p1; prev = p2; _log = n;
}

// show fail
int fail() { printf("\nUnrecognized option. =) \n\n"); }
