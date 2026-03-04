#include <stdio.h> // for io ops
#include <string.h> // for strlen(), strcpy(), strcspn()
#include <ctype.h> // for isdigit(), isspace()
#include <stdlib.h> // for malloc
#include <assert.h> // for assert()

// define a max size that is sufficient for any kind of string without spaces (more or less)
#define MAX_SIZE 255

// FUNCTION DEFINITIONS
char** resize(char **array, size_t *current_size, size_t new_size);
char** remove_string(char **array, int *rem_index, int *array_size);
int find_string(char **array, int array_size);
// END FUNCTION DEFINITIONS



/*
 * Main function
 * Sets array_size to 5, creates a buffer of 256 bytes
 * Creates an array of pointers with size of array_size * size of a char pointer
 * We then prompt the user 5 times for _CORRECT_ input
 * Then continues with the finding shortest array, removing and so on
*/
int main(void) {
    int i = 0; // index control int
    int array_size = 5; // array size (5 default)
    char buffer[MAX_SIZE + 1]; // max size buffer
    char **string_array = malloc(array_size * sizeof(char*)); // allocate memory for our outer array of pointers
    
    while (i < array_size) { // while we haven't gotten enough correct input
        printf("Insert a string\n"); 
        fgets(buffer, MAX_SIZE, stdin); // take user input and save in buffer
        
        int valid_string = 1; // controlling int for checking validity of strings
        
        /*
         * Loop through the input strings
         * (For) While we havent reached \n (which gets input by stdin) or \0 if the string hits max length
        */
        for (int index = 0; buffer[index] != '\n' && buffer[index] != '\0'; index++) {
            if (isspace(buffer[index])) { // check if char is a whitespace
                printf("Invalid string\n");
                valid_string = 0; // set control int to invalid (0)
                break; // break the forloop to prevent unnecessary execution
            }
        }
        
        // if we have a correct string
        if (valid_string == 1) {
            // we replace the \n with a \0 because only want "pure" strings with strcspn
            buffer[strcspn(buffer, "\n")] = '\0';
            
            // allocate correct amount of memory for the string
            string_array[i] = malloc((strlen(buffer) + 1) * sizeof(char));
            // copy the string into the string array
            strcpy(string_array[i], buffer);
            i++; // increment i for the next iteration
        }
    }
    // find the shortest string index and save it into rem_index via a find_string call
    int rem_index = find_string(string_array, array_size);

    // save the new string_array into string_array after removal with a remove_string call
    string_array = remove_string(string_array, &rem_index, &array_size);
    
    // print remaining strings via for loop from 0 to array size
    printf("Array after removal:\n");
    for (int j = 0; j < array_size; j++) {
        printf("%s\n", string_array[j]);
    }
    
    // loop over the string_array and free all the individual strings memory
    for (int j = 0; j < array_size; j++) {
        free(string_array[j]);
    }
    // free the outer arrays memory
    free(string_array);
    
    return 0; // successful execution
}

/*
 * Resize array function, takes array of pointers (string array)
 * The current size which is a size_t pointer
 * and a new size which is just a size_t
 * We then assert that the new size is less or equal to max size (unnecessary but might aswell for good meansure)
 * Save new_size into the memory address of current size
 * Sets the last element of array to NULL
 * Return array
*/
char** resize(char **array, size_t *current_size, size_t new_size) {
    assert(new_size <= MAX_SIZE); // check that new array size not too big
    *current_size = new_size; // save new_size into the memory location of current size
    array[new_size] = NULL; // index 0 so new_size = NULL shortens array
    return array; // return array
}

/*
 * Remove string function
 * Takes an array of pointers (string arrays)
 * and two int pointers, index to the string we're removing and the current array_size
 * The concept is then that we simply free the memory of remove index
 * then place the last item of the array of pointers into the removed strings place
 * and then return with a resize call (which returns the array)
 */
char** remove_string(char **array, int *rem_index, int *array_size) {
    // free the memory of the string we're removing
    printf("Shortest string removed: %s", array[*rem_index]);
    free(array[*rem_index]);

    // if index of string to remove is not the last element of the array
    if (*rem_index != (*array_size - 1)) {
    // from index of removed string, move strings backwards to keep original order minus the removed string
        for (int i = *rem_index; i < *array_size - 1; i++) {
            array[i] = array[i + 1];
        }
    }

    // return the resize returned array
    // dereferencing array_size to be able to set a new size = array_size -1
    return resize(array, array_size, *array_size - 1);
}

/*
 * Find string function
 * Takes an array of pointers (string arrays)
 * Defaults shortest index and len to index 0
 * Loops through the array without index 0 and compares
 * Returns the index of shortest string
*/
int find_string(char **array, int array_size) {
    int shortest_index = 0; // starting with index 0 string
    size_t shortest_len = strlen(array[0]); // starting with index 0 string
    
    // loop from 1 to array size
    for (int i = 1; i < array_size; i++) {
        size_t current_len = strlen(array[i]); // get current strings length and store in current_length
        if (current_len < shortest_len) { // if we found a new "highscore"
            shortest_len = current_len; // set the new shortest length
            shortest_index = i; // set the index to current i
        }
    }
    return shortest_index; // return the index of shortest string
}