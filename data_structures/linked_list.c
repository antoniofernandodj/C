#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó
typedef struct node {
    struct node* prev;
    struct node* next;
    int value;
} Node;

// Estrutura de uma lista
typedef struct {
    Node* head;  // Ponteiro para o início da lista
    int size;    // Tamanho da lista
} LinkedList;

// Inicializa a lista
void init_list(LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

// Função para adicionar um valor ao final da lista (push_to_list)
void push_to_list(LinkedList* list, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (!list->head) {
        list->head = new_node;  // Lista estava vazia
    } else {
        Node* current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
        new_node->prev = current;
    }
    list->size++;
}

// Função para adicionar vários valores de um array à lista (push_many)
void push_many_to_list(LinkedList* list, int values[], int count) {
    for (int i = 0; i < count; i++) {
        push_to_list(list, values[i]);
    }
}

// Função para remover o último valor da lista (pop)
int pop_from_list(LinkedList* list) {
    if (!list->head) {
        printf("Erro: Lista vazia.\n");
        return -1;  // Retorna -1 para indicar erro
    }

    Node* current = list->head;
    while (current->next) {
        current = current->next;
    }

    int value = current->value;

    if (current->prev) {
        current->prev->next = NULL;  // Atualiza o penúltimo nó
    } else {
        list->head = NULL;  // A lista ficou vazia
    }

    free(current);
    list->size--;

    return value;
}

// Função para encontrar um valor na lista (find)
int find_in_list(LinkedList* list, int value) {
    Node* current = list->head;
    int i = 0;
    while (current) {
        if (current->value == value) {
            return i;  // Retorna o indice do nó encontrado
        }
        current = current->next;
        i++;
    }
    return -1;  // Retorna -1 se não encontrado
}

// Função para encontrar um valor na lista (find)
Node* get_node(LinkedList* list, int value) {
    Node* current = list->head;
    while (current) {
        if (current->value == value) {
            return current;  // Retorna o nó encontrado
        }
        current = current->next;
    }
    return NULL;  // Retorna NULL se não encontrado
}

// Função para remover um valor específico da lista (remove)
int remove_value(LinkedList* list, int value) {
    Node* target = get_node(list, value);
    if (!target ) {
        printf("Valor %d não encontrado.\n", value);
        return 0;  // Indica falha
    }

    if (target->prev) {
        target->prev->next = target->next;
    } else {
        list->head = target->next;  // Atualiza o head se for o primeiro nó
    }

    if (target->next) {
        target->next->prev = target->prev;
    }

    free(target);
    list->size--;

    return 1;  // Indica sucesso
}

// Exibe todos os elementos da lista
void print_list(LinkedList* list) {
    Node* current = list->head;
    printf("Lista: [ ");
    while (current) {
        printf("%d, ", current->value);
        current = current->next;
    }
    printf("]\n");
}

// Libera a memória alocada pela lista
void free_list(LinkedList* list) {
    Node* current = list->head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->size = 0;
}

int len_list(LinkedList* list) {
    return list->size;
}


typedef struct list_operations {
    void (*init)(LinkedList*);
    void (*push)(LinkedList*, int);
    void (*push_many)(LinkedList*, int[], int);
    int (*pop)(LinkedList*);
    int (*find)(LinkedList*, int);
    int (*remove)(LinkedList*, int);
    void (*print)(LinkedList*);
    void (*free)(LinkedList*);
    int (*len)(LinkedList*);
} LinkedListOperations;

// Implementação das funções do namespace
LinkedListOperations list = {
    .push = push_to_list,
    .push_many = push_many_to_list,
    .pop = pop_from_list,
    .find = find_in_list,
    .remove = remove_value,
    .print = print_list,
    .free = free_list,
    .init = init_list,
    .len = len_list,
};


// Função principal
int main() {
    LinkedList l;
    list.init(&l);

    // Adiciona valores à lista
    list.push(&l, 10);
    list.push(&l, 20);
    list.push(&l, 30);
    list.print(&l);

    printf("Tamanho da list: %d\n", list.len(&l));

    // Adiciona vários valores de um array
    int values[] = {40, 50, 60};
    list.push_many(&l, values, 3);
    list.print(&l);

    printf("Tamanho da list: %d\n", list.len(&l));

    // Remove o último elemento
    int popped = pop_from_list(&l);
    printf("Valor removido (pop): %d\n", popped);
    list.print(&l);

    printf("Tamanho da list: %d\n", list.len(&l));

    // Encontra um valor
    int found = list.find(&l, 20);
    if (found != -1) {
        printf("Indice do valor encontrado: %d\n", found);
    } else {
        printf("Valor não encontrado.\n");
    }

    // Remove um valor específico
    int success = list.remove(&l, 10);
    if (success) {
        printf("Valor 10 removido com sucesso.\n");
    } else {
        printf("Falha ao remover valor 10.\n");
    }
    list.print(&l);

    // Libera a memória
    list.free(&l);

    return 0;
}
