#include <stdio.h>
#include <stdint.h>

/**
 * @brief Элемент односвязного списка.
 */
typedef struct list {
    uint64_t address; //!< Адрес блока памяти.
    size_t size; //!< Размер блока памяти.
    char comment[64]; //!< Данные (?).
    struct list *next; //!< Указатель на следующий элемент.
} list;

/**
 * @brief Получить адрес наибольшего по размеру блока памяти.
 * @param head Указатель на первый элемент односвязного списка.
 * @return Адрес наибольшего по размеру блока памяти, если в списке
 * есть элементы, а иначе - 0.
 */
uint64_t findMaxBlock(list *head) {
    if (head == NULL) {
        return 0;
    }
    size_t max = 0UL;
    uint64_t address = 0U;
    for (list *ptr = head; ptr != NULL; ptr = ptr->next) {
        if (ptr->size > max) {
            max = ptr->size;
            address = ptr->address;
        }
    }
    return address;
}

int main(void) {
    list thirdNode = {140525067852320U, 10UL, "Third", NULL};
    list secondNode = {140525067852350U, 30UL, "Second", &thirdNode};
    list firstNode = {140525067852900U, 100UL, "First", &secondNode};

    list *head = &firstNode;
    printf("Max block's address: %ld\n", findMaxBlock(head));

    return 0;
}
