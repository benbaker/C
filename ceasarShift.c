// Ben Baker
// Lab 2
// This program does basic IO and encryption.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
  // ./a.out text.txt dec.txt enc/dec 27 3


// Prototypes ----------------------------- |
int  i;
char* encrypt     ( char *string, int K, int N);
char* decrypt     ( char *string, int K, int N);    
int   checkOption ( char * string);                  // done
char* read        ( char *fileName);                 // done
void  write       ( char* fileName, char* string);

// ---------------------------------------- |


int main( int argc, char * argv[] ) {

  // Check for correct number of args
  if (argc != 6) { throwError(1); return 0; } 

  // Dereference args
  char* fileIn  = argv[1];
  char* fileOut = argv[2];
  int option    = checkOption(argv[3]);
  int K         = atoi(argv[4]);
  int N         = atoi(argv[5]);

  // Check shift and subs
  if (K > 26 || K < 0 || N > 26 || N < 0) { 
    throwError(4); return 0; 
  }

  // Instantiate strings
  char* beginString;
  beginString  = malloc(sizeof(char) * MAX);
  char* resultString;
  resultString = malloc(sizeof(char) * MAX);

  // Get string from input file
  beginString = read(fileIn);

  // Encrypt or decrypt?
  if (!option) { throwError(3); return 0; }
  if (option==1) { resultString =  encrypt( beginString, K, N ); }
  if (option==2) { resultString =  decrypt( beginString, K, N ); }

  write(fileOut, resultString);

  
} // end main()





// replace char with kth char

char* encrypt( char *string, int K, int N) {

  printf("Encrypting only letters...\n");
  printf("Plain Text:  %s\n", string);

  while (N) {

    for (i=0;i<strlen(string);i++) {
      if (isalpha(string[i])) {
        string[i] += K;
        }

    }

    N--;
  }
  printf("Encrypted: %s\n", string);
  return string;
} 




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





void  write( char* fileName, char* string) {

  FILE *fout;
  fout = fopen(fileName, "w");
  fprintf(fout, "%s", string);
  fclose(fout);

} // end write()



int checkOption(char *str) { // done

  if (strcmp(str, "enc")==0) { return 1; }
  if (strcmp(str, "dec")==0) { return 2; }

  return 0;

}



// Utilities ----------------------------- |


// Handle and print errors
int throwError(int err) {
  if (err == 1) {  
    printf( "\nToo few arguments. need file1, file2, opt, sub shift\n" ); }
  if (err == 2) {  
    printf( "\nUnable to open the file\n" ); }
} // end throwError()


// ---------------------------------------- |


