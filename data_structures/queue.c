#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node* next;
    int value;
} Node;

typedef struct queue {
    Node* front;
    Node* rear;
    int size;
} Queue;

void init_queue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

void enqueue(Queue* queue, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    new_node->value = value;
    new_node->next = NULL;
    if (!queue->rear) {
        queue->front = queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
    queue->size++;
}

int dequeue(Queue* queue) {
    if (!queue->front) {
        printf("Erro: Fila vazia.\n");
        return -1;  // Indica erro
    }
    Node* temp = queue->front;
    int value = temp->value;
    queue->front = queue->front->next;
    if (!queue->front) {
        queue->rear = NULL;
    }
    free(temp);
    queue->size--;
    return value;
}

int peek(Queue* queue) {
    if (!queue->front) {
        printf("Erro: Fila vazia.\n");
        return -1;  // Indica erro
    }
    return queue->front->value;
}

int queue_size(Queue* queue) {
    return queue->size;
}

int is_empty_queue(Queue* queue) {
    return queue->size == 0;
}

void free_queue(Queue* queue) {
    Node* current = queue->front;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    queue->front = queue->rear = NULL;
    queue->size = 0;
}

void print_queue(Queue* queue) {
    Node* current = queue->front;
    printf("Fila (frente -> trás): ");
    while (current) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

typedef struct {
    void (*init)(Queue*);
    void (*enqueue)(Queue*, int);
    int (*dequeue)(Queue*);
    int (*peek)(Queue*);
    int (*is_empty)(Queue*);
    void (*free)(Queue*);
    void (*print)(Queue*);
} QueueOperations;

QueueOperations queue = {
    .init = init_queue,
    .enqueue = enqueue,
    .dequeue = dequeue,
    .peek = peek,
    .is_empty = is_empty_queue,
    .free = free_queue,
    .print = print_queue,
};

int main() {
    Queue q;
    queue.init(&q);

    queue.enqueue(&q, 10);
    queue.enqueue(&q, 20);
    queue.enqueue(&q, 30);
    queue.print(&q);

    printf("Frente: %d\n", queue.peek(&q));
    printf("Dequeue: %d\n", queue.dequeue(&q));
    queue.print(&q);

    queue.free(&q);
    return 0;
}
