#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Estrutura para a Min-Heap e Max-Heap
typedef struct {
    int arr[MAX_SIZE];
    int size;
} Heap;

// Função para trocar dois elementos
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função de "heapify-up" para Min-Heap
void min_heapify_up(Heap *heap, int index) {
    while (index > 0 && heap->arr[index] < heap->arr[(index - 1) / 2]) {
        swap(&heap->arr[index], &heap->arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Função de "heapify-up" para Max-Heap
void max_heapify_up(Heap *heap, int index) {
    while (index > 0 && heap->arr[index] > heap->arr[(index - 1) / 2]) {
        swap(&heap->arr[index], &heap->arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Função para inserir na Min-Heap
void insert_min_heap(Heap *heap, int value) {
    if (heap->size >= MAX_SIZE) {
        printf("Heap is full!\n");
        return;
    }
    heap->arr[heap->size] = value;
    min_heapify_up(heap, heap->size);
    heap->size++;
}

// Função para inserir na Max-Heap
void insert_max_heap(Heap *heap, int value) {
    if (heap->size >= MAX_SIZE) {
        printf("Heap is full!\n");
        return;
    }
    heap->arr[heap->size] = value;
    max_heapify_up(heap, heap->size);
    heap->size++;
}

// Função de "heapify-down" para Min-Heap
void min_heapify_down(Heap *heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < heap->size && heap->arr[left] < heap->arr[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->arr[right] < heap->arr[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&heap->arr[index], &heap->arr[smallest]);
        min_heapify_down(heap, smallest);
    }
}

// Função de "heapify-down" para Max-Heap
void max_heapify_down(Heap *heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if (left < heap->size && heap->arr[left] > heap->arr[largest]) {
        largest = left;
    }
    if (right < heap->size && heap->arr[right] > heap->arr[largest]) {
        largest = right;
    }
    if (largest != index) {
        swap(&heap->arr[index], &heap->arr[largest]);
        max_heapify_down(heap, largest);
    }
}

// Função para remover a raiz da Min-Heap
int remove_min(Heap *heap) {
    if (heap->size == 0) {
        printf("Heap is empty!\n");
        return -1;
    }
    int min = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    min_heapify_down(heap, 0);
    return min;
}

// Função para remover a raiz da Max-Heap
int remove_max(Heap *heap) {
    if (heap->size == 0) {
        printf("Heap is empty!\n");
        return -1;
    }
    int max = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    max_heapify_down(heap, 0);
    return max;
}

// Função para imprimir a Heap
void print_heap(Heap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

int main() {
    Heap min_heap = {{0}, 0};
    Heap max_heap = {{0}, 0};

    insert_min_heap(&min_heap, 10);
    insert_min_heap(&min_heap, 20);
    insert_min_heap(&min_heap, 5);
    insert_min_heap(&min_heap, 30);

    printf("Min-Heap: ");
    print_heap(&min_heap);

    insert_max_heap(&max_heap, 10);
    insert_max_heap(&max_heap, 20);
    insert_max_heap(&max_heap, 5);
    insert_max_heap(&max_heap, 30);

    printf("Max-Heap: ");
    print_heap(&max_heap);

    printf("Removed from Min-Heap: %d\n", remove_min(&min_heap));
    printf("Min-Heap after removal: ");
    print_heap(&min_heap);

    printf("Removed from Max-Heap: %d\n", remove_max(&max_heap));
    printf("Max-Heap after removal: ");
    print_heap(&max_heap);

    return 0;
}
