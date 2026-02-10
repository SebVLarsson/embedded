#include <stdio.h> // for io operations
#include <string.h> // for strlen

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

int main(int argc, char *argv[]) { // main function, arguments enabled
    if (argc != 2) { // checking if its the correct amount of arguments
        printf("Error");
        return 0;
    }
    if (strlen(argv[1]) != 2) { // ensuring that length of argv1 (input) is 2 (2 hex values)
        printf("Error");
        return 0;
    }

    BitMap map = {0}; // initializing our BitMap Union struct to all 0s (getting rid of garbage values)
    char hex_value[3]; // char array for hex value +1 for the end
    strcpy(hex_value, argv[1]); // copy the argument into our hex_value string
    size_t len = strlen(hex_value); // now that we know its correct we just get the length for more readable compares
    int one; // first hex value (left most)
    int two; // second hex value (right most)

    /*
    Extremely messy, we apologise
    We loop over our _TWO_ char array checking if they're 0-9 or A-F
    If i == 0 we know its the first value so we put it into one
    else we put it into two 
    */
    for (int i = 0; i < len; i++) { 
        if (hex_value[i] >= 48 && hex_value[i] <= 57) { // 0-9 ASCII case
            if (i == 0) { // if its the first iteration, put it into one (important for shifting)
                one = hex_value[i] - 48; //remove the "starting" ascii value
            } else { // second iteration, place into two
                two = hex_value[i] - 48; //remove the "starting" ascii value
            }
        } else if (hex_value[i] >= 65 && hex_value[i] <= 70) { // A-F ASCII case
            if (i == 0) { // if its the first iteration, put it into one (important for shifting)
                one = hex_value[i] - 55; //remove the "starting" ascii value
            } else { // second iteration, place into two
                two = hex_value[i] - 55; //remove the "starting" ascii value
            }
        }
    }

    one = one<<4; // because one holds the right most bits, we need to shift them into position to get the correct total
    map.value = one + two; // just add one and two together and place them into map.value and it will "autocorrect" the bits in the struct

    if (map.bits.key_pos < 0 || map.bits.key_pos > 2) { // if keypos is less than 0 or greater than 2, incorrect configuration
        printf("Invalid key choice");
        return 0;
    }
    if (map.bits.gear_pos < 0 || map.bits.gear_pos > 4) { // if gearpos is less than 0 or greater than 4, incorrect configuration
        printf("Invalid gear choice");
        return 0;
    }

    // print the struct
    printf("Name          Value\n");
    printf("-------------------\n");
    printf("engine_on        %d\n", map.bits.engine_on);
    printf("gear_pos         %d\n", map.bits.gear_pos);
    printf("key_pos          %d\n", map.bits.key_pos);
    printf("brake1           %d\n", map.bits.brake1);
    printf("brake2           %d\n", map.bits.brake2);
}