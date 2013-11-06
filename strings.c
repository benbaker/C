#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 20



// Prototypes ----------------------------- |
int readFile      ( char *fileName, char **str1 );
int  getStringLength  ( char *s1 );
void createArray    ( char *s1 );
void printArray   ( char *s1 );
void reverse      ( char *s1 );
void ascii        ( char *s1 );
void sort       ( char *s1 );
int i;
// ---------------------------------------- |


int main( int argc, char * argv[] ) {


  // Verify filename
    if (argc != 2) { throwError(1); return 0; } 

  char* str1[MAX];


  // allocate memory for array of strings.

  for (i=0; i<MAX; i++) {

    str1[i] = malloc(sizeof(char)*MAX);

  }

  int fileSize = readFile( argv[1], str1 );
  if (!fileSize) { return 0; }

  createArray   (*str1);
  sort       (*str1);
  printArray   (*str1);
  reverse      (*str1);
  printArray   (*str1);
  ascii      (*str1);

  
} // end main()


int readFile( char *fileName, char **str1 ) {

    int i=0;
    FILE *f;
    f = fopen(fileName, "r");
    char buff[MAX];
    while (!feof(f)) {
  
      fgets(buff, MAX, f);
      printf("String read: %s", buff);
      
 }
    fclose(f);
    return 1;
}


// populate array with file info
int readFileOld( char *fileName, char **str1 ) {

  FILE *filePtr;
  filePtr = fopen(fileName, "r");

  // verify file open
  if (!filePtr) { throwError(2); return 0; }


  for (i=0;str1[i]!="\0";i++) {
    fscanf(filePtr, "%s ", str1[i]); 
    printf("%s\n", str1[i]);
  } // end for

  fclose(filePtr);

  // return size of arrays
  return 1;

}



// Reverse array
void reverse( char* s1 ) {

  int l = getStringLength(s1);
  // point to top and bottom of array
  char *ptr, *ptr2, tmp; 
  ptr = s1; ptr2 = s1 + (sizeof(char)*l)-1;
  // dereference and swap
  for (i=0;i<l/2;i++) { 
    tmp = *ptr;
    *ptr++ = *ptr2;
    *ptr2-- = tmp;
  } // end for(i<MAX)
} // end reverseArray()



// Print array ascii
void ascii( char *s1 ) {

  int l = getStringLength(s1);
  char *ptr; ptr = s1;
  for (i=0;i<l;i++) { 
    printf("%d ", *ptr++);
  } // end for(i<MAX)
  printf("\n\n");
} // end ascii()



// Print array letters
void printArray( char *array ) {

  int l = getStringLength(array);
  for (i=0;i<l;i++) {
    printf("[%c] ", array[i]);
  } // end for(i<n)
  printf("\n\n");
} // end printArray()



// Sort with selection sort
void sort( char * array) {

  int l = getStringLength(array);
  int lh, rh, i, temp;
  for (lh = 0; lh < l; lh++) {
    rh=lh;
   for (i=lh; i<l;i++) {
     if (array[i] < array[rh]) rh=i;
   } // end for(i<n)
    temp = array[lh];
   array[lh] = array[rh];
   array[rh] = temp;
  } // end for (lh <n) 
} // end sortArray()



// get length of string
int getStringLength(char *s1) {

  int length = ((sizeof(s1)) / (sizeof(s1[0])));
   return MAX;
}




// Utilities ----------------------------- |

// Make a randome array
void createArray( char *array ) {
  for (i=0;i<MAX;i++) {
    array[i] = random() % 190;
  } // end for(i<MAX)
} // end createArray()


// Handle and print errors
int throwError(int err) {
  if (err == 1) {  printf( "\nFilename not provided\n" ); }
  if (err == 2) {  printf( "\nUnable to open the file\n" ); }
} // end throwError()


// Reverse without pointers
void reverseWithoutPointers (char *s1)
{
 int i, l = getStringLength(s1)-1;
 
 for (i=0; i<l/2+1; i++)
 {
  char temp = s1[i];
  s1[i] = s1[l-i];
  s1[l-i]=temp;
 }

}

// ---------------------------------------- |


