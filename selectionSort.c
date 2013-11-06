#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int array[MAX];
int i;


int main() {


	createArray	(array, MAX);
	printArray	(array, MAX);
	sortArray	(array, MAX);
	printArray	(array, MAX);

  
} // end main()




int createArray( int array[], int n ) {
  for (i=0;i<MAX;i++) {
    array[i] = random() % MAX;
  } 
}



int printArray( int array[], int n ) {
  for (i=0;i<MAX;i++) {
    printf("%d | ", array[i]);
  } // end for(i<MAX)
} // end printArray()




int sortArray( int array[], int n) {
  
  int lh, rh, i, temp;

  for (lh = 0; lh < n; lh++) {

    rh=lh;
	 for (i=lh; i<n;i++) {
	   
	   if (array[i] < array[rh]) rh=i;
	 
	 } // end for(i<n)
    
    temp = array[lh];
	 array[lh] = array[rh];
	 array[rh] = temp;
	 
	 } // end for (lh <n) 
  } // end sortArray()

