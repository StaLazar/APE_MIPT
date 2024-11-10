#include <stdio.h>

int main(void) {
    int numCount = 0;

    printf("Input a natural number: ");
    scanf("%d", &numCount);

    const int lowerEdge = 1;
    if (numCount < lowerEdge) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    printf("\nThe list of first %d Fibonacci numbers is following:\n", numCount);
    for (int i = 0, prevNum = 0, curNum = 1; i < numCount; ++i) {
        printf("%d ", curNum);
        const int tempNum = prevNum + curNum;
        prevNum = curNum;
        curNum = tempNum;
    }
    printf("\n");

    return 0;
}
