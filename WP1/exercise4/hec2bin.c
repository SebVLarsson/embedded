#include <stdio.h> // include for io operations
#include <stdlib.h> // include for malloc
#include <string.h> // include for strlen, strcpy and strcspn

#define MAX_BUFFER 65 // the largest binary we'll ever receive is 64 bits, so we define a maxbuffer of 65 (64 + end character)

int main(int argc, char* argv[]) { // main function, arguments enabled
    char* input = malloc(MAX_BUFFER * sizeof(char)); // define and initialize char* input to max buffer * the size of a character

    if (argc == 1) { // pipe case
        if (fgets(input, MAX_BUFFER, stdin) == NULL) { // put the pipe (stdin) into input, check if its NULL
            printf("Invalid input\n");
            free(input); // free malloc memory
            return 1;
        }
        input[strcspn(input, "\n")] = '\0'; // strcosp finds the stdin \n character within the input str and replace it with \0
        input = realloc(input, (strlen(input) + 1) * sizeof(char)); // reallocate the memory to not use more than we need which is size of char * len + 1(+1 is for the \0)
    } else if (argc == 2) { // no piping
        input = realloc(input, ((strlen(argv[1]) + 1) * sizeof(char))); // reallocate the memory to not use more than we need which is size of char * len + 1(+1 is for the \0)
        strcpy(input, argv[1]); // copy the argv string into input
    } else {
        printf("Invalid input\n");
        free(input); // free malloc memory
        return 1;
    }

    int i;// initialize i outside of the for loop because we want i within current scope for later use
    for (i = 0; input[i] != '\0'; i++) { // check for invalid input
        if ((input[i] < 48 || input[i] > 57) && (input[i] < 65 || input[i] > 70)) { // check if the char is 0-9 or A-F
            printf("Incorrect hexadecimal\n");
            free(input); // free malloc memory
            return 1;
        }
    }
    i--; // decrement i by 1 for correcting bit count and loop behaviour
    

    /*
    Since 1 hex corresponds to 4 bits, we're initializing an int and check if the int/bit count is 8, 16, 32, 64 bits
    We then assign it to binLen for correct memory allocation later
    */
    int binLen;
    if (i < 2) {
        binLen = 8;
    } else if (i < 4) {
        binLen = 16;
    } else if (i < 8) {
        binLen = 32;
    } else if (i < 16) {
        binLen = 64;
    } else {
        printf("Hexadecimal too large\n");
        free(input); // free malloc memory
        return 1;
    }

    /*
    Allocate the minimum amount of memory needed an assign the last character of the string to \0
    */
    char* binValue = malloc((binLen + 1) * sizeof(char));
    binValue[binLen] = '\0';

    int hexToBits; //since we want to convert 1 hex to 4 bits at the time
    binLen--; // correcting the binLen for correct behaviour

    /*
    The principle here is that we're collecting the ASCII value of the hex character and converting it into a real integer
    Since 0-9 and A-F within ASCII can be considered the same as an array, we're substracting the 0 index element of those "arrays" to get the real integer value
    We then assign that to hexToBits
    */
    while (binLen >= 0 && i >= 0) {
        hexToBits = 0;
        if (input[i] >= 48 && input[i] <= 57) {
            hexToBits = input[i] - 48;
        } else if (input[i] >= 65 && input[i] <= 70) {
            hexToBits = input[i] - 55;
        }
        /*
        In the subsequent for loop, because hex to binary is a 4 bit increment, we will loop over 4 iterations each time:
        We assign the current binLen value into the binValue array, AND comparing it to 1 to see if its a 1 or a 0 (since we want the LSB each time)
        We then bitshift right and decrement the binLen by 1 to proceed with the next bit
        */
        for (int bit = 0; bit < 4; bit++) {
            binValue[binLen] = (hexToBits & 1) ? '1' : '0';
            hexToBits >>= 1;
            binLen--;
        }
        i--;
    }

    /*
    Correcting the binary string, if the hex number is smaller than the maximum size, we know the rest of them are 0s
    So here we're essentially just filling out 0s since we're dealing with 8, 16, 32 and 64 bit integers
    */
    while (binLen >= 0) {
        binValue[binLen] = '0';
        binLen--;
    }

    printf("%s\n", binValue);
    free(binValue); // free malloc memory
    free(input); // free malloc memory
    return 0;
}