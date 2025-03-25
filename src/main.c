#include <complex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int32_t length;
    int32_t capacity;
    int32_t* items;
} Int32Array;


Int32Array Int32Array__init(int32_t capacity) {
    Int32Array a;
    a.length = 0;
    a.capacity = capacity;
    a.items = malloc(capacity * sizeof(int32_t));
    if (!a.items) {
        printf("Erro ao alocar memória!\n");
        exit(EXIT_FAILURE);
    }
    return a;
}

void Int32Array__insert(Int32Array* array, int32_t value) {
    if (array->length < array->capacity) {
        array->items[array->length] = value;
        array->length++;
    } else {
        printf("Erro: capacidade máxima atingida!\n");
    }
}

void Int32Array__insert_with_index(Int32Array* array, int32_t value, int32_t index) {
    if (index >= 0 && index < array->length) {
        array->items[index] = value;
    }
}

int32_t Int32Array__get(Int32Array array, int32_t index) {
    if (index >= 0 && index < array.length) {
        return array.items[index];
    };

    return 0;
}

void Int32Array__free(Int32Array *array) {
    free(array->items);
}

int main() {
    
    Int32Array array = Int32Array__init(100);

    Int32Array__insert(&array, 1);
    Int32Array__insert(&array, 2);
    Int32Array__insert(&array, 3);
    Int32Array__insert(&array, 4);
    Int32Array__insert(&array, 5);

    int32_t i = 0;
    while (i < array.length) {
        printf("array[%d] = %d\n", i, Int32Array__get(array, i));
        i++;
    }

    Int32Array__free(&array);

    return 0;
}
