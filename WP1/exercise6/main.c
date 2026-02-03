#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ------ Function declarations ----------
// This function generates a set of random numbers
// and fills the table *tab with these numbers
void create_random(int *tab, int *max, int *max_number);

// This function takes the *tab of random numbers
// and creates a table with the frequency counts for these numbers
void count_frequency(int *tab, int *freq, int* max, int* max_number);

// This function takes the frequency count table
// and draws a histogram of the values in that frequency table
void draw_histogram(int *freq, int* max_number, char* orientation);

// ------ Function definitions ----------


// ------ Main --------------------------
// The main entry point for the program
//
// If you choose to go for the optional part
// Please modify it accordingly
int main (int argc, char* argv[]){
    if (argc != 4) {
        printf("Incorrect amount of arguments\nCorrect usage: ./myprogram.out AMOUNT_OF_NUMBERS MAX_NUMBER HISTOGRAM_ORIENTATION");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++) {
        if (!isdigit(argv[1][i])) return 1;
    }
    for (int i = 0; i < strlen(argv[2]); i++) {
        if (!isdigit(argv[2][i])) return 1;
    }
    if (strcmp(argv[3], "vertical") != 0 && (strcmp(argv[3], "horizontal") != 0)) return 1;

    int max = atoi(argv[1]);
    int max_number = atoi(argv[2]);
    char* orientation = argv[3];

    int table[max]; // initialize our number table
    int frequency[max_number + 1]; // initialize our frequency table with + 1

    create_random(table, &max, &max_number); // call create_random to fill the table with numbers
    count_frequency(table, frequency, &max, &max_number);  // call count_frequency to count the numbers
    draw_histogram(frequency, &max_number, orientation);  // call draw_histogram to draw our histogram
}

/*
Looping through our array from 0 to 99 to fill the array with 100 numbers
We achieve maxnumber by modulo to rand() with maxnumber and then +1 because we want 1-20 and not 0-19
*/
void create_random(int* tab, int* max, int* max_number) {
    for (int i = 0; i < *max; i++) {
        tab[i] = (rand() % *max_number) + 1;
    }
    
}

void count_frequency(int* tab, int* freq, int* max, int* max_number) {
    // Since we initialized the frequency array without setting all values to 0, it contains old data (i.e garbage values)
    // So first we need to loop over frequency to overwrite the garbage values to 0
    for (int i = 0; i <= *max_number; i++) {
        freq[i] = 0;
    }
    
    // Looping over the table of 100 numbers +1'ing the correct frequency
    for (int i = 0; i < *max; i++) {
        freq[tab[i]]++;
    }
}

void draw_histogram(int* freq, int* max_number, char* orientation) {
    /*
    Nested loop time since we want to draw i amount of x's, j amount of times
    */
    if (strcmp(orientation, "vertical") == 0) { // vertical case
        for (int i = 1; i <= *max_number; i++) {
            printf("%d: ", i);
            for (int j = 1; j <= freq[i]; j++) {
                printf("x");
            }
            printf("\n");
        }
    } else { // horizontal case
        int max_freq = 0;
        for (int i = 0; i <= *max_number; i++) {
            if (freq[i] > max_freq) max_freq = freq[i];
        }
        printf("  "); // spacing for top row since we want to print the rows for readability
        for (int i = 1; i <= *max_number; i++) { // looping over from 1 to max_number to print the first row ("x axis")
            printf("%2d ", i); // 2 digit %2d for spacing purposes
        }
        printf("\n"); // print newline before starting with the counting
        /*
        Nested loop time since we want to draw i amount of x's, j amount of times
        Difference here is that we consistently print %2d instead for spacing purposes
        Here we always need to check if i is equal or less than our current frequency number we're working with within the inner loop
        This is because we need to keep track of ALL numbers each loop iteration, so we need to print an x for every number that should have an x on the current row
        */
        for (int i = 1; i <= *max_number; i++) {
            if (i <= max_freq){
                printf("%2d", i); // printing row number for readability, same deal here, %2d for spacing purposes
            }
            for (int j = 1; j <= *max_number; j++) {
                if (i <= freq[j]) {
                    printf(" x ");
                } else if (i <= max_freq) {
                    printf("   ");
                }
            }
            if (i <= max_freq) printf("\n");
        }
    }
}
