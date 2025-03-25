#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int length;
    int capacity;
} ArrayADT;

ArrayADT* ArrayADT_init(int capacity) {
    ArrayADT *array = malloc(sizeof(ArrayADT));
    if (!array) {
        return NULL;
    }
    array->data = malloc(capacity * sizeof(int));
    array->length = 0;
    array->capacity = capacity;
    return array;
}

void ArrayADT_display(ArrayADT* array) {
    printf("[");
    for (int i = 0; i < array->length; i++) {
        printf("%d", array->data[i]);
        if (i < array->length -1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void ArrayADT_free(ArrayADT* array) {
    if (array) {
        free(array->data);
        free(array);
    }
}


int main(int argc, char **argv) {

    ArrayADT *array = ArrayADT_init(10);
    array->data[0] = 1;
    array->data[1] = 2;
    array->data[2] = 3;
    array->data[3] = 4;
    array->data[4] = 5;
    array->length = 5;

    ArrayADT_display(array);

    ArrayADT_free(array);

    return 0;
}
