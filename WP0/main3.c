#include <stdio.h> // we need this to perform io actions such as print
#include <string.h> // we want this for the strlen function to check how many chars the command line argument is
#define MINCHARS 3 // defining our min chars allowed for input since this wont change
#define MAXCHARS 50 // defining our max chars allowed for input since this wont change

int main (int argc, char *argv[]) { // main function, takes # of arguments aswell as those specified cl arguments as parameters
    if (argc < 2) { // ensuring that we error handle for no arguments provided
        printf("No command line argument provided, please provide a name. \n");
        return 0; // returning 0 to successfully close the program
    }

    int strlength; // initializing an int to store the length of the argument strings length
    strlength = strlen(argv[1]); // storing the length of the argument string into our int

    if (MINCHARS <= strlength && strlength <= MAXCHARS ) { // firstly checking if the string is correctly between (inclusive) between 3 and 50 characters long
        printf("Hello %s, how is your day today? \n", argv[1]);
        return 0; // returning 0 to succesfully close the program
    } else if (strlength < MINCHARS) { // since string was not correct, checking whether its smaller than minimum
        printf("Name too short, min 3 characters \n") ;
        return 0; // returning 0 to succesfully close the program
    } else if (strlength > MAXCHARS) { // since string was not correct, checking if its bigger than maximum 
                                       // (this can be just an else but for clarity keeping it an else if)
        printf("Name too long, max 50 characters \n");
        return 0; // returning 0 to succesfully close the program
    }
    return 0;
}