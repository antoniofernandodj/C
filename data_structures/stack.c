#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
} Node;

typedef struct {
    Node* top;
    int size;
} Stack;

// Inicializa a pilha
void init_stack(Stack* stack) {
    stack->top = NULL;
    stack->size = 0;
}

// Empilha um elemento
void push_to_stack(Stack* stack, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    new_node->value = value;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

// Desempilha um elemento
int pop_from_stack(Stack* stack) {
    if (!stack->top) {
        printf("Erro: Pilha vazia.\n");
        return -1;  // Indica erro
    }
    Node* temp = stack->top;
    int value = temp->value;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    return value;
}

// Consulta o elemento no topo
int peek_stack(Stack* stack) {
    if (!stack->top) {
        printf("Erro: Pilha vazia.\n");
        return -1;  // Indica erro
    }
    return stack->top->value;
}

// Verifica se a pilha está vazia
int is_empty_stack(Stack* stack) {
    return stack->size == 0;
}

// Libera a memória da pilha
void free_stack(Stack* stack) {
    Node* current = stack->top;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    stack->top = NULL;
    stack->size = 0;
}

// Exibe os elementos da pilha
void print_stack(Stack* stack) {
    Node* current = stack->top;
    printf("Pilha (topo -> base): ");
    while (current) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

// Estrutura de operações
typedef struct stack_operations {
    void (*init)(Stack*);
    void (*push)(Stack*, int);
    int (*pop)(Stack*);
    int (*peek)(Stack*);
    int (*is_empty)(Stack*);
    void (*free)(Stack*);
    void (*print)(Stack*);
} StackOperations;

// Funções disponíveis
StackOperations stack = {
    .init = init_stack,
    .push = push_to_stack,
    .pop = pop_from_stack,
    .peek = peek_stack,
    .is_empty = is_empty_stack,
    .free = free_stack,
    .print = print_stack,
};

// Função principal
int main() {
    Stack s;
    stack.init(&s);

    stack.push(&s, 10);
    stack.push(&s, 20);
    stack.push(&s, 30);
    stack.print(&s);

    printf("Topo: %d\n", stack.peek(&s));
    printf("Pop: %d\n", stack.pop(&s));
    stack.print(&s);

    stack.free(&s);
    return 0;
}
