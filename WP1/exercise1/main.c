#include <stdio.h> // import for io functions
#include <string.h> // import for strcmp, strchr and strcpy

void clearBuffer(); // letting the program know this function exists

int main() {
    char userString[31]; // initializing a 31 (because we have to include 1 byte for \0) char array
    int sentencesRemaining = 5; // initialize and set to 5, using to show how many sentences left to type to the user in line 19
    int correctSentences; // initializing to keep track of how many sentences we have stored thus far
    int userInput; // initializing the user sentence selector
    char stringArray[6][31]; // initialize a 2d array of 6*31 since we need to store the 31 byte string and 6 since we need to store 5 arrays.
    int validSentence; // bool to to ensure that we never add an invalid sentence

    correctSentences = 0; // set correctSentences to 0 before entering main loop
    while (correctSentences < 5) { // we want 5 sentences from the user, thus we will run this until we have gotten 5 (starting at index 0)
        validSentence = 1; // setting validSentence to true
        printf("Write a sentence, max 30 characters long. %d sentences left. \n", (sentencesRemaining - correctSentences)); // the %d is how many we want vs how many they gave so that we can dynamically tell them how many more than need to type
        fgets(userString, 31, stdin); // collect 30 characters from stdin (inputbuffer) and place it into userString

        if (strchr(userString, '\n') == NULL) { // because fgets will automatically place a \n at the end of a user input, if userString does not contain the \n it means that the inputbuffer was longer than 30 chars and as such its too long
            printf("String too long, try again \n");

            validSentence = 0; // setting to false
            clearBuffer(); // clear the input buffer
            continue; // continue next loop iteration so that we skip the rest of the current while loop (no need to go through it again)
        }
        
        for (int i = 0; i < correctSentences; i++) { // loop to compare strings, going from 0 to how many correctSentences we currently have, if we have none this will be bypassed
            if (strcmp(stringArray[i], userString) == 0) { // comparing the current input string with the i'th index of the array
                printf("String not unique, try again. \n"); // if not unique
                validSentence = 0; // set to false
                break; // break the for-loop so that we may continue with the outer while loop
            } 
        };
        
        if (validSentence == 1) { // if validSentence is true, proceed with the add and +1 the correctSentences counter
            strcpy(stringArray[correctSentences], userString); // because we're not allowed to assign directly into the array, we strcopy the userString into it instead
            correctSentences += 1; // +1 the correctSentences counter
        }
    };

    do { // since we always want to do this first
        userInput = 0; // set userInput to 0 upon each new loop iteration
        printf("Select a sentence by typing a number, 1-5. \n");

        if (scanf("%d", &userInput) != 1) { // if scanf can NOT put the userInput into the %d (digit)
            clearBuffer(); // clear the inputbuffer

            userInput = 0; // set userInput back to 0 from invalid input
        }
    } while (userInput > 5 || userInput < 1); // we want to run the loop as long as userinput is not between 1-5
    printf("Your selected sentence is: %s", stringArray[userInput-1]); // since we're working with 0-index we need to -1
    return 0; // successfully exit the program
}

void clearBuffer() { // clear inputbuffer function to avoid having to write the same lines of code twice
    int buffer; // initialize a buffer int
    while ((buffer = getchar()) != '\n' && buffer != EOF); // while we dont run into a \n or EOF we keep going to successfully clear the buffer
}