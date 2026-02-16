#include <stdio.h> // for io ops (fgets)
#include <string.h> // for strcpy

// max string length +1 since we need 1 spot for the \0
#define BUFFER_SIZE 21

// initialize our own strcpy function
// camelCase because the assignment said so
void copyString(char *buffer, char *copy_string);


// main function, no arguments since we're gonna shell inject into stdin with program < file
int main(void) {
    char buffer[BUFFER_SIZE]; // initialize our input buffer
    char copy_string[BUFFER_SIZE]; // initialize our destination string
    fgets(buffer, sizeof(buffer), stdin); // read the input either from user or txt file

    // calling our copyString function and then printing it to ensure it works
    copyString(buffer, copy_string);
    printf("%s\n", copy_string);

    // use strcpy and double check with printf (since we kinda know strcpy already works)
    strcpy(copy_string, buffer);
    printf("%s\n", copy_string);
}


// strcpy function, take source and destination string arrays
void copyString(char *buffer, char *copy_string) {
    int i; // initialize i outside of for loop since we want to keep track of it to add the \0 terminator at the end

    // set i to 0 then we iterate from i to MAX buffer_size -1 for memory safety since we want space for the \0 at the end
    // we also look for the end of the string with \n (stdin will add if space) or \0
    for (i = 0; i < BUFFER_SIZE - 1 && buffer[i] != '\n' && buffer[i] != '\0'; i++) {
        // each iteration we copy over the char from buffer to copy_string
        // even if arrays are technically pointers, you can copy the individual chars from one to another with = operator
        copy_string[i] = buffer[i]; 
    }
    // assign \0 at the end of the string
    copy_string[i] = '\0';
}