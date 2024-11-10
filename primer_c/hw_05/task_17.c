#include <stdio.h>

#define BASE_10 10 //!< Основание десятичной системы счисления.

int main(void) {
    int edgeNum = 0;

    printf("Input a natural number: ");
    scanf("%d", &edgeNum);

    const int lowerEdge = 10;
    if (edgeNum < lowerEdge) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    printf("\nThe list of magic numbers is following:\n");
    for (int num = lowerEdge; num <= edgeNum; ++num) {
        int numForCalc = num;
        int sum = 0;
        int product = 1;
        while (numForCalc != 0) {
            sum += numForCalc % BASE_10;
            product *= numForCalc % BASE_10;
            numForCalc /= BASE_10;
        }
        if (sum == product) {
            printf("%d ", num);
        }
    }
    printf("\n");

    return 0;
}
