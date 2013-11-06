#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 15

// This program uses basic IO, selection sort, and structs in arrays to mainuplate text files containing baseball player stats.

// Define data structure for players.
typedef struct {
	char name[50];
	int goals;
	int apps;
} data;

// Global array
data players[MAX];



int loadArray ( char *fileName ); // Open the given filename, read in all of the data into the players array, return a count of how many players data entries were read in.

void printArray( int size ); // Walk the players array and print out in neat columns the contents of each data element in the array until the total number of elements in the array is reached.

void sortByGoals( int size ); // Use selection sort to sort the arrays by the goal count from highest to lowest. 

int mvp( int size ); // Find the player that shows the best performance calculated by the highest goals to games ratio. Return the index of this player and print that result in main.

int searchArray( int size, char *target ); // Use a linear search to find the player in the array matching the given name and return the index of that player if found. If not found, return -1 and print "not found."

void writeContent( char *fileName, int size ); // Take the second argument form the command line as the filename to which formatted, sorted results should be printed.




int main( int argc, char * argv[] ) {

	// Check args or die
	if (argc != 3) { throwError(1); return 0; } 

	// Get file size or die
	int size;
	if (!(size = loadArray(argv[1]))) { throwError(2); return 0; }

	// Print the array
	printf("\nContent of the file:");
	printArray(size);

	// Sort the array
	sortByGoals(size);

	// Print the MVPs stats
	int bestPlayer = mvp(size);
	printPlayer(bestPlayer);

	// Prompt user for search name
	char *search = malloc(sizeof(char)*50);
	printf("Enter a player to find:");
	scanf("%s", search);

	// Search array for name
	int found = searchArray(size, search);

	found > -1 ? 
		printf("%s has %d goal(s) and %d appearances.\n\n"
		       , players[found].name
		       , players[found].goals
		       , players[found].apps) 
		: printf("Player not found.\n\n");

	// Write formatted content to file
	writeContent( argv[2], size);

} // end main()  



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



void printArray( int size ) {

	// Print Title and table headers
	printf("\n\n%-26s%-10s%-10s\n"
	       , "Name"
	       , "Goals"
	       , "Appearances"
	);

	// Format & print each player
	int i =0; for (i=0;i<size;i++) {

  		printf("%-26s%-10d%-10d\n"
  		       , players[i].name
				 , players[i].goals
				 , players[i].apps
		);
  } printf("\n");
} // end printArray()



void sortByGoals( int size ) {

	int lh, rh, i;
	data temp;

	// Selection sort algorithm
	for (lh = 0; lh < size; lh++) {
		rh=lh;
		for (i=lh; i<size;i++) {
			if (players[i].goals > players[rh].goals) rh=i;
		} // end for(i<n)
		temp = players[lh];
		players[lh] = players[rh];
		players[rh] = temp;
	} // end for (lh <n) 
   printf("Sorted player goals scored:");
   printArray(size);
} // end sortByGoals



int mvp( int size ) {

	int i, MVP;
	float score, highScore;

	for (i=0;i<size;i++) {

		// Calculate goals to games ratio.
		score = (float) players[i].goals / (float) players[i].apps;
		// Store it if it's the highest.
		if (score>highScore) {
			highScore = score;
			MVP = i;
		} 
	} return MVP;
}



int printPlayer( int i ) {

	printf("\n\nBest performance: %s, %d goals, %d appearence(s)\n"
	       , players[i].name
	       , players[i].goals
	       , players[i].apps
	);
}



int searchArray( int size, char *target ) {

	int i;
	for (i=0;i<size;i++) {
		if (strcmp(players[i].name, target)==0) { 
			return i; 
		} 
	} return -1;
}


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


int throwError(int err) {
	// Handle and print errors
  if (err == 1) {  printf( "\nInput and output filenames required.\n\n" ); }
  if (err == 2) {  printf( "\nUnable to open the input file\n\n" ); }
} // end throwError()

