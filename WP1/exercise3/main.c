#include <stdio.h> // include for io operations
#include <stdlib.h> // include for atoi and rand
#include <ctype.h> // include for isdigit
#define MAX_GUESSES 10
// #define RANDOM_MIN 1
// #define RANDOM_MAX 100

void clearBuffer(); // initializing clearBuffer function

int main() {
    // int number = rand() % (RANDOM_MAX - RANDOM_MIN + 1) + RANDOM_MIN;
    int number = 30; // hardcoded for codegrade
    char userChoice[4]; // input array
    int userNumber; // initializing int for atoi into it if correct input by user
    int incorrectGuesses = 0; // initializing guess counter

    while (1) { // from research this is the C equivalent of while (True), Can apparently also use for (;;)
        printf("1. New round\n0. Finish?\n");
        fgets(userChoice, 4, stdin); // taking user input

        int validInput = 1; // setting up a boolean int
        for (int i = 0; userChoice[i] != '\0' && userChoice[i] != '\n'; i++) {  // looping through user input to look for invalid input
            if (!isdigit(userChoice[i])) { // if theres a non-digit its invalid input
                printf("Error: Invalid number.\n");
                userChoice[0] = '\0'; // setting userChoice 0 to \0 to "clear the array" (We're not really since the rest of the input will still be in memory)
                validInput = 0;       // However since the first char will always be \0 and every read of the array is a loop, it will always terminate on first char
                clearBuffer(); // clear buffer incase of overflow
                break; // break the for loop since we found invalid input
            }
        }

        if (!validInput) { // if invalid input we need to skip the rest of the loop
            continue;
        }

        userNumber = atoi(userChoice); // convert userinput into a int
        if (userNumber < 0 || userNumber > 1) { // checking if input integer is a valid choice
            printf("Press 1 for new game, 0 for finish\n");
            clearBuffer(); // clear the buffer in case the user input an int larger than 2.13b
            continue; // continue to skip the rest of the while loop
        }   
        
        if (userNumber == 0) { // exiting program if user selected finish
            return 0;
        } else if (userNumber == 1) { // entering game loop if user selected new round
            printf("Guess the number\n");
            while (fgets(userChoice, 4, stdin) && incorrectGuesses < MAX_GUESSES) { // since fgets will not be valid if EOF is input, it functions fairly well as a while condition
                
                /*
                Same codeblock as above, looping through userInput to find invalid input
                START */
                int validInput = 1;
                for (int i = 0; userChoice[i] != '\0' && userChoice[i] != '\n'; i++) { 
                    if (!isdigit(userChoice[i])) { 
                        printf("Error: Invalid number.\n");
                        userChoice[0] = '\0'; 
                        validInput = 0;
                        clearBuffer();
                        break;
                    }
                }
            
                if (!validInput) {
                    continue;
                }
                /*
                Same codeblock as above, looping through userInput to find invalid input
                END */


                userNumber = atoi(userChoice);

                if (userNumber == 0) { // exit game if user wants to instantly exit
                    return 0;
                } else if (userNumber < 1 || userNumber > 100) { // checking if user input a valid integer
                    printf("Your guess is outside of the accepted range\n");
                    printf("Guess the number\n");
                    clearBuffer(); // clear buffer incase the user input an int larger than 2.13b something
                    continue; // skip the rest of the while loop
                }

                if (userNumber < number) { // low number case
                    incorrectGuesses += 1;
                    printf("Your guess is too low, you have %d guesses remaining\n", MAX_GUESSES-incorrectGuesses);
                } else if (userNumber > number) { // high number case
                    incorrectGuesses += 1;
                    printf("Your guess is too high, you have %d guesses remaining\n", MAX_GUESSES-incorrectGuesses);
                } else { // since we checked for invalid input, invalid number, low case and high case, we should in theory only have correct guess remaining
                    printf("You have guessed %d times and your guess is correct\n", incorrectGuesses);
                    break; // break game loop
                }
                printf("Guess the number\n");
            }

            if (incorrectGuesses >= MAX_GUESSES) { // if the user ran out of guesses
                printf("Too many guesses, you lose :)\n");
            }

        }
    }
}


void clearBuffer() { // clear inputbuffer function to avoid having to write the same lines of code twice
    int buffer; // initialize a buffer int
    while ((buffer = getchar()) != '\n' && buffer != EOF); // while we dont run into a \n or EOF we keep going to successfully clear the buffer
}