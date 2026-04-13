#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int jack = 0;
int bunny = 0;

pthread_mutex_t lock;

void* game_thread(void* arg) {
    for (int i = 0; i < 10; i++) {
        int byte = rand() % 255;
        if (*(int*)arg == 1) {
            pthread_mutex_lock(&lock);
            printf("Round %d: Bunny draws 1 byte: 0x%x\n", i+1, byte);
            pthread_mutex_unlock(&lock);
        } else {
            pthread_mutex_lock(&lock);
            printf("Round %d: Jack draws 1 byte:  0x%x\n", i+1, byte);
            pthread_mutex_unlock(&lock);
        }
        int move = (byte >> 7) & 1;
        int direction = (byte >> 6) & 1;
        int speed = (byte >> 4) & 0x3;
        int steps = byte & 0xE;
        if (move == 1) {
            if (direction == 1) {
                pthread_mutex_lock(&lock);
                bunny += (speed * steps);
                printf("Bunny moves %d steps forward\n", (speed*steps));
                pthread_mutex_unlock(&lock);
            } else if (direction == 0) {
                pthread_mutex_lock(&lock);
                bunny -= (speed * steps);
                printf("Bunny moves %d steps backward\n", -(speed*steps));
                pthread_mutex_unlock(&lock);
            }
        } else if (move == 0) {
            if (direction == 1) {
                pthread_mutex_lock(&lock);
                jack += (speed * steps);
                printf("Jack moves %d steps forward\n", (speed*steps));
                pthread_mutex_unlock(&lock);
            } else if (direction == 0) {
                pthread_mutex_lock(&lock);
                jack -= (speed * steps);
                printf("Jack moves %d steps backward\n", -(speed*steps));
                pthread_mutex_unlock(&lock);
            }
        }
    }
    pthread_exit(NULL);
    
}

int main() {
    srand(time(NULL));
    pthread_mutex_init(&lock, NULL);
    pthread_t ptrThread0, ptrThread1;
    int bunny_id = 1;
    int jack_id = 0;

    pthread_create(&ptrThread0, NULL, game_thread, &jack_id);
    pthread_create(&ptrThread1, NULL, game_thread, &bunny_id);

    pthread_join(ptrThread0, NULL);
    pthread_join(ptrThread1, NULL);

    if (bunny > jack) {
        printf("Bunny wins, Bunny position: %d, Jack position: %d\n", bunny, jack);
    } else if (bunny < jack) {
        printf("Jack wins, Bunny position: %d, Jack position: %d\n", bunny, jack);
    } else {
        printf("Draw, Bunny position: %d, Jack position: %d\n", bunny, jack);
    }


    pthread_mutex_destroy(&lock);
    return 0;
}