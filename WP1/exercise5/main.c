#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Defines the maximum number of the values in the table
#define MAXNUMBER 20 // Defines the maximum value of random numbers

// ------ Function declarations ----------
// This function generates a set of random numbers
// and fills the table *tab with these numbers
void create_random(int *tab);

// This function takes the *tab of random numbers
// and creates a table with the frequency counts for these numbers
void count_frequency(int *tab, int *freq );

// This function takes the frequency count table
// and draws a histogram of the values in that frequency table
void draw_histogram(int *freq );

// ------ Function definitions ----------


// ------ Main --------------------------
// The main entry point for the program
//
// If you choose to go for the optional part
// Please modify it accordingly
int main (void){
    int table[MAX]; // initialize our number table
    int frequency[MAXNUMBER + 1]; // initialize our frequency table with +1 because MAXNUMBER is 20, which means we want the max number to actually be 20

    create_random(table); // call create_random to fill the table with numbers
    count_frequency(table, frequency);  // call count_frequency to count the numbers
    draw_histogram(frequency);  // call draw_histogram to draw our histogram
}

/*
Looping through our array from 0 to 99 to fill the array with 100 numbers
We achieve maxnumber by modulo to rand() with maxnumber
*/
void create_random(int* tab) {
    for (int i = 0; i < MAX; i++) {
        tab[i] = (rand() % MAXNUMBER) + 1;
    }
    
}

void count_frequency(int* tab, int* freq) {
    // Since we initialized the frequency array without setting all values to 0, it contains old data (i.e garbage values)
    // So first we need to loop over frequency to overwrite the garbage values to 0
    for (int i = 0; i <= MAXNUMBER; i++) {
        freq[i] = 0;
    }
    
    // Looping over the table of 100 numbers +1'ing the correct frequency
    for (int i = 1; i < MAX; i++) {
        freq[i] += tab[i];
    }
}

void draw_histogram(int* freq) {
    /*
    Nested loop time since we want to draw i amount of x's, j amount of times
    We also include an if case for the last x of each line to get the newline chararacter in
    */
    for (int i = 1; i <= MAXNUMBER; i++) {
        printf("%d: ", i);
        for (int j = 1; j <= freq[i]; j++) {
            printf("x");
        }
        printf("\n");
    }
}