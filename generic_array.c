#include <stdio.h>
#include <stdlib.h>

#define len(array) (sizeof(array) / sizeof(array[0]))  // Apenas funciona com arrays estáticos

typedef enum {
    INT,
    FLOAT,
    STRING,
    CHAR,
    DOUBLE,
    LONG
} DataType;

typedef struct {
    void* data;
    DataType type;
} Data;


void print_array(Data *array, int len) {
    printf("[ ");
    for (int i = 0; i < len; i++) {
        switch (array[i].type) {
            case INT:
                printf("%d", *(int*)array[i].data);
                break;
            case FLOAT:
                printf("%.2f", *(float*)array[i].data);
                break;
            case STRING:
                printf("%s", (char*)array[i].data);
                break;
            case CHAR:
                printf("'%c'", *(char*)array[i].data);
                break;
            case DOUBLE:
                printf("%.2lf", *(double*)array[i].data);
                break;
            case LONG:
                printf("%ld", *(long*)array[i].data);
                break;
        }
        if (i < len - 1) {
            printf(", ");
        }
    }
    printf(" ]\n");
}

int main() {

    Data array[6] = {
        { &(int){10}, INT },
        { &(float){3.14f}, FLOAT },
        { "Hello, World!", STRING },
        { &(char){'A'}, CHAR },
        { &(double){6.28}, DOUBLE },
        { &(long){1234567890}, LONG }
    };

    print_array(array, len(array));

    return 0;
}
