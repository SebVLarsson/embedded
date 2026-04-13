#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** songs;
    int size;
    int capacity;
} Playlist;

// func to create new play
Playlist* createPlaylist(int capacity) {
    Playlist* pl = malloc(sizeof(Playlist)); // initialize playlist
    pl->capacity = capacity; // set capacity to user input cap
    pl->size = 0; // size is currently 0 so set it to 0
    pl->songs = malloc(capacity * sizeof(char*)); // since cap is 2, we might aswell create enough memory in songs to hold these 2 now with 2 * sizeof char pointer
    return pl; // return the playlist address
}

// func to add song (resize of need)
void addSong(Playlist* pl, const char* song) {
    if (pl->capacity == pl->size) {
        pl->capacity = pl->capacity * 2;
        pl->songs = realloc(pl->songs, pl->capacity * sizeof(char*));
    }
    pl->songs[pl->size] = malloc(strlen(song) + 1);
    strcpy(pl->songs[pl->size++], song);
}

void printPlaylist(Playlist* pl) {
    for (int i = 0; i < pl->size; i++) {
        printf("%d. %s\n", i+1, pl->songs[i]);
    }
}

void freePlaylist(Playlist* pl) {
    for (int i = 0; i < pl->size; i++) {
        free(pl->songs[i]);
    }
    free(pl->songs);
    free(pl);
}

int main() {
    Playlist* pl = createPlaylist(2);
    int choice;
    char song[100];

    while (1) {
        printf("\nSpotify Playlist:\n");
        printf("1. Add Song\n");
        printf("2. Show Playlist\n");
        printf("3. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter song name: ");
                scanf("%s", song);
                addSong(pl, song);
                break;
            case 2:
                printPlaylist(pl);
                break;
            case 3:
                freePlaylist(pl);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid chocie.\n");
        }
    }
    return 0;
}