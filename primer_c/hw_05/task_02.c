#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int numbers[2] = {0, 0};
    const int edgeNum = 100;

    printf("Input 2 integer numbers in ascending order, which are not exceeding modulo %d: ",
           edgeNum);
    scanf("%d %d", &numbers[0], &numbers[1]);

    if ((numbers[1] < numbers[0])) {
        printf("Interrupting: the numbers are not in ascending order!\n");
        return 1;
    }

    if ((abs(numbers[0]) > edgeNum) || (abs(numbers[1]) > edgeNum)) {
        printf("Interrupting: the numbers are out of range!\n");
        return 2;
    }

    printf("\nThe list of squares in [%d; %d]:\n", numbers[0], numbers[1]);
    for (int number = numbers[0]; number <= numbers[1]; ++number) {
        printf("%d ", number * number);
    }
    printf("\n");

    return 0;
}