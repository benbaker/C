#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <systime.h>

#define MAX 20



// Prototypes ---------------------------------------------- |
int readFile      ( char *fileName, char **str1 );
int  getStringLength  ( char *s1 );
void createArray    ( char *s1 );
void printArray   ( char *s1 );
void reverse      ( char *s1 );
void ascii        ( char *s1 );
void sort       ( char *s1 );
int i;
// ---------------------------------------- |


// Define data structure for players.
typedef struct {
   char name[50];
   int goals;
   int apps;
} data;

// Global array
data players[MAX];



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



// File I/O  ------------------------------------------------ |



// read in strings
char* read( char *fileName ) {

  char* inputString;
  inputString = malloc(sizeof(char) * MAX);

    FILE *f;
    f = fopen(fileName, "r");
    while(!feof(f)) {
      fscanf(f, "%s", inputString);
    }
    
    fclose(f);
    return inputString;
} // end read()




// read in ints as double pointer
int read_input(char *name , int ** a) {

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



// Write a string to a file
void  write( char* fileName, char* string) {

  FILE *fout;
  fout = fopen(fileName, "w");
  fprintf(fout, "%s", string);
  fclose(fout);

} // end write()



// Read a struct from a file
int loadArray( char *fileName ) {

   // Open the given file
   FILE *f; f = fopen(fileName, "r");
   if (!f) {return 0;}

   // Put all that data into global array players
   int i = 0;
   while(!feof(f)) { 
      fscanf(f, "%s%d%d"
              , players[i].name
              , &players[i].goals
              , &players[i].apps
      ); i++;
   } 
   // Peace out
   fclose(f); 
   return --i;
} // end loadAray()



// Write a struct to a file
void writeContent( char *fileName, int size) {

   // Open & point to file
   FILE *fout;
   fout = fopen(fileName, "w");

   // Format and print each player
   int i =0; for (i=0;i<size;i++) {

      fprintf(fout, "%-26s%-10d%-10d\n"
            , players[i].name
            , players[i].goals
            , players[i].apps
      );
   } fclose(fout);
}



// Strings and arrays --------------------------------------- |


// Encrypt
char* encrypt( char *string, int K, int N) {

  printf("Encrypting only letters...\n");
  printf("Plain Text:  %s\n", string);

  while (N) {

    for (i=0;i<strlen(string);i++) {
      // if (isalpha(string[i])) {
        string[i] += K;
        }
    } N--;
  }
  printf("Encrypted: %s\n", string);
  return string;
} 



// Decrypt
char* decrypt( char *string, int K, int N) {

  printf("\nDecrypting...\n");
  printf("Encrypted Text:  %s\n", string);

  // Shift N times
  while (N) {

    // replace char with self + K
    for (i=0;i<strlen(string);i++) {

        string[i] -= K;
      
    } N--;
  }
  printf("Plain Text:  %s\n", string);
  return string;
} 



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



// get length of string
int getStringLength(char *s1) {

  int length = strlen(s1);
  return length;

}


// Print array as ints
void printArray( int *a, int size ) {
  for (i=0;i<size;i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
} // end printArray()



// Print from struct
int printPlayer( int i ) {

  printf("\n\nBest performance: %s, %d goals, %d appearence(s)\n"
         , players[i].name
         , players[i].goals
         , players[i].apps
  );
}



// Sorts, searches, reverses -------------------------------- |


// Linear search for ints
int searchArray ( int *a, int size, int num ) {

   int foundIndex =0;
   for (i=0;i<size;i++) {
      if ( num == a[i] ) { 
         foundIndex = i;
      }
   } return foundIndex;
}

// Linear search for strings
int searchArray( int size, char *target ) {

   int i;
   for (i=0;i<size;i++) {
      if (strcmp(players[i].name, target)==0) { 
         return i; 
      } 
   } return -1;
}


// Sort with selection sort size x - y
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


// Insertion sort 
void sortArray( int *a, int size ) { 

   printf("\nArray before sorting: \n");
   printArray(a, size);

   int f, u, k;

   for (f = 1 ; f <= size - 1; f++) {
      u = f;

      while ( u > 0 && a[u] < a[u-1]) {

         k           = a[u];
         a[u]        = a[u-1];
         a[u-1]      = k;

         printArray(a, size);

         u--;
      }
   }
   printf("Array before sorting: \n");
   printArray(a, size);
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



// Reverse without pointers
void reverseWithoutPointers (char *s1) {
  
 int i, l = getStringLength(s1)-1;
 
 for (i=0; i<l/2+1; i++) {

  char temp = s1[i];
  s1[i] = s1[l-i];
  s1[l-i]=temp;
 }
}



// Make a random array
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





