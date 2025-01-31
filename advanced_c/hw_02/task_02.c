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
 * @brief Получить суммарный размер памяти, занятый односвязным списком.
 * @param head Указатель на первый элемент односвязного списка.
 * @return Суммарный размер памяти, занятый односвязным списком, если
 * в нем есть элементы, а иначе - 0.
 */
size_t totalMemoryUsage(list *head) {
    if (head == NULL) {
        return 0U;
    }
    size_t totalSize = 0UL;
    for (list *ptr = head; ptr != NULL; ptr = ptr->next) {
        totalSize += ptr->size;
    }
    return totalSize;
}

int main(void) {
    list thirdNode = {140525067852320U, 10UL, "Third", NULL};
    list secondNode = {140525067852350U, 30UL, "Second", &thirdNode};
    list firstNode = {140525067852900U, 100UL, "First", &secondNode};

    list *head = &firstNode;
    printf("Total memory usage: %ld\n", totalMemoryUsage(head));

    return 0;
}
