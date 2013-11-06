#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 10


int main( void ) {

	// Def struct
	typedef struct {
		int  number;
		int  address;
	} person;

	// Global array
	person users[MAX];

	int i; for (i=0;i<MAX;i++){

		users[i].number  = random() % 99999;
		users[i].address = random() % 99999;

		printf("%-10d%-10d\n"
		       , users[i].number
		       , users[i].address
		);
	}
}


