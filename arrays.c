// Ben Baker
// pre-lab1

// Basic file i/o, arrays

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 15
 
int readInfo(char* fileName, int *IDs, char** names, float *GPAs); 
void printArray(int *IDs, char** names, float *GPAs, int size);
int minGPA(float*, int);
int maxGPA(float *, int);
int searchID(float*, int, int);
void printArray(int *, char**, float*, int);



int main ( int argc, char * argv[] ) {

  // Verify filename
  if (argc != 2) { throwError(1); return 0; } 
 

  int IDs[MAX];
  char *names[MAX];
  float GPAs[MAX];

  int i;

  for (i=0;i<10;i++) {

    names[i] = malloc(sizeof(char)*20);

  }


  int gotFile = readInfo(argv[1], IDs, names, GPAs);

  if (!gotFile) { return 1; }


  // print the array we made
  // printArray(IDs, names, GPAs, 5);

 return 0;
} // end main()

// Handle and print errors
int throwError(int err) {

  if (err == 1) {  printf( "\nFilename not provided\n" ); }
  if (err == 2) {  printf( "\nUnable to open the file\n" ); }

} // end throwError()

int readInfo(char* fileName, int *IDs, char** names, float *GPAs) {

  FILE *filePtr;

  filePtr = fopen(fileName, "r");

  if (!filePtr) { throwError(2); return 0; }
  

  printf("\ngot file\n");

  int size;
  fscanf(filePtr, "%d", &size);

  printf("\n got size: %d\n", size);
  printf("getting stuff from file...\n");
  
  int i;
  for (i=0;i<size;i++) {


    fscanf(filePtr, "%s%d%f", names[i], &IDs[i], &GPAs[i]); 
    printf("%s%d%f", names[i], IDs[i], GPAs[i]);

  }

  return 1;

}


// print array contents with for loop
void printArray(int *IDs, char** names, float *GPAs, int size) {

  printf("\nuser input: \n\n");

  int i;
  // walk the array
  for (i=0;i<size;i++) {
    // print array element
    printf("%d\t%s\t%d\n", IDs[i], names[i], GPAs[i]);
  } // end printf()
} // end printArray()






