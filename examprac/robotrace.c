#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLAYERS 4
#define ROUNDS 10


typedef struct {
    int player_id;
    int position;
    int last_byte;
} Player;

int extract_bits(int byte, int start, int len) {
    return (byte >> start) & ((1u << len) - 1);
}

int main()
{
    srand(time(NULL));
    int id, speed, direction, steps;
    int byte;
    char* dir;
    Player** player_array = malloc(MAX_PLAYERS * sizeof(Player*));
    for (int i = 0; i < MAX_PLAYERS; i++) {
        Player* player = (Player*)malloc(sizeof(Player));
        byte = rand() % 32767;
        id = extract_bits(byte, 14, 2);
        player->player_id = id;
        player_array[i] = player;
    }
    Player* current_player;
    for (int rnd = 0; rnd < ROUNDS; rnd++) {
        for (int robot = 0; robot < MAX_PLAYERS; robot++) {
            byte = rand() % 32767;
            current_player = player_array[robot];
            current_player->last_byte = byte;
            speed = extract_bits(byte, 11, 3);
            direction = extract_bits(byte, 10, 1);
            steps = extract_bits(byte, 1, 9);
            if (direction == 1) current_player->position += (speed*steps);
            else current_player->position -= (speed*steps);
        }
        for (int rob = 0; rob < MAX_PLAYERS; rob++) {
            current_player = player_array[rob];
            byte = current_player->last_byte;
            speed = extract_bits(byte, 11, 3);
            direction = extract_bits(byte, 10, 1);
            steps = extract_bits(byte, 1, 9);
            if (direction == 1) {
                dir = "forward";
            } else {
                dir = "backward";
            }
            printf("Round #%d: Player %d number last round: %d, speed=%d, direction=%s, steps=%d\n", rnd+1, rob+1, byte, speed, dir, steps);
        }
        printf("After Round #%d:\n", rnd+1);
        for (int rnd_stat = 0; rnd_stat < MAX_PLAYERS; rnd_stat++) {
            current_player = player_array[rnd_stat];
            printf("Player %d: Distance=%d\n", rnd_stat+1, current_player->position);
        }
    }
    for (int i = 0; i < MAX_PLAYERS; i++) {
        free(player_array[i]);
    }
    free(player_array);
    return 0;
}