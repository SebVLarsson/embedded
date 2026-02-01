#include <stdio.h> // include for io operations
#include <stdlib.h> // include for malloc
#include <string.h> // include for strcpy and strcspn

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

    int i; // initialize i outside of the for loop because we want i within current scope for later use
    for (i = 0; input[i] != '\0'; i++) { // check for invalid input
        if (input[i] != '0' && input[i] != '1') { // check if current char is either a 1 or a 0
            printf("Incorrect binary\n");
            free(input); // free malloc memory
            return 1; // if any char or int other than 1 or 0, return error code 1
        }
    }
    i--; // decrement i by 1 for correcting bit count and loop behaviour

    /*
    Initialize an int to see how big our char array needs to be to hold the hex value
    We check the amount of bits by seeing how big i currently is, this is why we originally initialized it outside the for loop scope
    We also decremented it to ensure that it follows our 0 index
    We then set hexLen to however many bits there is divided by 4 since each hex character represents 4 bits
    */
    int hexLen;
    if (i < 8) {
        hexLen = 2;
    } else if (i < 16) {
        hexLen = 4;
    } else if (i < 32) {
        hexLen = 8;
    } else if (i < 64) {
        hexLen = 16;
    } else {
        printf("Binary too large\n");
        free(input); // free malloc memory
        return 1;
    }

    /*
    Since we want to print the HEX as a string, we malloc the hexLen + 1 so that it fits the \0 character
    We also set the last hexLen value to \0
    */
    char* hexValue = malloc((hexLen + 1) * sizeof(char));
    hexValue[hexLen] = '\0';


    int fourBitValue; // initialize our four bit counter since we want to calculate hex value by hex value
    hexLen--; // decrement hexLen to follow 0 indexing

    while (hexLen >= 0 && i >= 0) { // while either is greater or equal than 0, keep running the loop
        fourBitValue = 0; // initialize the four bit counter to 0
        for (int j = 0; j < 4; j++) { // 4 bit loop to count the value of each hex
            if (input[i] == '1') {
                /*
                If we found a 1, we bitshift add whatever our current j is.
                For example: If j is 3, we bitshift 3 steps to the left which would be 2³ = 8, 2 would bitshift 2 steps left and be 2² etc
                */
                fourBitValue += (1 << j);
            }
            i--; // decrement i to get the next bit
        }

        /*
        Because 0-9 and A-F is not next to eachother within the ASCII table
        We need 2 cases:
        First is, if fourBitValue is less than 10, i.e 0-9, we do 0 + fourBitValue to get the correct number
        Secondly, if fourBitValue is larger than 10 we get the ASCII of A, we then add the value of fourBitValue - 10 (-10 because we're looking for A, B, C, D, E or F)
        This will in turn give us the correct hexadecimal value
        */
        if (fourBitValue < 10) {
            hexValue[hexLen] = '0' + fourBitValue;
        } else {
            hexValue[hexLen] = 'A' + (fourBitValue - 10);
        }
        hexLen--; // decrement hexLen since we want to work 4 bits by 4 bits
    }

    printf("%s\n", hexValue);
    free(hexValue); // free malloc memory
    free(input); // free malloc memory
    return 0; // successful exit of the program
}
