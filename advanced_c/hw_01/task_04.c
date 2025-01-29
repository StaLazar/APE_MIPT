#include <stdio.h>
#include <stdint.h>

int main(void) {
    size_t amount = 0U;
    const size_t lowerEdge = 1U;
    const size_t upperEdge = 1000000U;

    printf("Input a natural number not exceeding %lu: ", upperEdge);
    scanf("%lu", &amount);

    if ((amount < lowerEdge) || (amount > upperEdge)) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    uint32_t result = 0;
    for (size_t i = 0; i < amount; ++i) {
        uint32_t number = 0;
        scanf("%u", &number);
        result ^= number;
    }

    printf("The lonely number: %u\n", result);

    return 0;
}
