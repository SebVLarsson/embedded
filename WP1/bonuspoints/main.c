#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int printBinary(int n);

int main(int argc, char* argv[]) {
    if (argc < 2 && argc > 2) {
        printf("Incorrect input, exiting... \n");
        return 1;
    }
    
    for (int i = 0; i < strlen(*argv[1]); i++) {
        if (!isdigit(*argv[1])) {
            printf("Incorrect input, exiting... \n");
            return 1;
        }
    }

    int exitCode;

    int n = atoi(argv[1]);

    exitCode = printBinary(n);
    if (exitCode == 0){
        return 0;
    } else {
        return 1;
    }
    return 0;
}

int printBinary(int n) {
    printf("%b", n);

    return 0;
}