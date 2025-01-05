#pragma once

#include <stdio.h>
#include <stdbool.h>

/**
 * @ingroup common
 * @{
 */

//! Тип функции сравнения элементов вектора.
typedef int (vector_cmp)(const void *, const void *);

/**
 * @brief Контейнер типа "Вектор".
 * @details Представляет собой усеченный аналог std::vector из C++,
 * т.е. коллекцию переменного размера произвольного типа данных
 * (https://en.cppreference.com/w/cpp/container/vector).
 */
typedef struct {
    void **data; //<! Массив данных.
    size_t typeSize; //!< Размер элемента данных в байтах.
    size_t size; //!< Размер массива данных.
    size_t capacity; //!< Вместимость массива данных.
} vector;

/**
 * @brief Инициализировать вектор.
 * @param vec Указатель на инициализируемый вектор.
 * @param typeSize Размер хранимого в векторе элемента в байтах.
 * @param capacity Начальная вместимость вектора.
 * @retval true - инициализация прошла успешно.
 * @retval false - инициализация прошла неудачно.
 */
bool initVector(vector *vec, size_t typeSize, size_t capacity);

/**
 * @brief Очистить вектор.
 * @param vec Указатель на очищаемый вектор.
 */
void clearVector(vector *vec);

/**
 * @brief Добавить элемент в конец вектора.
 * @param vec Указатель на вектор.
 * @param data Элемент, добавляемый в конец вектора.
 */
void addVectorElement(vector *vec, void *data);

/**
 * @brief Удалить элемент из вектора.
 * @param vec Указатель на вектор.
 * @param idx Индекс удаляемого элемента.
 */
void delVectorElement(vector *vec, size_t idx);

/**
 * @brief Получить элемент вектора.
 * @param vec Указатель на вектор.
 * @param idx Индекс элемента.
 * @retval Элемент вектора, если индекс имеет допустимое значение.
 * @retval NULL, если индекс имеет недопустимое значение.
 */
void *getVectorElement(const vector *vec, size_t idx);

/**
 * @brief Проверить, является ли вектор пустым.
 * @param vec Указатель на вектор.
 * @retval true - вектор является пустым.
 * @retval false - вектор не является пустым.
 */
bool isVectorEmpty(const vector *vec);

/**
 * @brief Получить размер вектора.
 * @param vec Указатель на вектор.
 * @return Размер вектора.
 */
size_t getVectorSize(const vector *vec);

/**
 * @brief Отсортировать вектор.
 * @details Для сортировки используется функция qsort()
 * стандартной библиотеки C.
 * @param vec Указатель на вектор.
 * @param comparator Указатель на функцию сравнения элементов вектора.
 */
void qsortVector(vector *vec, vector_cmp *comparator);

/**
 * @}
 */
