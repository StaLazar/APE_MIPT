#include <stdio.h>
#include <stdint.h>

//! Число бит в одном байте.
#define BIT_PER_BYTE 8U

int main(void) {
    uint32_t num = 0U;
    const uint32_t lowerNumEdge = 0U;

    uint32_t shift = 0U;
    const uint32_t lowerShiftEdge = 1U;
    const uint32_t upperShiftEdge = 31U;

    printf("Input an unsigned integer and a natural number not exceeding %u: ", upperShiftEdge);
    scanf("%u %u", &num, &shift);

    if ((num < lowerNumEdge) || (shift < lowerShiftEdge) || (shift > upperShiftEdge)) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    const size_t numSize = BIT_PER_BYTE  * sizeof(num);
    uint32_t result = (num >> shift) | (num << (numSize - shift));

    printf("Result of cyclic shift: %u\n", result);

    return 0;
}
