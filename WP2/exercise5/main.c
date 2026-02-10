#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


// Defining a BitField struct, ' : number' signifies how many bits the variable contains
struct BitField {
    unsigned char brake2 : 1; // lsb
    unsigned char brake1 : 1;
    unsigned char key_pos : 2;
    unsigned char gear_pos : 3;
    unsigned char engine_on : 1; // msb
};

// Defining our union to map from from value to bit
union Map {
    unsigned char binmode;
    struct BitField convert;
};

void print_binary(unsigned int bitmap, int bits);

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Error, invalid amount of arguments");
        printf("Usage - engine_on gear_pos key_pos brake1 brake2");
        return 0;
    }
    for (int j = 1; j < argc; j++) {
        for (int i = 0; argv[j][i] != '\0'; i++) { 
            if (!isdigit(argv[j][i])) { 
                printf("Error: Invalid number.\n");
                return 0; 
            }
        }
        switch (j) {
                case 1:
                if (atoi(argv[j]) < 0 || atoi(argv[j]) > 1) {
                    printf("Invalid input\n");
                    return 0;
                }
                break;
                case 2:
                if (atoi(argv[j]) < 0 || atoi(argv[j]) > 7) {
                    printf("Invalid input\n");
                    return 0;
                }
                break;
                case 3: 
                if (atoi(argv[j]) < 0 || atoi(argv[j]) > 2) {
                    printf("Invalid input\n");
                    return 0;
                }
                break;
                case 4: 
                if (atoi(argv[j]) < 0 || atoi(argv[j]) > 1) {
                    printf("Invalid input\n");
                    return 0;
                }
                break;
                case 5:
                if (atoi(argv[j]) < 0 || atoi(argv[j]) > 1) {
                    printf("Invalid input\n");
                    return 0;
                }
            }
    }

    union Map map = {0};
    char *binary_string;
    map.convert.engine_on = atoi(argv[1]);
    if (atoi(argv[2]) < 0 || atoi(argv[2]) > 7) {
        printf("Invalid gear");
        return 0;
    }
    map.convert.gear_pos = atoi(argv[2]);
    map.convert.key_pos = atoi(argv[3]);
    map.convert.brake1 = atoi(argv[4]);
    map.convert.brake2 = atoi(argv[5]);
    size_t mapsize = alignof(map);
    printf("%lu", sizeof(map));
    printf("%zu", mapsize);

    printf("Name          Value\n");
    printf("-------------------\n");
    printf("engine_on        ");
    print_binary(map.convert.engine_on, 1);
    printf("\n");
    printf("gear_pos         ");
    print_binary(map.convert.gear_pos, 3);
    printf("\n");
    printf("key_pos          ");
    print_binary(map.convert.key_pos, 2);
    printf("\n");
    printf("brake1           ");
    print_binary(map.convert.brake1, 1);
    printf("\n");
    printf("brake2           ");
    print_binary(map.convert.brake2, 1);
    printf("\n");
}

void print_binary(unsigned int bitmap, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (bitmap >> i) & 1);
    }
}