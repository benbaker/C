#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define MAX 15
#define MAX_LENGTH 30

// prototypes
int  openFiles(char* input, char* output, char* upd);
int  readContent();
void sort(int size, int option);
void writeFile(int size);
void closeFiles();
void updateInfo(int size);

// define a struct
typedef struct {
    int account;
    char name[MAX_LENGTH];
    float amount;
} bank;




// Make array from bank struct
bank customers[MAX];
bank updates[MAX];

// Instantiate file pointers
FILE *in, *out, *upd;


// Tell the story
int main( int argc, char* argv[] ) {
    
    // Open files from console input
    int files = openFiles( argv[1], argv[2], argv[3]);
    if (files < 0) { printf("Files could not be opened.");}
    
    // Read files, get number of customers
    int contentSize = readContent();
    if (!contentSize) { printf("Files could not be opened.");}
    
    // read and apply updates
    updateInfo(contentSize);
    
    // Write to output.txt
    writeFile(contentSize);
    
    // Close files
    closeFiles();
    
}


// open files
int openFiles(char* input, char* output, char* update) {
    
    // try
    in = fopen(input, "r");
    if (!in) { return -1; }
    // try
    out = fopen(output, "w");
    if (!out) { return -1; }
    // try
    upd = fopen(update, "r");
    if (!upd) { return -1; }
}

// read files
int readContent() {
    
    char* entry[MAX];
    int customerCount = 0;
    int i;
    
    fscanf(in, "%d", &customerCount);
    
    printf("\n******ACCOUNTS******\n");
    for(i=0;i<customerCount;i++) {
        
        fscanf(in, "%d", &customers[i].account);
        fscanf(in, "%s", customers[i].name);
        fscanf(in, "%f", &customers[i].amount);
        printf("%d\t%s\t%f\n", customers[i].account, customers[i].name, customers[i].amount);
        
    }
    
    return customerCount;
    
} // end readContent()



void updateInfo(int size) {
    
    int j;
    int i;
    int updateCount;
    
    fscanf(upd, "%d", &updateCount);
    
    printf("\n******UPDATES*****\n");
    for(j=0;j<updateCount;j++) {
        
        fscanf(upd, "%d", &updates[j].account);
        fscanf(upd, "%f", &updates[j].amount);
        
        printf("%d\t%f\n", updates[j].account, updates[j].amount);
        
        
        
        for (i=0;i<size;i++) {
            
            if (updates[j].account == customers[i].account) {
                
                customers[i].amount += updates[j].amount;
                
            }
            
        }
        
    }
    
}

// write to a file
void writeFile(int customerCount){
    
    
    printf("\n******OUTPUTS******\n");
    
    int i;
    float totalBank;
    float poorest = 0;
    float richest = 0;
    
    char* richestDude;
    char* poorestDude;
    
    
    
    fprintf(out, "Acc. no. \t  Name  \t amount\n");
    printf("Acc. no. \t  Name  \t amount\n");
    
    for (i=0;i<customerCount;i++) {
        
        fprintf(out,"%6d\t%15s\t%6.2f\n", customers[i].account, customers[i].name, customers[i].amount);
        printf("%6d\t%15s\t%6.2f\n", customers[i].account, customers[i].name, customers[i].amount);
        
        totalBank += customers[i].amount;
        
        if (customers[i].amount > richest) {
            
            richest =  customers[i].amount;
            richestDude = customers[i].name;
            
        }
        
        
        
        if (!poorest || customers[i].amount < poorest) {
            
            poorest =  customers[i].amount;
            poorestDude = customers[i].name;
            
        }
        
        
    } // end for
    
    
    fprintf(out,"%6d\t%15s\t%6lf\n", customers[i].account, customers[i].name, customers[i].amount);
    
    printf("\nTotal amount in the bank is %.2f", totalBank);
    printf("\nCustomer with the highest amount in account is %s with %.2f", richestDude, richest);
    printf("\nCustomer with the lowest amount in account is %s with %.2f", poorestDude, poorest);
    printf("\n");
    
    fprintf(out, "\nTotal amount in the bank is %.2f", totalBank);
    fprintf(out, "\nCustomer with the highest amount in account is %s with %.2f", richestDude, richest);
    fprintf(out, "\nCustomer with the lowest amount in account is %s with %.2f", poorestDude, poorest);
    
    
    
    
    
} // end writeFile()











void closeFiles(){
    
    fclose(in);
    fclose(out);
    
} // end closeFiles()


// double star means an array of different char pointers

~
~
~