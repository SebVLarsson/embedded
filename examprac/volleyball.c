#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int team_a_score = 0;
int team_b_score = 0;

int extract_bytes(int byte, int start, int len) {
    return (byte >> start) & ((1u << len) - 1);
}

int main()
{
    srand(time(NULL));
    int** bytes_array = malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        bytes_array[i] = malloc(10 * sizeof(int));
        for (int j = 0; j < 10; j++) {
            int byte = rand() % 255;
            bytes_array[i][j] = byte;
        }
    }
    
    int acting_team = 0;
    int action = 0;
    int action_mult = 0;
    int action_eff = 0;
    for (int rnd = 0; rnd < 10; rnd++) {
        for (int team = 0; team < 2; team++) {
            acting_team = extract_bytes(bytes_array[team][rnd], 7, 1);
            action = extract_bytes(bytes_array[team][rnd], 6, 1);
            action_mult = extract_bytes(bytes_array[team][rnd], 4, 2);
            action_eff = extract_bytes(bytes_array[team][rnd], 0, 4);
            
            if (acting_team == 1) {
                if (action == 1) {
                    team_a_score += (action_mult * action_eff);
                } else {
                    team_b_score -= (action_mult * action_eff);
                    if (team_b_score < 0) {
                        team_b_score = 0;
                    }
                }
            } else if (acting_team == 0) {
                if (action == 1) {
                    team_b_score += (action_mult * action_eff);
                } else {
                    team_a_score -= (action_mult * action_eff);
                    if (team_a_score < 0) {
                        team_a_score = 0;
                    }
                }
            }
        }
    }
    if (team_a_score > team_b_score) {
        printf("Team A wins, %d - %d\n", team_a_score, team_b_score);
    } else if (team_a_score < team_b_score) {
        printf("Team B wins, %d - %d\n", team_b_score, team_a_score);
    } else {
        printf("Draw: %d - %d\n", team_a_score, team_b_score);
    }
    
    
    for (int j = 0; j < 2; j++) {
        free(bytes_array[j]);
    }
    free(bytes_array);
}