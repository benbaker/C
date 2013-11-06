// Ben Baker, 14175659, BPBKT7, Section Tuesday
// Labcode: 61813

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


// this program implements selection sort and linear search algorithm

int i;

int readInput( char *, int ** ); // Takes the input file name and a double integer pointer. First it opens the input file, create an array by mallocing right amount of memory (using first number in the first line as the size of the input).Load the array with the remaining input and return the size of the input at the end. 

void selectionSort( int *, int ); // This function sorts the integer array using insertion sort algorithm. 

int binarySearch( int *, int, int, int ); // This function takes an integer array , size of the array and a number to be searched in the array. If the number is present in the array it returns the index of that number otherwise display the message in the main() that the given number is not present in the array. Easiest way to implement this problem is to implement linear search algorithm but you can also implement efficient searching algorithm as discussed in the class.


void printArray( int *, int ); //It takes an integer array and the size of the array as an input and prints the content of the array as shown in the sample output below.

int partialSort(int *, int); // takes integer array and the size of the array and returns the pivot element at the end. 

void swap(int *x,int *y);


int main( int argc, char * argv[] ) {

	srand (time ( NULL ));

	int *a, size;
	// Check args or die
	if (argc != 2) { throwError(1); return 0; } 
	// Get file size or die
	if (!(size = readInput(argv[1], &a))) { throwError(2); return 0; }

	// insertion sort & report
	selectionSort( a, size );


	// Prompt for search
	int find  = getNumber(); 
	// Search for prompted
	int found = binarySearch ( a, 0, size, find ); 

	// Report search findings
	found != -1 ? printFound(find,found) : printNotFound(find); // report findings

	// BONUS
	// partial sort on pivot

	// reset the array
	if (!(size = readInput(argv[1], &a))) { throwError(2); return 0; }

	printf("Array before partial sort\n");
	printArray(a, size);

	int pivot = partialSort(a, size);

	printf("Array after partial sort with pivot element %d\n", pivot);
	printArray(a, size);

} 


// search array and return index
int binarySearch ( int *a, int low, int high, int target ) {

    if (high < low)
        return -1;
    int middle = (low + high)/2;
    if (target < a[middle])
        return binarySearch(a, low, middle-1, target);
    else if (target > a[middle])
        return binarySearch(a, middle+1, high, target);
    else if (target == a[middle])
        return middle; 

}


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
	printf("\nEnter the number for which you want to search: ");
	scanf("%d", &num);
	return num;
}



// BONUS
// Sort on a random pivot
int partialSort(int *a, int size) {

	int r = rand() % size;
	int i,j;
	int f = a[r];

	// The TA Told me that this is the proper implementation of the bonus.

	for (j=0; j<size; j++) {
		for (i=1; i<size-1; i++) {
			if (f > a[i]) { swap(&a[i], &a[i-1]); }
			if (f < a[i]) { swap(&a[i], &a[i+1]); }
		}
	} return f;
}


// swap by pointers
void swap(int *x,int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;

}


// Slection sort the array, report before & after
void selectionSort( int *a, int size ) { 

	printf("\nArray before sorting: \n");
	printArray(a, size);

  int l = size;
  int lh, rh, i, temp;
  for (lh = 0; lh < l; lh++) {
    rh=lh;
   for (i=lh; i<l;i++) {
     if (a[i] < a[rh]) rh=i;
   } // end for(i<n)
    temp = a[lh];
    a[lh] = a[rh];
    a[rh] = temp;
  } // end for (lh <n) 
	printf("Array after sorting: \n");
	printArray(a, size);
}



// Handle search results.
int printFound( int f, int q) {
	printf("\nNumber %d was present at index %d.\n\n",f,q); 
}
int printNotFound( int f ) { 
	printf("\nNumber %d was not present in the array. \n\n", f ); 
}


// Handle and print errors
int throwError(int err) {
  if (err == 1) {  printf( "\nFilename not provided\n" ); }
  if (err == 2) {  printf( "\nUnable to open the file\n" ); }
} // end throwError()







