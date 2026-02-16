#include <stdio.h> // io ops
#include <stdlib.h> // rand()

#define MAX 5 // arbitrary max amount of number size for array

void fill_array(int *array); // initialize fill_array function

int main(void) { // main function
    int array[MAX] = {0}; // initialize our int array[MAX] and set starting values to 0
    fill_array(array); // call the fill_array function to generate numbers

    // prints the address of the array pointer
    // since an array is just a sequential block of memory, all it does is point to the first element of the array
    printf("The value of the address of the array: %p\n", array); 
    // just prints first item in array, array[0]
    printf("First integer in the array is %d\n", array[0]);
    // since we know max is 5 and its 0 indexing, just do MAX -1 to fetch last
    printf("The last integer in the array is: %d\n", array[MAX - 1]);
    //sizeof(int) to figure out what size, returns a long unsigned int, therefore %ld
    printf("The size of an integer (number of bytes) is: %ld\n", sizeof(int));
    // and to get the whole array size, multiple sizeof(int) with MAX, this also returns long unsigned int so %ld
    printf("The size of the whole array in bytes is %ld\n", (MAX * sizeof(int)));
    return 0;
}


// function to randomly fill upp array, if we didn't #define a max size we would also pass on an int size
void fill_array(int *array) {
    for (int i = 0; i < MAX; i++) { // from 0 to max -1 (0 indexing)
        array[i] = (rand() % 99) + 1; // %99 for 0-98 and + for 1-99
    }
}