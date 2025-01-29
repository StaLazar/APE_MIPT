#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define BASE_2 2 //!< Основание двоичной системы счисления.

int main(void) {
    uint32_t num = 0U;
    const uint32_t lowerNumEdge = 0U;

    uint32_t bitRange = 0U;
    const uint32_t lowerBitRangeEdge = 1U;
    const uint32_t upperBitRangeEdge = 31U;

    printf("Input an unsigned integer and a natural number not exceeding %u: ", upperBitRangeEdge);
    scanf("%u %u", &num, &bitRange);

    if ((num < lowerNumEdge) || (bitRange < lowerBitRangeEdge) || (bitRange > upperBitRangeEdge)) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    uint32_t result = 0U;
    for (size_t i = 0; i < bitRange; ++i) {
        const uint8_t bit = (num >> i) & 0x1;
        result += bit * pow(BASE_2, i);
    }

    printf("Result of the magic operation: %u\n", result);

    return 0;
}
