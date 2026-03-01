#include <stdio.h> // for printf

#pragma pack(1) // Ensuring that we pack everything into 1 byte
typedef union {
    unsigned char value;  // Access as a single 8-bit value (0-255)

    // elevator operation struct
    struct {
        unsigned brake2 : 1;  // Emergency brakes (Bit 0) (LSB)
        unsigned brake1 : 1;  // normal brakes (Bit 1)
        unsigned door_pos : 2;  // open/close elevator doors (Bit 2, 3)
        unsigned floor_pos : 3;  // What floor elevator is on currently (Bit 4, 5, 6)
        unsigned engine_on : 1;  // Elevator engine on/off (Bit 7) (MSB)
    } bits;
} BitMap;
#pragma pack()

// function inits
int validate_arguments(int *argc, char *argv[]);
void set_bits(BitMap *map, char *argv[]);
// end function inits


// main function, arguments enabled
int main(int argc, char *argv[]) {
    // sent argc and argv to validate_arguments to ensure they are valid and store the return value in an int
    int valid_args = validate_arguments(&argc, argv);

    // if the int returned from validate_arguments was not 0, invalid input so we print and exit
    if (valid_args != 0) {
        printf("Invalid input\n");
        return 0; // exit
    }

    // initialize our BitMap, set all initial values to 0 via {0}
    BitMap map = {0};
    set_bits(&map, argv); // send our map by pointer to set_bits together with argv

    printf("0x%02X\n", map.value); // print the hex value of the BitMap
    return 0; // successful execution
    
}

// function to validate all arguments, including amount
int validate_arguments(int *argc, char *argv[]) {
    if (*argc != 6) return 1; // must be 6
    for (int i = 1; i <= 5; i++) { // since we know we have 6 arguments, loop from 1-5 and check them all
        if (argv[i][1] != '\0') return 1; // check to see that each input is single digit
        switch (i) { // switch case the for loop to check each bit individually
            // bit 7
            case 1:
            // bit 7 can only be 1 or 0
            if (argv[i][0] != '1' && argv[i][0] != '0') return 1; 
            break;
            // bit 6, 5, 4
            case 2:
            // bit 6, 5, 4 can be between 0-7 so we check by ascii value that it is within the acceptable span
            if (argv[i][0] < '0' || argv[i][0] > '7') return 1; 
            break;
            // bit 2, 3
            case 3:
            // 
            /*
             * bit 2, 3 can only be 1 (2⁰ -> 01) or 2 (2¹ -> 10)
             * there is an argument to be had here that perhaps 0 (00) and 1 (01) would be the correct inputs
             * or even 00 (0) and 11 (3) albeit this one slightly less logically sound
             * but the wording of the assignment made me feel like 01 and 10 as implemented is correct
            */
            if (argv[i][0] != '1' && argv[i][0] != '2') return 1;
            break;
            // bit 1
            case 4:
            // bit 1 can only be 1 or 0
            if (argv[i][0] != '1' && argv[i][0] != '0') return 1;
            break;
            // bit 0
            case 5:
            // bit 0 can only be 1 or 0
            if (argv[i][0] != '1' && argv[i][0] != '0') return 1;
            break;
        }
    }
    return 0; // valid input
}


// function to set the bits correctly
void set_bits(BitMap *map, char *argv[]) {
    /*
     * Simple for loop to go from 1-5 and switch case i for bit positions
     * We then assign via pointer the values by taking the ascii values since argv is char/string
     * Deduct the ascii value of 0 to get the correct integer value
    */
    for (int i = 1; i <= 5; i++) {
        switch (i) {
            case 1: // bit 7
                map->bits.engine_on = argv[i][0] - '0'; break;
            case 2: // bit 6, 5, 4
                map->bits.floor_pos = argv[i][0] - '0'; break;
            case 3: // bit 3, 2
                map->bits.door_pos = argv[i][0] - '0'; break;
            case 4: // bit 1
                map->bits.brake1 = argv[i][0] - '0'; break;
            case 5: // bit 0
                map->bits.brake2 = argv[i][0] - '0'; break;
            }
    }
}