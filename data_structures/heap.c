#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // Tamanho máximo do heap

// Estrutura do heap
typedef struct {
    int data[MAX_SIZE];
    int size;
} Heap;

// Função para inicializar o heap
void init_heap(Heap* heap) {
    heap->size = 0;
}

// Função para obter o índice do pai
int parent(int i) {
    return (i - 1) / 2;
}

// Função para obter o índice do filho esquerdo
int left_child(int i) {
    return 2 * i + 1;
}

// Função para obter o índice do filho direito
int right_child(int i) {
    return 2 * i + 2;
}

// Função para trocar dois elementos
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para manter a propriedade do Max-Heap (Heapify para baixo)
void heapify_down(Heap* heap, int i) {
    int largest = i;
    int left = left_child(i);
    int right = right_child(i);

    // Verifica se o filho esquerdo é maior
    if (left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }

    // Verifica se o filho direito é maior
    if (right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }

    // Se o maior não é o nó atual, troca e continua o heapify
    if (largest != i) {
        swap(&heap->data[i], &heap->data[largest]);
        heapify_down(heap, largest);
    }
}

// Função para manter a propriedade do Max-Heap (Heapify para cima)
void heapify_up(Heap* heap, int i) {
    while (i > 0 && heap->data[parent(i)] < heap->data[i]) {
        swap(&heap->data[i], &heap->data[parent(i)]);
        i = parent(i);
    }
}

// Função para inserir um elemento no heap
void insert(Heap* heap, int value) {
    if (heap->size == MAX_SIZE) {
        printf("Heap cheio! Não é possível inserir.\n");
        return;
    }

    heap->data[heap->size] = value;
    heap->size++;
    heapify_up(heap, heap->size - 1);
}

// Função para remover o maior elemento (raiz) do heap
int extract_max(Heap* heap) {
    if (heap->size <= 0) {
        printf("Heap vazio! Não é possível remover.\n");
        return -1;
    }

    int max_value = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);

    return max_value;
}

// Função para obter o maior elemento sem removê-lo
int get_max(Heap* heap) {
    if (heap->size <= 0) {
        printf("Heap vazio!\n");
        return -1;
    }
    return heap->data[0];
}

// Função para imprimir o heap
void print_heap(Heap* heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

// Estrutura de operações
typedef struct heap_operations {
    void (*init)(Heap*);
    void (*insert)(Heap*, int);
    int (*extract_max)(Heap*);
    int (*get_max)(Heap*);
    void (*print)(Heap*);
} HeapOperations;

// Operações disponíveis
HeapOperations heap = {
    .init = init_heap,
    .insert = insert,
    .extract_max = extract_max,
    .get_max = get_max,
    .print = print_heap,
};

// Função principal para testar o heap
int main() {
    Heap h;
    heap.init(&h);

    heap.insert(&h, 10);
    heap.insert(&h, 20);
    heap.insert(&h, 5);
    heap.insert(&h, 30);

    heap.print(&h);

    printf("Maior elemento: %d\n", heap.get_max(&h));

    printf("Removendo maior elemento: %d\n", heap.extract_max(&h));
    heap.print(&h);

    printf("Removendo maior elemento: %d\n", heap.extract_max(&h));
    heap.print(&h);

    return 0;
}
