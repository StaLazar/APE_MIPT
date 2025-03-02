#include <stdio.h>
#include <string.h>

//! Максимальный размер входной строки.
#define MAX_INPUT_SIZE 1105UL

/**
 * @brief Получить наибольшее число символов из начала строки template,
 * совпадающих с суффиксом строки source.
 * @details В основе поиска лежит алгоритм Кнута-Морриса-Пратта (КМП),
 * позволяющий находить префикс-функцию от строки за линейное время.
 * @param source Строка, в суффиксе которой осуществляется поиск.
 * @param template Строка, по которой осуществляется поиск.
 * @return 0 - хотя бы одна из строк пуста, иначе - искомое число.
 */
size_t getMaxSuffixOverlap(const char source[MAX_INPUT_SIZE], const char template[MAX_INPUT_SIZE]) {
    if ((source[0] == '\0') || (template[0] == '\0')) {
        return 0UL;
    }

    static const char sep[] = "~";
    const size_t sepLen = strlen(sep);

    const size_t size = 2 * MAX_INPUT_SIZE + sepLen;
    char str[size];
    memset(str, 0, sizeof(char) * size);
    strcat(str, template);
    strcat(str, sep);
    strcat(str, source);

    //! Префикс-функция:
    size_t ps[size];
    memset(ps, 0, sizeof(size_t) * size);
    //! Алгоритм Кнута-Морриса-Пратта (КМП):
    for (size_t i = 1UL; i < size; ++i) {
        size_t j = ps[i - 1UL];
        while ((j > 0UL) && (str[i] != str[j])) {
            j = ps[j - 1UL];
        }
        if (str[i] == str[j]) {
            ps[i] = j + 1UL;
        } else {
            ps[i] = j;
        }
    }

    return ps[strlen(template) + sepLen + strlen(source) - 1UL];
}

int main() {
    char firstStr[MAX_INPUT_SIZE];
    memset(firstStr, 0, sizeof(char) * MAX_INPUT_SIZE);
    char secondStr[MAX_INPUT_SIZE];
    memset(secondStr, 0, sizeof(char) * MAX_INPUT_SIZE);

    printf("Input first string: ");
    scanf("%s", firstStr);
    printf("Input second string: ");
    scanf("%s", secondStr);

    size_t firstResult = getMaxSuffixOverlap(secondStr, firstStr);
    printf("Max suffix overlap for first-to-second: %ld", firstResult);
    size_t secondResult = getMaxSuffixOverlap(firstStr, secondStr);
    printf("Max suffix overlap for second-to-first: %ld", secondResult);

    return 0;
}
