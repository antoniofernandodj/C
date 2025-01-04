#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define len(array) (array != NULL ? array->size : 0)  // Tamanho dinâmico

// Definindo um tipo enum para identificar o tipo de dados
typedef enum {
    INT,
    FLOAT,
    STRING,
    CHAR,
    DOUBLE,
    LONG
} DataType;

// Estrutura para armazenar dados genéricos
typedef struct {
    void* data;
    DataType type;
} Data;

// Estrutura para o array genérico dinâmico
typedef struct {
    Data* array;
    size_t size;
    size_t capacity;
} GenericArray;

// Funções para manipulação do array genérico
GenericArray* create_array();
void destroy_array(GenericArray* arr);
void add_element(GenericArray* arr, void* data, DataType type);
void print_array(const GenericArray* arr);
void remove_element(GenericArray* arr, size_t index);
Data get_element(const GenericArray* arr, size_t index);

#endif // DATA_H


// Função para criar um array genérico dinâmico
GenericArray* create_array() {
    GenericArray* arr = (GenericArray*)malloc(sizeof(GenericArray));
    if (!arr) {
        perror("Failed to create array");
        return NULL;
    }
    arr->size = 0;
    arr->capacity = 10;
    arr->array = (Data*)malloc(arr->capacity * sizeof(Data));
    if (!arr->array) {
        free(arr);
        perror("Failed to allocate memory for array data");
        return NULL;
    }
    return arr;
}

// Função para destruir o array e liberar a memória
void destroy_array(GenericArray* arr) {
    if (arr) {
        for (size_t i = 0; i < arr->size; i++) {
            if (arr->array[i].type == STRING) {
                free(arr->array[i].data); // Free string if it's dynamically allocated
            }
        }
        free(arr->array);
        free(arr);
    }
}

// Função para adicionar um elemento no array genérico
void add_element(GenericArray* arr, void* data, DataType type) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->array = (Data*)realloc(arr->array, arr->capacity * sizeof(Data));
        if (!arr->array) {
            perror("Failed to reallocate memory for array");
            return;
        }
    }
    arr->array[arr->size].data = data;
    arr->array[arr->size].type = type;
    arr->size++;
}

// Função para imprimir o array genérico
void print_array(const GenericArray* arr) {
    printf("[ ");
    for (size_t i = 0; i < arr->size; i++) {
        switch (arr->array[i].type) {
            case INT:
                printf("%d", *(int*)arr->array[i].data);
                break;
            case FLOAT:
                printf("%.2f", *(float*)arr->array[i].data);
                break;
            case STRING:
                printf("%s", (char*)arr->array[i].data);
                break;
            case CHAR:
                printf("'%c'", *(char*)arr->array[i].data);
                break;
            case DOUBLE:
                printf("%.2lf", *(double*)arr->array[i].data);
                break;
            case LONG:
                printf("%ld", *(long*)arr->array[i].data);
                break;
        }
        if (i < arr->size - 1) {
            printf(", ");
        }
    }
    printf(" ]\n");
}

// Função para remover um elemento do array genérico por índice
void remove_element(GenericArray* arr, size_t index) {
    if (index >= arr->size) {
        printf("Index out of bounds.\n");
        return;
    }
    
    if (arr->array[index].type == STRING) {
        free(arr->array[index].data);  // Free the string if it's dynamically allocated
    }
    
    // Shift elements to remove the selected index
    for (size_t i = index; i < arr->size - 1; i++) {
        arr->array[i] = arr->array[i + 1];
    }
    
    arr->size--;
}

// Função para acessar um elemento por índice
Data get_element(const GenericArray* arr, size_t index) {
    if (index < arr->size) {
        return arr->array[index];
    } else {
        printf("Index out of bounds.\n");
        Data empty_data = { NULL, -1 };
        return empty_data;
    }
}

void print_element(Data element) {
    if (element.data != NULL) {
        switch (element.type) {
            case INT:
                printf("%d", *(int*)element.data);
                break;
            case FLOAT:
                printf("%.2f", *(float*)element.data);
                break;
            case STRING:
                printf("%s", (char*)element.data);
                break;
            case CHAR:
                printf("'%c'", *(char*)element.data);
                break;
            case DOUBLE:
                printf("%.2lf", *(double*)element.data);
                break;
            case LONG:
                printf("%ld", *(long*)element.data);
                break;
            default:
                printf("Tipo desconhecido");
        }
        printf("\n");
    } else {
        printf("Elemento inválido (NULL).\n");
    }
}

// Estrutura de operações para o namespace
typedef struct {
    GenericArray* (*create)();
    void (*push)(GenericArray*, void*, DataType);
    void (*push_many)(GenericArray*, int[], int);
    int (*pop)(GenericArray*);
    Data (*get)(GenericArray*, int);
    void (*remove)(GenericArray*, int);
    void (*print)(GenericArray*);
    void (*free)(GenericArray*);
    int (*len)(GenericArray*);
} GenericArrayOperations;

// Implementação do namespace
GenericArrayOperations genarray = {
    .create = create_array,
    .push = add_element,
    .get = get_element,
    .remove = remove_element,
    .print = print_array,
    .free = destroy_array,
};


int main() {
    Data element = { &(int){42}, INT };
    print_element(element);

    element = (Data){ &(float){3.14f}, FLOAT };
    print_element(element);

    element = (Data){ "Hello", STRING };
    print_element(element);

    element = (Data){ &(char){'A'}, CHAR };
    print_element(element);

    element = (Data){ &(double){6.28}, DOUBLE };
    print_element(element);

    element = (Data){ &(long){1234567890}, LONG };
    print_element(element);

    // Criando um array genérico dinâmico
    GenericArray* arr = genarray.create();
    
    // Adicionando elementos ao array
    int int_val = 10;
    float float_val = 3.14f;
    char* str_val = strdup("Hello, World!");
    char char_val = 'A';
    double double_val = 6.28;
    long long_val = 1234567890;

    genarray.push(arr, &int_val, INT);
    genarray.push(arr, &float_val, FLOAT);
    genarray.push(arr, str_val, STRING);
    genarray.push(arr, &char_val, CHAR);
    genarray.push(arr, &double_val, DOUBLE);
    genarray.push(arr, &long_val, LONG);

    genarray.print(arr);

    genarray.remove(arr, 2);
    printf("After removing index 2:\n");
    genarray.print(arr);

    element = get_element(arr, 2);
    print_element(element);

    destroy_array(arr);

    return 0;
}
