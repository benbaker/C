// Ben Baker
// Lab 1 

// Basic file i/o, arrays, and pointers

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 15
 
// Prototypes
int readInfo(char* fileName, int *IDs, char** names, float *GPAs); 
void printArray(int *IDs, char** names, float *GPAs, int size);
int minGPA(float *, int);
int maxGPA(float *, int);
float avgGPA(float*, int);
int searchID(int*, int, int);
void printArray(int *, char**, float*, int);


int main ( int argc, char * argv[] ) {

  // Verify filename
  if (argc != 2) { throwError(1); return 0; } 
 
  // instantiate arrays
  int IDs[MAX];
  char *names[MAX];
  float GPAs[MAX];

  int i;
  // allocaote memory for string array
  for (i=0;i<10;i++) {
    names[i] = malloc(sizeof(char)*20);
  }

  // populate arrays from file
  int arraySize = readInfo(argv[1], IDs, names, GPAs);
  // throw error if that didn't work
  if (!arraySize) { throwError(2);  return 1; }


  // print the arrays we made
  printArray(IDs, names, GPAs, arraySize);

  // Do business logic on arrays
  int highest = maxGPA(GPAs, arraySize);
  int lowest  = minGPA(GPAs, arraySize);
  float averageGPA = avgGPA(GPAs, arraySize);

  // Print results of business logic
  printf("\nStudent with the highest GPA is %s with %f\n", names[highest], GPAs[highest]);
  printf("\nStudent with the lowest GPA is %s with %f\n", names[lowest], GPAs[lowest]);
  printf("\nAverage GPA fpr the class is %f\n", averageGPA);

  // find a student by ID
  int findMe;
  printf("\n\nEnter the student ID to search: ");
  scanf("%d", &findMe);

  int found = searchID(IDs, arraySize, findMe);

  // print found ID info or error if student not found
  if (found==-1) { printf("\nStudent with ID %d is not present in the class\n", findMe); }
  else { printf("\nStudent with ID %d is %s with GPA of %f\n", IDs[found], names[found], GPAs[found]); }

  return 0;
} // end main()


// find highest GPA
int maxGPA(float *GPAs, int arraySize) {

  int i,ind;
  float highest=0;
  for (i=0;i<arraySize;i++ ){
    if (GPAs[i] > highest) { highest = GPAs[i]; ind = i; }
  } // end for
  return ind;
} // end maxGPA

// find lowest GPA
int minGPA(float *GPAs, int arraySize) {
  int i,ind;
  float lowest=5;
  for (i=0;i<arraySize;i++) {
    if (GPAs[i] < lowest) { lowest = GPAs[i]; ind = i; }
  }
  return ind;
} // end minGPA

// calculate average GPA
float avgGPA(float *GPAs, int arraySize) {
  float total=0;
  int i;
  for(i=0;i<arraySize;i++) {
    total += GPAs[i];
  }
  return (total / arraySize);
} // end avgGPA

// find student by ID, return index of that student
int searchID(int *IDs, int arraySize, int searchID) {
  int i;
  for(i=0;i<arraySize;i++) {
    if (searchID == IDs[i]) { return i;}
  }  
  // if not found, fail
  return -1;
}



// Handle and print errors
int throwError(int err) {

  if (err == 1) {  printf( "\nFilename not provided\n" ); }
  if (err == 2) {  printf( "\nUnable to open the file\n" ); }

} // end throwError()

int readInfo(char* fileName, int *IDs, char** names, float *GPAs) {

  FILE *filePtr;
  filePtr = fopen(fileName, "r");

  // verify file open
  if (!filePtr) { throwError(2); return 0; }
  
  // get array size
  int size;
  fscanf(filePtr, "%d", &size);

  // push data to respective arrays
  int i;
  for (i=0;i<size;i++) {
    fscanf(filePtr, "%s%d%f", names[i], &IDs[i], &GPAs[i]); 
  } // end for
  // return size of arrays
  return size;
}


// print array contents with for loop
void printArray(int *IDs, char** names, float *GPAs, int size) {

  // print prettifier stuff
  printf("\nUser input: \n\n");
  printf("Name\tID\tGPA\n");

  int i;
  // walk the array
  for (i=0;i<size;i++) {
    // print array element
    printf("%s\t%d\t%.2f\n", names[i], IDs[i], GPAs[i]);
  } // end printf()
} // end printArray()


