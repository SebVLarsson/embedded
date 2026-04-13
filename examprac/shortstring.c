#include <stdio.h>
#include <string.h>

void find_and_remove_string(char **strings, int *size) {
    int shortest = strlen(strings[0]);
    int short_idx = 0;
    
    for (int i = 1; i < *size; i++) {
        if (strlen(strings[i]) < shortest) {
            shortest = strlen(strings[i]);
            short_idx = i;
        }
    }
    
    printf("Removed string: %s\n", strings[short_idx]);
    
    for (int i = short_idx; i < *size - 1; i++) {
        strings[i] = strings[i + 1];
    }
}

int main(int argc, char *argv[])
{
    if (argc < 4 || argc > 11) {
        printf("Incorrect amount of strings\n");
        return 0;
    }
    
    char **strings = &argv[1];
    int size = argc - 1;
    
    find_and_remove_string(strings, &size);
    printf("Remaining strings:\n");
    for (int i = 0; i < argc - 1; i++) {
        printf("%s\n", strings[i]);
    }
    
    return 0;
}
