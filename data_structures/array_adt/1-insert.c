#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int *data;
    int capacity;
    int length;
} ArrayADT;

ArrayADT* ArrayADT_init(int capacity) {
    ArrayADT* array = malloc(sizeof(ArrayADT));
    array->data = malloc(sizeof(int) * capacity);
    array->capacity = capacity;
    array->length = 0;
    return array;
}

void ArrayADT_display(ArrayADT* array) {
    printf("[");
    for (int i = 0; i < array->length; i++) {
        printf("%d", array->data[i]);
        if (i + 1 < array->length) {
            printf(", ");
        }
    }
    printf("]\n");
}

void ArrayADT_push(ArrayADT* array, int element) {
    if (!(array->length < array->capacity)) {
        return;
    }

    array->data[array->length] = element;
    array->length++;
}

void ArrayADT_free(ArrayADT* array) {
    free(array->data);
    free(array);
}

void ArrayADT_insert(ArrayADT* array, int index, int element) {

    if (index >= array->length) {
        array->data[array->length] = element;
        array->length++;
        return;
    }

    for (int i = array->length; i > index; i--) {
        array->data[i] = array->data[i - 1];
    }

    array->data[index] = element;
    array->length++;

}

int main(int argc, char **argv) {

    ArrayADT* array = ArrayADT_init(100);

    for (int i = 1; i < 30; i++) {
        ArrayADT_push(array, i);
    }

    ArrayADT_display(array);

    ArrayADT_insert(array, 3, 20);

    ArrayADT_display(array);

    ArrayADT_free(array);

    return 0;
}
