#include <stdio.h>

int contains_substring(const char* stringone, const char* substring) {
    int j = 0;
    int len = 0;
    while (substring[len] != '\n' && substring[len] != '\0') {
        len++;
    }
    for (int i = 0; stringone[i] != '\0' && stringone[i] != '\n'; i++) {
        while (substring[j] != '\0' && substring[j] != '\n' && stringone[i+j] == substring[j]) j++;
        if (j == len) return i;
    }
    return -1;
}

int main()
{
    char buffer[256];
    char buffertwo[256];
    int idx;
    printf("Write string, no spaces: \n");
    scanf("%255s", &buffer);
    printf("Write second string no spaces: \n");
    scanf("%255s", &buffertwo);
    idx = contains_substring(buffer, buffertwo);
    if (idx != -1) {
        printf("Index of string: %d", idx);
    } else {
        printf("String not found");
    }
    return 0;
}