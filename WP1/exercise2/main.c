#include <stdio.h> // import for io operations
#include <string.h> // import for strchr to ensure we get a valid string within the limits set by arguments
#include <stdlib.h> // for atoi to cast argv char into int

void clearBuffer(); // letting the program know this function exists
int rot(char c); // letting the program know this function exists (ROT13 encryption)

int main(int argc, char* argv[]) { // taking arguments for how many chars to allow encryption for
    if (argc < 2 || argc > 2) { // we only want to run the program if arguments were provided
        printf("Must input amount of encryptable characters \n");
        return 1; // return 1 for general error code
    }

    int maxLength = atoi(argv[1]) + 1; // getting the maxLength provided within the command line arguments and then converting from char (which argv is) to int using atoi
    char userString[maxLength]; // creating our char array (string array)
    printf("Enter a text or press EOF to exit \n");
    while (fgets(userString, maxLength, stdin)) { // while we're getting input that is valid keep running the loop, this include EOF input actually which is nice, if EOF is put in this fails and exits (thank you https://en.cppreference.com/w/c/io/fgets)
        if (strchr(userString, '\n') == NULL) { // because fgets will automatically place a \n at the end of a user input, if userString does not contain the \n it means that the inputbuffer was longer than 30 chars and as such its too long
            printf("String too long, try again \n");

            clearBuffer(); // clear the input buffer
            continue; // continue next loop iteration so that we skip the rest of the current while loop (no need to go through it again)
        }

        int len = strlen(userString); // storing the inputlength into an int

        for (int i = 0; i < len; i++) { // loop until i is equal to len
            userString[i] = rot(userString[i]); // call rot on each char in userString and replace the value at the same time
        }

        printf("Your encrypted string: %s", userString);
    }
}

int rot(char c) { // ROT13 converter
    if (c >= 'A' && c <= 'Z') { // by putting single quotes around chars, we call them by ASCII value
        return ('A' + (c - 'A' + 13) % 26); // take the ASCII value and add the char ASCII value minus the ASCII of first letter of alphabet + 13 (this is where the shifting happens) and then get the remainder of the entire alphabet by %26
    } else if (c >= 'a' && c <= 'z') { // by putting single quotes around chars, we call them by ASCII value
        return 'a' + (c - 'a' + 13) % 26; // take the ASCII value and add the char ASCII value minus the ASCII of first letter of alphabet + 13 (this is where the shifting happens) and then get the remainder of the entire alphabet by %26
    }
    return c; // if the char was not a letter, we simply return it since we don't convert integers etc
}

void clearBuffer() { // clear inputbuffer function to avoid having to write the same lines of code twice
    int buffer; // initialize a buffer int
    while ((buffer = getchar()) != '\n' && buffer != EOF); // while we dont run into a \n or EOF we keep going to successfully clear the buffer
}