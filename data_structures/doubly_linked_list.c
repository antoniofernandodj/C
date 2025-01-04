#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da lista duplamente encadeada
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Estrutura da lista
typedef struct {
    Node* head;
    Node* tail;
    int size;
} DoublyLinkedList;

// Função para inicializar uma lista
void init_list(DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Função para criar um novo nó
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

// Função para adicionar um nó ao início da lista
void insert_at_head(DoublyLinkedList* list, int data) {
    Node* new_node = create_node(data);

    if (list->head == NULL) {
        list->head = list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }

    list->size++;
}

// Função para adicionar um nó ao final da lista
void insert_at_tail(DoublyLinkedList* list, int data) {
    Node* new_node = create_node(data);

    if (list->tail == NULL) {
        list->head = list->tail = new_node;
    } else {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->size++;
}

// Função para remover um nó do início da lista
void remove_from_head(DoublyLinkedList* list) {
    if (list->head == NULL) {
        printf("A lista está vazia!\n");
        return;
    }

    Node* temp = list->head;
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }

    free(temp);
    list->size--;
}

// Função para remover um nó do final da lista
void remove_from_tail(DoublyLinkedList* list) {
    if (list->tail == NULL) {
        printf("A lista está vazia!\n");
        return;
    }

    Node* temp = list->tail;
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    free(temp);
    list->size--;
}

// Função para exibir os elementos da lista (da cabeça ao final)
void display_forward(DoublyLinkedList* list) {
    Node* current = list->head;
    printf("Lista (head -> tail): ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Função para exibir os elementos da lista (da cauda ao início)
void display_backward(DoublyLinkedList* list) {
    Node* current = list->tail;
    printf("Lista (tail -> head): ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

// Função para limpar toda a lista
void clear_list(DoublyLinkedList* list) {
    while (list->head != NULL) {
        remove_from_head(list);
    }
}

// Estrutura de operações para a lista
typedef struct doubly_linked_list_operations {
    void (*init)(DoublyLinkedList*);
    void (*insert_head)(DoublyLinkedList*, int);
    void (*insert_tail)(DoublyLinkedList*, int);
    void (*remove_head)(DoublyLinkedList*);
    void (*remove_tail)(DoublyLinkedList*);
    void (*display_forward)(DoublyLinkedList*);
    void (*display_backward)(DoublyLinkedList*);
    void (*clear)(DoublyLinkedList*);
} DoublyLinkedListOperations;

// Operações disponíveis
DoublyLinkedListOperations list_ops = {
    .init = init_list,
    .insert_head = insert_at_head,
    .insert_tail = insert_at_tail,
    .remove_head = remove_from_head,
    .remove_tail = remove_from_tail,
    .display_forward = display_forward,
    .display_backward = display_backward,
    .clear = clear_list,
};

// Função principal para testar a lista
int main() {
    DoublyLinkedList list;
    list_ops.init(&list);

    list_ops.insert_head(&list, 10);
    list_ops.insert_head(&list, 20);
    list_ops.insert_tail(&list, 30);
    list_ops.insert_tail(&list, 40);

    list_ops.display_forward(&list);
    list_ops.display_backward(&list);

    printf("Removendo da cabeça...\n");
    list_ops.remove_head(&list);
    list_ops.display_forward(&list);

    printf("Removendo da cauda...\n");
    list_ops.remove_tail(&list);
    list_ops.display_forward(&list);

    printf("Limpando a lista...\n");
    list_ops.clear(&list);
    list_ops.display_forward(&list);

    return 0;
}
