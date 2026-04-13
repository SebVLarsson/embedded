#include <stdio.h>

int main() {
    int n, i, first_number, second_number, temp;
    printf("What number to calculate?\n");
    scanf("%d", &n);

    for (i = 1; i < n; i++) {
        if (i == 1) {
            first_number = 0;
            second_number = 0;
        } else if (i == 2) {
            second_number = first_number;
            first_number = 1;
        } else {
            temp = second_number;
            second_number = first_number + second_number;
            first_number = temp;
        }
        printf("Num: %d\n", second_number);
    }
}