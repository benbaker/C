// **********************
// BRING IN DEPENDENCIES
// **********************
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// **********************
// SET PROGRAM PARAMETERS
// **********************
#define MAX_NAME 20
#define TOOLKIT_SIZE 5
#define SERVER_SIZE 5
#define MAX_SCORES 6
#define UPGRADE_STR 2
#define HIGHSCORES_SIZE 5
#define MAX_TURNS 10
#define LOSS 0

// **********************
// DEFINE DATA STRUCTS
// **********************

typedef struct {
	char tool_name[MAX_NAME];
	char type;
	int str;
	int cost;	
}ToolKit;

typedef struct {
	char server_name[MAX_NAME];
	char type;
	int str;
}WorldServers;

typedef struct {
	char player_name[MAX_NAME];
	int score;
}TopFiveHighScores;

// **********************
// INSTANTIATE PROTOTYPES
// **********************
ToolKit* getToolsFromFile(char * filename);
WorldServers* getServersFromFile(char * filename);
TopFiveHighScores* getHighScoresFromFile(char * filename);
void displayTargetServerInfo (WorldServers server);
int selectTool (ToolKit* tools);
int startRun (ToolKit tool, WorldServers * server);
void massServerUpgrade(WorldServers * servers, char upgrade_type);
void displayHighScoresFromFile(TopFiveHighScores * highscores);
void sortHighScores(TopFiveHighScores * highscores, int length);
void writeUpdatedHighScoresToFile(char* filename, TopFiveHighScores *highscores, int score);

// Utility Functions might be worth making
// int getTargetServer(); 
// int upgradeTool(ToolKit * tool);

int main (int argc, char *argv[]) {

	// Open files from console input
   int files = openFiles( argv[1], argv[2], argv[3]);
    if (!files) { 
    	printf("Game is missing one or some of the following:")
    	printf(" Tools.txt, Servers.txt, or highscores.txt");
    }
	
	 


}


// Let's get out files
int openFiles(char* toolsFile, char* serversFile, char* highScoresFile) {
    
    toolKit = fopen(toolsFile, "r");
    servers = fopen(serversFile, "w");
    highscores = fopen(highScoresFile, "r");

    // Lets verify that we got them
    if (!toolKit || !servers || highscores) { return 0;} else {return 1;}

}
















