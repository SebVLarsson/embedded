#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int x;
    int y;
} Piece;

int extract_bits(int byte, int start, int len) {
    return (byte >> start) & ((1u << len) - 1);
}

void print_binary(int n) {
    int num = n;
    printf("0b");
    while (num > 0) {
        printf("%d", (num & 1));
        num >>= 1;
    }
}

int main()
{   
    srand(time(NULL));
    Piece santa;
    santa.x = 127;
    santa.y = 128;
    
    Piece bunny;
    bunny.x = 128;
    bunny.y = 127;
    
    bool meet = false;
    bool santas_turn = false;
    int byte;
    int vert, hor, step_vert, step_hor, draw, double_turn;
    
    while (!meet) {
        byte = rand() % 255;
        step_hor = extract_bits(byte, 0, 2);
        step_vert = extract_bits(byte, 2, 2);
        double_turn = extract_bits(byte, 4, 2);
        hor = extract_bits(byte, 6, 1);
        vert = extract_bits(byte, 7, 1);
        if (!santas_turn) {
            printf("Easter Bunny draws: 0x%x , ", byte);
            print_binary(byte);
            switch (vert) {
                case 0:
                printf(", which means: up, ");
                break;
                case 1:
                printf(", which means: down, ");
                break;
            }
            switch (hor) {
                case 0:
                printf("left, ");
                break;
                case 1:
                printf("right, ");
                break;
            }
            if (double_turn == 3) {
                printf("one more draw, ");
            } else {
                printf("no double draw, ");
            }
            printf("%d steps vertically, ", step_vert);
            printf("%d steps horizontally, ", step_hor);
        } else if (santas_turn) {
            printf("Santa draws: 0x%x", byte);
            print_binary(byte);
            switch (vert) {
                case 0:
                printf(", which means: up, ");
                break;
                case 1:
                printf(", which means: down, ");
                break;
            }
            switch (hor) {
                case 0:
                printf("left, ");
                break;
                case 1:
                printf("right, ");
                break;
            }
            if (double_turn == 3) {
                printf("one more draw, ");
            } else {
                printf("no double draw, ");
            }
            printf("%d steps vertically, ", step_vert);
            printf("%d steps horizontally, ", step_hor);
        }
        
        if (!santas_turn) {
            if (hor == 1) bunny.x += step_hor;
            if (hor == 0) bunny.x -= step_hor;
            if (bunny.x < 0) bunny.x = 255;
            if (bunny.x > 255) bunny.x = 0;
            if (vert == 0) bunny.y += step_vert;
            if (vert == 1) bunny.y -= step_vert;
            if (bunny.y < 0) bunny.y = 255;
            if (bunny.y > 255) bunny.y = 0;
            if (double_turn != 3) {
                santas_turn = !santas_turn;
            }
        } else if (santas_turn) {
            if (hor == 1) santa.x += step_hor;
            if (hor == 0) santa.x -= step_hor;
            if (santa.x < 0) santa.x = 255;
            if (santa.x > 255) santa.x = 0;
            if (vert == 0) santa.y += step_vert;
            if (vert == 1) santa.y -= step_vert;
            if (santa.y < 0) santa.y = 255;
            if (santa.y > 255) santa.y = 0;
            if (double_turn != 3) {
                santas_turn = !santas_turn;
            }
        }
        if (!santas_turn) printf("new position: %d, %d\n", bunny.x, bunny.y);
        else if (santas_turn) printf("new position: %d, %d\n", santa.x, santa.y);
    }
    printf("They met at %d, %d", santa.x, santa.y);
}
