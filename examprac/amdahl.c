#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ITERATIONS 100

double speedup(double S, unsigned int N) {
    double fix_s = S/100;
    double result = 1/(fix_s+((1-fix_s)/N));
    printf("S = %.2f, N = %d, ", fix_s, N);
    return result;
}

int main()
{
    srand(time(NULL));
    
    for (int i = 0; i < ITERATIONS; i++) {
        printf("Choice #%d: ", i+1);
        printf(", speedup = %.2f\n", speedup((rand()%100), (rand()%100)+1));
    }
    return 0;
}
