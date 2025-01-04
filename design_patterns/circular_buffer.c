#include <stdio.h>
#include <stdbool.h>

// Buffer Circular (Circular Buffer)

#define BUFFER_SIZE 5

typedef struct {
    int data[BUFFER_SIZE];
    int head;
    int tail;
    int size;
} CircularBuffer;

bool is_full(CircularBuffer* cb) {
    return cb->size == BUFFER_SIZE;
}

bool is_empty(CircularBuffer* cb) {
    return cb->size == 0;
}

void enqueue(CircularBuffer* cb, int value) {
    if (is_full(cb)) {
        printf("Buffer cheio!\n");
        return;
    }
    cb->data[cb->tail] = value;
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->size++;
}

int dequeue(CircularBuffer* cb) {
    if (is_empty(cb)) {
        printf("Buffer vazio!\n");
        return -1;
    }
    int value = cb->data[cb->head];
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->size--;
    return value;
}

int main() {
    CircularBuffer cb = { .head = 0, .tail = 0, .size = 0 };

    enqueue(&cb, 10);
    enqueue(&cb, 20);
    printf("Dequeued: %d\n", dequeue(&cb));
    printf("Dequeued: %d\n", dequeue(&cb));
    return 0;
}
