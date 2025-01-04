#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
    struct node* prev;
} Node;

typedef struct deque {
    Node* front;
    Node* rear;
    int size;
} Deque;

// Inicializa o deque
void init_deque(Deque* deque) {
    deque->front = NULL;
    deque->rear = NULL;
    deque->size = 0;
}

// Insere no início
void push_front(Deque* deque, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = deque->front;
    if (deque->front) {
        deque->front->prev = new_node;
    }
    deque->front = new_node;
    if (!deque->rear) {
        deque->rear = new_node;
    }
    deque->size++;
}

// Insere no final
void push_back(Deque* deque, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = deque->rear;
    if (deque->rear) {
        deque->rear->next = new_node;
    }
    deque->rear = new_node;
    if (!deque->front) {
        deque->front = new_node;
    }
    deque->size++;
}

// Remove do início
int pop_front(Deque* deque) {
    if (!deque->front) {
        printf("Erro: Deque vazio.\n");
        return -1;  // Indica erro
    }
    Node* temp = deque->front;
    int value = temp->value;
    deque->front = deque->front->next;
    if (deque->front) {
        deque->front->prev = NULL;
    } else {
        deque->rear = NULL;
    }
    free(temp);
    deque->size--;
    return value;
}

// Remove do final
int pop_back(Deque* deque) {
    if (!deque->rear) {
        printf("Erro: Deque vazio.\n");
        return -1;  // Indica erro
    }
    Node* temp = deque->rear;
    int value = temp->value;
    deque->rear = deque->rear->prev;
    if (deque->rear) {
        deque->rear->next = NULL;
    } else {
        deque->front = NULL;
    }
    free(temp);
    deque->size--;
    return value;
}

// Consulta o elemento da frente
int peek_front(Deque* deque) {
    if (!deque->front) {
        printf("Erro: Deque vazio.\n");
        return -1;  // Indica erro
    }
    return deque->front->value;
}

// Consulta o elemento de trás
int peek_back(Deque* deque) {
    if (!deque->rear) {
        printf("Erro: Deque vazio.\n");
        return -1;  // Indica erro
    }
    return deque->rear->value;
}

// Libera o deque
void free_deque(Deque* deque) {
    Node* current = deque->front;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    deque->front = deque->rear = NULL;
    deque->size = 0;
}

// Imprime o deque
void print_deque(Deque* deque) {
    Node* current = deque->front;
    printf("Deque (frente -> trás): ");
    while (current) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

// Estrutura de operações
typedef struct deque_operations {
    void (*init)(Deque*);
    void (*push_front)(Deque*, int);
    void (*push_back)(Deque*, int);
    int (*pop_front)(Deque*);
    int (*pop_back)(Deque*);
    int (*peek_front)(Deque*);
    int (*peek_back)(Deque*);
    void (*free)(Deque*);
    void (*print)(Deque*);
} DequeOperations;

// Funções disponíveis
DequeOperations deque = {
    .init = init_deque,
    .push_front = push_front,
    .push_back = push_back,
    .pop_front = pop_front,
    .pop_back = pop_back,
    .peek_front = peek_front,
    .peek_back = peek_back,
    .free = free_deque,
    .print = print_deque,
};

// Função principal
int main() {
    Deque d;
    deque.init(&d);

    deque.push_front(&d, 10);
    deque.push_back(&d, 20);
    deque.push_front(&d, 30);
    deque.print(&d);

    printf("Pop Frente: %d\n", deque.pop_front(&d));
    printf("Pop Trás: %d\n", deque.pop_back(&d));
    deque.print(&d);

    deque.free(&d);
    return 0;
}
