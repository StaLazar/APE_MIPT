#include <stdio.h>
#include <stdint.h>

//! Число бит в одном байте.
#define BIT_PER_BYTE 8U

int main(void) {
    uint32_t num = 0U;
    const uint32_t lowerNumEdge = 0U;

    printf("Input an unsigned integer: ");
    scanf("%u", &num);

    if ((num < lowerNumEdge)) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    const size_t numSize = BIT_PER_BYTE  * sizeof(num);
    size_t bitCounter = 0UL;
    for (size_t i = 0; i < numSize; ++i) {
        bitCounter += ((num >> i) & 0x1) ? 1 : 0;
    }

    printf("Number of raised bits of %u: %ld\n", num, bitCounter);

    return 0;
}
