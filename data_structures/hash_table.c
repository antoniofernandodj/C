#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10 // Tamanho da tabela hash

// Estrutura do nó na lista encadeada para colisões
typedef struct node {
    char* key;
    int value;
    struct node* next;
} Node;

// Estrutura da tabela de hash
typedef struct {
    Node* buckets[TABLE_SIZE];
} HashTable;

// Função hash simples
unsigned int hash_function(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key++;
    }
    return hash % TABLE_SIZE;
}

// Inicializa a tabela de hash
void init_hash_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
}

// Insere um par chave-valor na tabela
void hash_table_insert(HashTable* table, const char* key, int value) {
    unsigned int index = hash_function(key);
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

// Procura um valor pela chave
int hash_table_search(HashTable* table, const char* key, int* found) {
    unsigned int index = hash_function(key);
    Node* current = table->buckets[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            *found = 1;
            return current->value;
        }
        current = current->next;
    }
    *found = 0;
    return -1; // Indica que não foi encontrado
}

// Remove uma chave da tabela de hash
void hash_table_remove(HashTable* table, const char* key) {
    unsigned int index = hash_function(key);
    Node* current = table->buckets[index];
    Node* prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                table->buckets[index] = current->next;
            }
            free(current->key);
            free(current);
            printf("Chave '%s' removida.\n", key);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Chave '%s' não encontrada.\n", key);
}

// Imprime a tabela de hash
void hash_table_print(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        Node* current = table->buckets[i];
        while (current) {
            printf("[%s: %d] -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Libera a memória da tabela de hash
void free_hash_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = table->buckets[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
        table->buckets[i] = NULL;
    }
}

// Estrutura de operações
typedef struct {
    void (*init)(HashTable*);
    void (*insert)(HashTable*, const char*, int);
    int (*search)(HashTable*, const char*, int*);
    void (*remove)(HashTable*, const char*);
    void (*print)(HashTable*);
    void (*free)(HashTable*);
} HashTableOperations;

// Operações disponíveis
HashTableOperations hashtable = {
    .init = init_hash_table,
    .insert = hash_table_insert,
    .search = hash_table_search,
    .remove = hash_table_remove,
    .print = hash_table_print,
    .free = free_hash_table,
};

// Função principal
int main() {
    HashTable table;
    hashtable.init(&table);

    hashtable.insert(&table, "apple", 50);
    hashtable.insert(&table, "banana", 30);
    hashtable.insert(&table, "grape", 20);
    hashtable.insert(&table, "pear", 15);

    hashtable.print(&table);

    int found;
    int value = hashtable.search(&table, "banana", &found);
    if (found) {
        printf("Encontrado: banana -> %d\n", value);
    } else {
        printf("Chave 'banana' não encontrada.\n");
    }

    hashtable.remove(&table, "grape");
    hashtable.print(&table);

    hashtable.free(&table);
    return 0;
}
