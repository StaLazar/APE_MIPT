#include "vector.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

//! Коэффициент роста вместимости вектора.
#define CAPACITY_GROW_FACTOR 1.5F

/**
 * @brief Изменить вместимость вектора.
 * @details Увеличивает вместимость вектора в CAPACITY_GROW_FACTOR раз
 * и изменяет размер памяти, ранее выделенной под вектор.
 * @param vec Указатель на вектор.
 */
static void resizeVector(vector *vec) {
    vec->capacity = (size_t) ceil(vec->capacity * CAPACITY_GROW_FACTOR);
    vec->data = (void **) realloc(vec->data, vec->capacity * sizeof(void *));
}

bool initVector(vector *vec, const size_t typeSize, const size_t capacity) {
    if ((typeSize == 0U) || (capacity == 0U)) {
        return false;
    }
    vec->data = (void **) malloc(capacity * sizeof(void *));
    if (vec->data == NULL) {
        return false;
    }
    vec->typeSize = typeSize;
    vec->size = 0U;
    vec->capacity = capacity;
    return true;
}

void clearVector(vector *vec) {
    for (size_t i = 0; i < vec->size; ++i) {
        free(vec->data[i]);
        vec->data[i] = NULL;
    }
    vec->size = 0U;
    free(vec->data);
    vec->data = NULL;
}

void addVectorElement(vector *vec, void *data) {
    if (vec->size >= vec->capacity) {
        resizeVector(vec);
    }
    vec->data[vec->size] = (void *) malloc(vec->typeSize);
    if (vec->data[vec->size] == NULL) {
        return;
    }
    memcpy(vec->data[vec->size], data, vec->typeSize);
    vec->size++;
}

void delVectorElement(vector *vec, const size_t idx) {
    if (idx >= vec->size) {
        return;
    }
    free(vec->data[idx]);
    vec->data[idx] = NULL;
    for (size_t i = idx; i < vec->size - 1; ++i) {
        vec->data[i] = vec->data[i + 1];
        if (i == (vec->size - 2)) {
            free(vec->data[i + 1]);
            vec->data[i + 1] = NULL;
        }
    }
    vec->size--;
}

void *getVectorElement(const vector *vec, const size_t idx) {
    if (idx >= vec->size) {
        return NULL;
    }
    return vec->data[idx];
}

bool isVectorEmpty(const vector *vec) {
    return (vec->size == 0U) ? true : false;
}

size_t getVectorSize(const vector *vec) {
    return vec->size;
}

void qsortVector(vector *vec, vector_cmp *comparator) {
    qsort(vec->data, vec->size, sizeof(void *), comparator);
}
