#include <stdio.h> // io operations
#include <stdlib.h> // for atoi
#include <ctype.h> // for atoi


/*
Because using the union struct combination, we never actually have to shift ourselves, the compiler sort of does it for us
Theoretically speaking, you can simply input an integer in value and that will also set the correct bits
Very nifty thing!
*/
#pragma pack(1) // Ensuring that we pack everything into 1 byte
typedef union {
    unsigned char value;  // Access as a single 8-bit value (0-255)

    // Car struct
    struct {
        unsigned brake2 : 1;  // Rear brakes (Bit 0) (LSB)
        unsigned brake1 : 1;  // Front brakes (Bit 1)
        unsigned key_pos : 2;  // Key position (Bit 2, 3)
        unsigned gear_pos : 3;  // Gear position (Bit 4, 5, 6)
        unsigned engine_on : 1;  // Ignition (Bit 7) (MSB)
    } bits;
} BitMap;
#pragma pack() // end pack


int main(int argc, char *argv[]) { // main functions, arguments enabled
    if (argc != 6) { // incorrect amount of arguments
        printf("Error, invalid amount of arguments");
        printf("Usage - engine_on gear_pos key_pos brake1 brake2");
        return 0;
    }

    // looping over the arguments to ensure that all of them are digits!
    for (int j = 1; j < argc; j++) {
        for (int i = 0; argv[j][i] != '\0'; i++) { //loop until \0 character
            if (!isdigit(argv[j][i])) { // if not digit
                printf("Error: Invalid number.\n");
                return 0; 
            }
        }

        // switch casing j to ensure they are correct values
        // j is the different arguments, 1 engine_pos, 2 gear_pos, 3 key_pos, 4 front brake, 5 rear break
        switch (j) {
                case 1: // engine_pos
                if (atoi(argv[j]) < 0 || atoi(argv[j]) > 1) { // checking if argument is valid input
                    printf("Invalid input\n");
                    return 0;
                }
                break;
                case 2: // gear_pos
                if (atoi(argv[j]) < 0 || atoi(argv[j]) > 4) {// checking if argument is valid input
                    printf("Invalid input\n");
                    return 0;
                }
                break;
                case 3: // key_pos
                if (atoi(argv[j]) < 0 || atoi(argv[j]) > 2) {// checking if argument is valid input
                    printf("Invalid input\n");
                    return 0;
                }
                break;
                case 4: //front rake
                if (atoi(argv[j]) < 0 || atoi(argv[j]) > 1) {// checking if argument is valid input
                    printf("Invalid input\n");
                    return 0;
                }
                break;
                case 5: // rear brake
                if (atoi(argv[j]) < 0 || atoi(argv[j]) > 1) {// checking if argument is valid input
                    printf("Invalid input\n");
                    return 0;
                }
            }
    }


    BitMap map = {0}; // initialize map and set all values to 0 to get rid of garbage values

    map.bits.engine_on = atoi(argv[1]); // set value to argument with atoi (ASCII TO INT)
    if (atoi(argv[2]) < 0 || atoi(argv[2]) > 4) {
        printf("Invalid gear");
        return 0;
    }
    map.bits.gear_pos = atoi(argv[2]); // set value to argument with atoi (ASCII TO INT)
    map.bits.key_pos = atoi(argv[3]); // set value to argument with atoi (ASCII TO INT)
    map.bits.brake1 = atoi(argv[4]); // set value to argument with atoi (ASCII TO INT)
    map.bits.brake2 = atoi(argv[5]); // set value to argument with atoi (ASCII TO INT)

    printf("%02X\n", map.value); // print as HEX, %02X is 2 HEX values
}