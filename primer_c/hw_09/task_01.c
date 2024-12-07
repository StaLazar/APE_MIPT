#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

/**
 * @brief Данные об элемете массива.
 */
typedef struct {
    int value; //!< Значение элемента массива.
    size_t idx; //!< Индекс элемента массива.
} ItemData;

/**
 * @brief Проверить наличие элемента в массиве.
 * @param array Массив, в котором осуществляется поиск.
 * @param size Размер массива.
 * @param element Элемент, наличие которого проверяется.
 * @return true - элемент найден в массиве, false - иначе.
 */
bool checkElement(const ItemData *array, const size_t size, const ItemData element) {
    for (size_t i = 0; i < size; ++i) {
        if ((array[i].value == element.value) && (array[i].idx == element.idx)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Отсортировать массив алгоритмом "Пузырек".
 * @param array Массив для сортировки.
 * @param size Размер массива.
 */
void bubbleSort(ItemData *array, const size_t size) {
    for (size_t i = 0; i < size; ++i) {
        bool wasChanged = false;
        for (size_t j = size - 1; j > i; --j) {
            if (array[j - 1].idx > array[j].idx) {
                ItemData tmp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = tmp;
                wasChanged = true;
            }
        }
        if (!wasChanged) {
            break;
        }
    }
}

/**
 * @brief Напечатать в порядке возрастания индексы элементов массива, сумма которых минимальна.
 * @param array Массив элементов.
 * @param size Размер массива.
 * @param count Количество элементов, сумма которых должна быть минимальна.
 */
void printMinSmdsIdx(const int *array, const size_t size, const size_t count) {
    if ((count < 1) || (size < count)) {
        printf("printMinSmdsIdx: the summands' count is out of range!\n");
        return;
    }

    ItemData minSmds[count];
    for (size_t i = 0; i < count; ++i) {
        minSmds[i].value = INT_MAX;
        minSmds[i].idx = INT_MAX;
    }

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < size; ++j) {
            if (array[j] < minSmds[i].value) {
                const ItemData newMinSmd = {array[j], j};
                if (checkElement(minSmds, count, newMinSmd)) {
                    continue;
                }
                minSmds[i] = newMinSmd;
            }
        }
    }

    bubbleSort(minSmds, count);

    printf("\nThe min summands' indexes:\n");
    for (size_t i = 0; i < count; ++i) {
        printf("%ld ", minSmds[i].idx);
    }
    printf("\n");
}

int main(void) {
    const size_t size = 30;
    int numArray[size];
    const size_t smdsCount = 2;

    printf("Input a list of %ld integer numbers:\n", size);
    for (size_t i = 0; i < size; ++i) {
        scanf("%d", &numArray[i]);
    }

    printMinSmdsIdx(numArray, size, smdsCount);

    return 0;
}
