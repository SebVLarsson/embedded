// (C) __Your names here, group: 123 __ (2022)
// Work package 0
// Exercise 1
// Submission code: XXXXXX (provided by your TA-s)
#include <stdio.h> // include for io operation print
#include <string.h> // include to make use of strcmp function
// Main function in the program, no program arguments supported
int main (int argc, char *argv[]) { // main function taking command-line arguments in form of argc/argv    
    for (int i = 1; i < argc; i++) { // we loop from 1 (because 0 is always file name), going through all arguments looking for -h
        if (strcmp(argv[i], "-h") == 0) { // strcmp, if first and second value are equal it will be 0
            printf("To use the program, simply run the program via commandline and input your name as a command line argument. \n");
            return 0; // ending program successfully
        }
    }
    if (argc > 1 && argc < 3) { // ensuring that the user only provided one argument (their name hopefully)
        printf("%s - I'm %s \n", "Hello World!\n", argv[1]); // Note: double quotes
        return 0;  // ending program successfully
    } else { // else we just give them an error message
        printf("Sorry you must provide an argument, for information run the program with -h argument \n");
        return 0;  // ending program successfully
    }
}