#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//! Максимальный размер стека.
#define MAX_STACK_SIZE 10UL
//! Максимальное количество разрядов в числе.
#define MAX_DIGITS_COUNT 20UL
//! Основание десятичной системы счисления.
#define BASE_10 10

/**
 * @brief Стек - коллекция элементов, организованных по принципу LIFO.
 */
typedef struct stack {
    unsigned long data[MAX_STACK_SIZE]; //!< Массив целевых данных.
    size_t size; //!< Текущий размер.
} stack;

/**
 * @brief Инициализировать стек.
 * @param storage Стек для инициализации.
 */
void initStack(stack *storage) {
    memset(storage->data, 0, sizeof(unsigned long) * MAX_STACK_SIZE);
    storage->size = 0UL;
}

/**
 * @brief Поместить элемент в стек.
 * @param storage Стек, в который будет добавлен новый элемент.
 * @param element Элемент для добавления в стек.
 */
void putToStack(stack *storage, const unsigned long element) {
    assert(storage->size < MAX_STACK_SIZE);
    storage->data[storage->size] = element;
    ++storage->size;
}

/**
 * @brief Извлечь элемент из стека.
 * @param storage Стек, из которого будет извлечен элемент.
 * @return Крайний элемент, хранившийся в стеке.
 */
unsigned long fetchFromStack(stack *storage) {
    assert(storage->size > 0UL);
    --storage->size;
    unsigned long result = storage->data[storage->size];
    storage->data[storage->size] = 0UL;
    return result;
}

int main() {
    stack storage;
    initStack(&storage);

    char numStr[MAX_DIGITS_COUNT];
    memset(numStr, '\0', sizeof(char) * MAX_DIGITS_COUNT);
    size_t vacantIdx = 0UL;

    char symbol = '0';
    const char finalSymbol = '.';
    printf("Input reverse Polish notation ending with '%c':\n", finalSymbol);
    for (scanf("%c", &symbol); symbol != finalSymbol; scanf("%c", &symbol)) {
        if (isdigit(symbol) && (vacantIdx < MAX_DIGITS_COUNT)) {
            numStr[vacantIdx++] = symbol;
            continue;
        }
        if (numStr[0] != '\0') {
            putToStack(&storage, strtoul(numStr, NULL, BASE_10));
            memset(numStr, '\0', sizeof(char) * MAX_DIGITS_COUNT);
            vacantIdx = 0UL;
        }
        if (symbol == '+') {
            const unsigned long secondOperand = fetchFromStack(&storage);
            const unsigned long firstOperand = fetchFromStack(&storage);
            putToStack(&storage, firstOperand + secondOperand);
        } else if (symbol == '-') {
            const unsigned long secondOperand = fetchFromStack(&storage);
            const unsigned long firstOperand = fetchFromStack(&storage);
            putToStack(&storage, firstOperand - secondOperand);
        } else if (symbol == '*') {
            const unsigned long secondOperand = fetchFromStack(&storage);
            const unsigned long firstOperand = fetchFromStack(&storage);
            putToStack(&storage, firstOperand * secondOperand);
        } else if (symbol == '/') {
            const unsigned long secondOperand = fetchFromStack(&storage);
            const unsigned long firstOperand = fetchFromStack(&storage);
            putToStack(&storage, firstOperand / secondOperand);
        }
    }

    printf("Result of computation: %ld\n", fetchFromStack(&storage));

    return 0;
}
