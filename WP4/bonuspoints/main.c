#include <stdio.h> // io ops
#include <string.h> // for strdup (string duplication), it just makes copying string faster and easier
#include <stdlib.h> // stdlib for memory stuff

// defining an array struct much like a dynamic array
// reason being is that we need to keep track and resize when necessary
typedef struct {
    char **permutations; // the array
    int count; // how full the array is
    int capacity; // capacity of the array
} DynamicArray;

// FUNCTION DEFINITIONS
void init_array(DynamicArray *array, size_t *start_size);
void resize_array(DynamicArray *array);
void add_permutation(DynamicArray *array, char *string);
void swap(char *x, char *y);
void backtrack(char *string, int start, size_t *len, DynamicArray *array);
void free_array(DynamicArray *array);
// END FUNCTION DEFINITIONS


// main function, arguments enabled
int main(int argc, char *argv[]) {
    // error handling for wrong amount of arguments which is 1 (+1) = 2
    if (argc != 2) {
        printf("invalid\n");
        return 0;
    }

    // duplicate the string and store it into a string array
    char *string = strdup(argv[1]);

    // get the length of the string, store in size_t since we're measuring something
    size_t len = strlen(string);

    // check if length is less than 10 or the length is less than 2 (since 1 only has 1 permutation)
    if (len > 10 || len < 2) {
        printf("invalid\n");
        return 0;
    }

    // initialize our dynamic array
    DynamicArray perms;

    // call the init function with the pointer to the struct and an arbitrary starting size
    // we know that this wont be enough since we're going to get !n permutations (in every case I think?)
    // but we need to start somewhere and our resizing is very aggressive (*2) so it shouldnt matter too much
    init_array(&perms, &len);

    // call backtracking with the string, starting point (index 0), end point (length of the string) and ptr to array
    backtrack(string, 0, &len, &perms);


    // print the permutations, just looping through the structs (dynamic array) array
    printf("All permutations of the string %s are: ", string);
    for (int i = 0; i < perms.count; i++) {
        if (i == perms.count - 1) {
            printf("%s\n", perms.permutations[i]);
        } else {
            printf("%s ", perms.permutations[i]);
        }
    }

    // call free_array since we need to free memory, each time we call strdup it will automatically allocate memory
    // so its extremely important that we call this function
    free_array(&perms);

    // free the string
    free(string);

    // successful execution
    return 0;
}


// function to init the array with a starting size that is somewhat relevant
void init_array(DynamicArray *array, size_t *start_size) {
    // set capacity to what we sent as a parameter
    // because we're looking at n! permutations, we might aswell begin with a n³ size where n is length of string
    array->capacity = *start_size * *start_size * *start_size;

    // set starting size
    array->permutations = malloc(array->capacity * sizeof(char*));
    
    // set the count to 0 since we havent starting looking for permutations yet
    array->count = 0;
    
}


// resize for our dynamic array
void resize_array(DynamicArray *array) {
    // aggressive resizing which would definetely be bad for longer strings, but 10 chars is not that bad
    // 10! is 3.6million * size of each permutation plus the pointers, haven't sat down and calculated but
    // I think we're somewhere in the two digit megabytes at most?
    // and for resizing, lets say we get very unlucky and it resizes on the very last item
    // our array would be 7million, bad, but not too bad since we dont have memory restraints here
    array->capacity *= 2;
    
    //reallocate the memory
    array->permutations = realloc(array->permutations, array->capacity * sizeof(char*));
}

// adding individual permutations
void add_permutation(DynamicArray *array, char *string) {

    // first we check if we actually have space
    // if we don't, we resize the array
    if (array->count >= array->capacity) {
        resize_array(array);
    }

    // add the permutation by just duplicating the string into the array
    array->permutations[array->count] = strdup(string);

    // increment the count so we know how full the array is for next iteration
    array->count++;
}


// swap function
void swap(char *x, char *y) {
    // dereferencing pointers throughout since we care about the values and not the addresses
    char temp = *x; // store value of x in temp
    *x = *y; // assign value of y to x
    *y = temp; // assign value of temp to y
}


/*
The idea here is:
Base case: After we have placed the characters in all possible positions (start is now equal to len - 1)
we have a permutation that is complete, and thus we add it and return from the recursion step

Every other case is a recursive step: For each position from start to end
We swap the character at our starting position (2nd parameter) with the current for loops i value
We then call backtrack to recursively do this step over and over until we have achieved a new permutation
Once the recusive steps has been complete (base case was computed) we swap back all chars to their original positions for the next iteration
This includes all permutations for the i'th value of the for loop
*/
void backtrack(char *string, int start, size_t *len, DynamicArray *array) {

    // base case
    if (start == *len - 1) {
        // add the permutation to the array
        add_permutation(array, string);
        return;
    }


    // main part of the backtrack recursive algorithm
    for (int i = start; i < *len; i++) {
        // swap starting char with current i position char
        swap(&string[start], &string[i]);
        // recursively call backtrack with starting position +1 (same end as before)
        backtrack(string, start + 1, len, array);
        // backtrack the entire thing, putting things back into their places
        swap(&string[start], &string[i]);
    }
}


// free memory for everything in the array
// since we're copying strings, we need to free each strings memory individually, thus the for loop
void free_array(DynamicArray *array) {
    for (int i = 0; i < array->count; i++) {
        // free each string
        free(array->permutations[i]);
    }
    // free the array at the end
    free(array->permutations);
}