#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** find_remove_string(char** strings, int* size) {
    int short_idx = 0;
    int shortest = strlen(strings[0]);
    
    for (int i = 1; i < *size; i++) {
        if (strlen(strings[i]) < shortest) {
            short_idx = i;
            shortest = strlen(strings[i]);
        }
    }
    printf("Removed string: %s\n", strings[short_idx]);
    
    for (int i = short_idx; i < *size - 1; i++) {
        strings[i] = strings[i + 1];
    }
    *size -= 1;
    return realloc(strings, *size * sizeof(char*));
}

int main(int argc, char* argv[])
{
    if (argc != 6) {
        printf("Invalid input\n");
        return 0;
    }
    int size = argc - 1;
    char** strings = malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        strings[i] = argv[i + 1];
    }
    printf("Strings input:\n");
    for (int i = 0; i < size; i++) {
        printf("%s\n", strings[i]);
    }
    
    strings = find_remove_string(strings, &size);
    printf("Strings remaining:\n");
    for (int i = 0; i < size; i++){
        printf("%s\n", strings[i]);
    }
    free(strings);
    
    return 0;
}