#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// this program implements insertion sort and linear search algorithm

int i;


int readInput( char *, int ** ); // Takes the input file name and a double integer pointer. First it opens the input file, create an array by mallocing right amount of memory (using first number in the first line as the size of the input).Load the array with the remaining input and return the size of the input at the end. 

int searchArray( int *, int, int ); // This function takes an integer array , size of the array and a number to be searched in the array. If the number is present in the array it returns the index of that number otherwise display the message in the main() that the given number is not present in the array. Easiest way to implement this problem is to implement linear search algorithm but you can also implement efficient searching algorithm as discussed in the class.

void sortArray( int *, int ); // This function sorts the integer array using insertion sort algorithm. 

void printArray( int *, int ); //It takes an integer array and the size of the array as an input and prints the content of the array as shown in the sample output below.



int main( int argc, char * argv[] ) {

	int *a, size;
	// Check args or die
	if (argc != 2) { throwError(1); return 0; } 
	// Get file size or die
	if (!(size = readInput(argv[1], &a))) { throwError(2); return 0; }

	// Prompt for search
	int find  = getNumber(); 
	// Search for prompted
	int found = searchArray	( a, size, find ); 

	// Report search findings
	found ? printFound(find,found) : printNotFound(find); // report findings

	// insertion sort & report
	sortArray( a, size );

} // end main()  


int readInput(char *name , int **a) {

	// make file pointer -> file
	FILE *ptr; 
	ptr=fopen(name, "r");
	if(ptr==NULL) return 0; 

	// get size of file from first line in file
	int size; 
	fscanf(ptr, "%d", &size); 

	// make memory for a
	*a=malloc(sizeof(int)*size); 
	int num; 

	// walk file and put everything in a
	for(i=0;i<size;i++) { 
		fscanf(ptr, "%d", &num); 
		*(*a+i)=num; 
	} 

	// spill and bail
	fclose(ptr);
	return size;

} // end read_input()


// Print array as ints
void printArray( int *a, int size ) {
  for (i=0;i<size;i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
} // end printArray()


// Ask user for number to search
int getNumber() {
	int num;
	printf("Enter the number for which you want to search: ");
	scanf("%d", &num);
	return num;
}


// search array and return index
int searchArray ( int *a, int size, int num ) {

	int foundIndex =0;
	for (i=0;i<size;i++) {
		if ( num == a[i] ) { 
			foundIndex = i;
		}
	} return foundIndex;
}


// Insertion sort the array, report before & after
void sortArray( int *a, int size ) { 

	printf("\nArray before sorting: \n");
	printArray(a, size);

	int f, u, k;

	for (f = 1 ; f <= size - 1; f++) {
		u = f;

		while ( u > 0 && a[u] < a[u-1]) {

			k         	= a[u];
			a[u]   		= a[u-1];
			a[u-1] 		= k;

			printArray(a, size);

			u--;
		}
	}
	printf("Array after sorting: \n");
	printArray(a, size);
}


// Handle search results.
int printFound( int f, int q) {
	printf("\nNumber %d was present at index %d.\n",f,q); 
}
int printNotFound( int f ) { 
	printf("\nNumber %d was not present in the array. \n", f ); 
}


// Handle and print errors
int throwError(int err) {
  if (err == 1) {  printf( "\nFilename not provided\n" ); }
  if (err == 2) {  printf( "\nUnable to open the file\n" ); }
} // end throwError()
