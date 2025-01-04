#include <stdio.h>
#include <stdlib.h>

// Estrutura de um array dinâmico
typedef struct {
    int* data;     // Ponteiro para os elementos do array
    int size;      // Número de elementos no array
    int capacity;  // Capacidade do array
} DynamicArray;

// Função para inicializar o array dinâmico
void init_array(DynamicArray* array) {
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
}

// Função para redimensionar o array dinâmico
void resize_array(DynamicArray* array, int new_capacity) {
    int* new_data = (int*)realloc(array->data, new_capacity * sizeof(int));
    if (!new_data) {
        printf("Erro ao redimensionar o array.\n");
        return;
    }
    array->data = new_data;
    array->capacity = new_capacity;
}

// Função para adicionar um elemento ao final do array
void push_to_array(DynamicArray* array, int value) {
    if (array->size == array->capacity) {
        int new_capacity = (array->capacity == 0) ? 1 : array->capacity * 2;
        resize_array(array, new_capacity);
    }
    array->data[array->size++] = value;
}

// Função para adicionar vários elementos ao array
void push_many_to_array(DynamicArray* array, int values[], int count) {
    for (int i = 0; i < count; i++) {
        push_to_array(array, values[i]);
    }
}

// Função para remover o último elemento do array
int pop_from_array(DynamicArray* array) {
    if (array->size == 0) {
        printf("Erro: Array vazio.\n");
        return -1;  // Indica erro
    }
    return array->data[--array->size];
}

// Função para acessar um elemento por índice
int get_from_array(DynamicArray* array, int index) {
    if (index < 0 || index >= array->size) {
        printf("Erro: Índice fora do intervalo.\n");
        return -1;  // Indica erro
    }
    return array->data[index];
}

// Função para remover um elemento por índice
void remove_from_array(DynamicArray* array, int index) {
    if (index < 0 || index >= array->size) {
        printf("Erro: Índice fora do intervalo.\n");
        return;
    }
    for (int i = index; i < array->size - 1; i++) {
        array->data[i] = array->data[i + 1];
    }
    array->size--;
}

// Função para liberar a memória do array dinâmico
void free_array(DynamicArray* array) {
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
}

// Função para imprimir os elementos do array
void print_array(DynamicArray* array) {
    printf("Array: [ ");
    for (int i = 0; i < array->size; i++) {
        printf("%d ", array->data[i]);
    }
    printf("]\n");
}

// Função para obter o tamanho do array
int len_array(DynamicArray* array) {
    return array->size;
}

// Estrutura de operações para o namespace
typedef struct array_operations {
    void (*init)(DynamicArray*);
    void (*push)(DynamicArray*, int);
    void (*push_many)(DynamicArray*, int[], int);
    int (*pop)(DynamicArray*);
    int (*get)(DynamicArray*, int);
    void (*remove)(DynamicArray*, int);
    void (*print)(DynamicArray*);
    void (*free)(DynamicArray*);
    int (*len)(DynamicArray*);
} DynamicArrayOperations;

// Implementação do namespace
DynamicArrayOperations dynamic_array = {
    .init = init_array,
    .push = push_to_array,
    .push_many = push_many_to_array,
    .pop = pop_from_array,
    .get = get_from_array,
    .remove = remove_from_array,
    .print = print_array,
    .free = free_array,
    .len = len_array,
};

// Função principal para testar o array dinâmico
int main() {
    DynamicArray arr;
    dynamic_array.init(&arr);

    dynamic_array.push(&arr, 10);
    dynamic_array.push(&arr, 20);
    dynamic_array.push(&arr, 30);
    dynamic_array.print(&arr);

    int values[] = {40, 50, 60};
    dynamic_array.push_many(&arr, values, 3);
    dynamic_array.print(&arr);

    printf("Elemento removido (pop): %d\n", dynamic_array.pop(&arr));
    dynamic_array.print(&arr);

    int value = dynamic_array.get(&arr, 1);
    printf("Elemento no índice 1: %d\n", value);

    dynamic_array.remove(&arr, 1);
    dynamic_array.print(&arr);

    printf("Tamanho do array: %d\n", dynamic_array.len(&arr));

    dynamic_array.free(&arr);

    return 0;
}
