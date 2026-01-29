#include <stdio.h> // include for io operations
#include <stdlib.h> // include for use of atoi since we need to convert a string to integer
#include <ctype.h> // include for isdigit so that we can ensure that argument is a digit

void printBinary(int n); // letting the program know this functions exists

int main(int argc, char* argv[]) { // taking arguments via command line
    if (argc != 2) { // since we only want one argument we ensure we only accept 2 arguments (1 is by default, 2nd is for the actualy command line argument)
        printf("Error: No number provided. Please provide a number as a command line argument.\n");
        return 0; // return error status code since we did not get the correct amount of arguments
    }
    
    /* Because argv is by default a string, or a char*, we need to loop through whatever the user put into the command line argument
    Because all strings are terminated with \0 we simply loop through the character array until we hit the \0*/
    for (int i = 0; argv[1][i] != '\0'; i++) { // 
        if (!isdigit(argv[1][i])) { // for each character in the char array we check, is this not a digit?
            printf("Error: Invalid number.\n"); 
        return 0; // if any of the chars within the string is NOT a digit, we exit with error code 1
        }
    }

    int n = atoi(argv[1]); // converting the argv string into int now that we know its an actual digit using ATOI (ASCII TO INTEGER)

    printBinary(n); // send our integer into the binary function
    return 0; // exit with successful runtime code 0
}

/*  The idea here is that we will store 1's and 0's into a integer array of 32
    My idea of shifting (which I would love feedback on whether im right or wrong in my thinking here)
    is that if we have 8 bits: 00101011 - if we use the '& 1' operator combination we will by default always get the right most bit (least significant bit (LSB))
    After we extract the 1 or 0 from the rightmost bit and shift right, we will move the entire "memoryblock" one step to the right but the "pointer" stays in the same position
    and in doing so, fill in with 0s on the left so our original will now be 00010101 and then next iteration 00001010 etc */

void printBinary(int n) { // function to convert and print any integer into binary and list the amount of 0's and 1's
if (n == 0) { // base case, incase the user put in a 0
    printf("0b0\nAmount of zeroes: 1\nAmount of ones: 0\n");
    return;
}

int number = n; // since we're shifting with n we need to store the original number for print purposes later
int bits[32]; // since a regular int is 32 bits, we only need 32 numbers/bits into our int array
int zero = 0; // initializing and setting zeros to 0
int one = 0; // initializing and setting ones to 0
int i = 0; // index variable to keep our while loop running

while (n != 0) { // keep the loop running until our number n is 0

    /* Using the bitwise AND operator here to take the RIGHTMOST bit, comparing it to 1 (which will inherently always be howevermany 0's followed by a 1 in the rightmost bit)
    If the bit from n we're looking at is a 1, because the rightmost bit in 1 is always a 1, we get 1's, this will in turn prove to us that the rightmost bit is a 1
    We then store this into the bit array, if the current bit positin of n is a 0, because both the n bit and 1 has different bits, this will give us a 0 
    We then store this in our number/bit array*/
    bits[i] = n & 1;
    if (bits[i] == 1) { // saving our statistics, if its a 1, we +1 the one variable
        one += 1;
    } else { // if its a 0, we +1 the zero variable
        zero += 1;
    }
    i++; // increment our loop indexer by 1
    n >>= 1; // shift our bits 1 step to the right, thus giving us the bit left of the current for our next iteration
}

printf("Number: %d\n", number); // printing the original n which we saved into number
printf("Binary: 0b"); // to show that we're giving the user a binary (0b) and not hex (0x)
for (int j = i - 1; j >= 0; j--) { // loop through the bits, reversing order since we want the left most bit from the original, left most here
    printf("%d", bits[j]); // print the current bit in j loop
}
printf("\nNumber of 0s: %d \nNumber of 1s: %d \n", zero, one); // printing the 0s and 1s statistics
}