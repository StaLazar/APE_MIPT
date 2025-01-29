#include <stdio.h>
#include <stdint.h>

/**
 * @brief Структура числа с плавающей точкой типа float.
 */
typedef struct {
    uint32_t mantissa : 23; //!< Мантисса.
    uint32_t exponent : 8; //!< Экспонента.
    uint32_t sign : 1; //!< Знак.
} float_fields;

/**
 * @brief "Атомарное" число с плавающей точкой типа float.
 * @details Позволяет оперировать числом как единым целым,
 * а также обращаться к его структурным единицам.
 */
typedef union {
    float number; //<! Число с плавающей точкой типа float.
    float_fields fields; //!< Структура числа с плавающей точкой типа float.
} float_atomic;

/**
 * @brief Получить экспоненту числа с плавающей точкой
 * типа float в виде десятичного целого числа.
 * @param number Число с плавающей точкой типа float.
 * @return Экспонента искомого числа в виде десятичного целого.
 */
int extractExponent(const float number) {
    float_atomic targetNum;
    targetNum.number = number;
    return (int)(targetNum.fields.exponent);
}

int main(void) {
    float number = 0.F;

    printf("Input a float number: ");
    scanf("%f", &number);

    const int result = extractExponent(number);
    printf("Exponent of the specified float number: %d\n", result);

    return 0;
}
