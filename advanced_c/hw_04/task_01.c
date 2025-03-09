#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//! Размер слова.
#define WORD_SIZE 20UL

/**
 * @brief Макрос освобождения памяти.
 * @param ptr Указатель на объект, из-под которого нужно высвободить память.
 */
#define FREE_MEMORY(ptr) \
    if ((ptr) != NULL) { \
        free((ptr)); \
        (ptr) = NULL; \
    }

/**
 * @brief Элемент односвязного списка.
 */
typedef struct node {
    char word[WORD_SIZE]; //!< Целевые данные в виде слова.
    struct node *next; //!< Указатель на следующий элемент.
} node;

/**
 * @brief Создать элемент односвязного списка по
 * введенным в консоли данным.
 * @return Указатель на элемент односвязного списка.
 */
node *createNode() {
    node *item = (node *) calloc(1UL, sizeof(node));
    scanf("%[^ .]", item->word);
    return item;
}

/**
 * @brief Добавить элемент item в список head.
 * @param head Заглавный элемент списка.
 * @param item Добавляемый в список элемент.
 */
void addNodeToList(node *head, node *item) {
    if ((head == NULL) || (item == NULL)) {
        return;
    }
    node *tail = head;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = item;
}

/**
 * @brief Поменять содержимое двух элементов списка.
 * @param first Первый элемент списка.
 * @param second Второй элемент списка.
 */
void swapListNodes(node *first, node *second) {
    char tmp[WORD_SIZE];
    memset(tmp, '\0', sizeof(char) * WORD_SIZE);
    strcpy(tmp, first->word);
    strcpy(first->word, second->word);
    strcpy(second->word, tmp);
}

/**
 * @brief Отсортировать список.
 * @attention Алгоритм сортировки может быть
 * не самым оптимальным.
 * @param head Заглавный элемент списка.
 */
void sortList(node *head) {
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    bool isSorted = false;
    while (!isSorted) {
        isSorted = true;
        node *current = head;
        node *next = head->next;
        while (next) {
            if (strcmp(current->word, next->word) > 0) {
                isSorted = false;
                swapListNodes(current, next);
            }
            current = next;
            next = next->next;
        }
    }
}

/**
 * @brief Распечатать список.
 * @details Выводит в строку все элементы списка,
 * кроме заглавного.
 * @param head Заглавный элемент списка.
 */
void printList(node *head) {
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    node *tail = head->next;
    while (tail) {
        printf("%s ", tail->word);
        tail = tail->next;
    }
    printf("\n");
}

/**
 * @brief Очистить список.
 * @param head Заглавный элемент списка.
 */
void deleteList(node *head) {
    if (head == NULL) {
        return;
    }
    node *tail = head;
    while (tail) {
        node *item = tail;
        tail = tail->next;
        FREE_MEMORY(item)
    }
}

int main() {
    node *head = (node *) calloc(1UL, sizeof(node));
    memset(head->word, '\0', sizeof(char) * WORD_SIZE);

    for (char symbol = '0'; symbol != '.'; scanf("%c", &symbol)) {
        addNodeToList(head, createNode());
    }

    sortList(head);
    printList(head);

    deleteList(head);

    return 0;
}
