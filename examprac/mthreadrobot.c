#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_PLAYERS 4
#define ROUNDS 10

pthread_mutex_t lock;

typedef struct {
    int id;
    int distance;
} Player;

void* run_robot(void* arg) {
    Player* p = (Player*) arg;
    unsigned short rnd;
    int speed, gear, steps;
    rnd = rand() % 65536;
    // player id = bits 15-14
    p->id = (rnd >> 14) & 0x3;

    for (int round = 0; round < ROUNDS; round++) {
        rnd = rand() % 65536;
        // speed = bits 13-11
        speed = (rnd >> 11) & 0x7;
        // gear = bit 10
        gear = (rnd >> 10) & 1;
        // steps = bits 9-1 (LSB)
        steps = rnd & 0x1FF;
        if (gear == 0) {
            p->distance += -(steps * speed);
        } else if (gear == 1) {
            p->distance += (steps * speed);
        }
        // todo calculate travelled distance and update p->distance
        // todo lock mutex before printing
        pthread_mutex_lock(&lock);
        printf("Player %d, Round %d: Number=%u, ID=%d, Speed=%d, Gear=%d, Steps=%d, Total Distance=%d\n", p->id, round+1, rnd, p->id, speed, gear, steps, p->distance);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

Player* max(Player* a, Player* b) {
    return a->distance > b->distance ? a : b;
}

int main() {
    srand(time(NULL));
    pthread_t threads[NUM_PLAYERS];
    Player players[NUM_PLAYERS];
    pthread_mutex_init(&lock, NULL);
    pthread_t ptrThread0, ptrThread1, ptrThread2, ptrThread3;
    Player p1, p2, p3, p4;
    p1.distance = 0;
    p2.distance = 0;
    p3.distance = 0;
    p4.distance = 0;
    Player* leader1;
    Player* leader2;
    Player* winner;

    pthread_create(&ptrThread0, NULL, run_robot, &p1);
    pthread_create(&ptrThread1, NULL, run_robot, &p2);
    pthread_create(&ptrThread2, NULL, run_robot, &p3);
    pthread_create(&ptrThread3, NULL, run_robot, &p4);

    pthread_join(ptrThread0, NULL);
    pthread_join(ptrThread1, NULL);
    pthread_join(ptrThread2, NULL);
    pthread_join(ptrThread3, NULL);

    leader1 = max(&p1, &p2);
    leader2 = max(&p3, &p4);
    winner = max(leader1, leader2);
    printf("Winner is %d with distance: %d", winner->id, winner->distance);

    // todo initailize players and create threads
    // pthread_create(...)
    // todo: wait for all threads to finish
    // pthread_join(...)
    // todo determine and print the winner
    pthread_mutex_destroy(&lock);
    return 0;
}