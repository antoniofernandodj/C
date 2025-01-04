#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore AVL
typedef struct avl_node {
    int key;
    struct avl_node* left;
    struct avl_node* right;
    int height;
} AVLNode;

// Função para obter a altura de um nó
int get_height(AVLNode* node) {
    return node ? node->height : 0;
}

// Função para calcular o fator de balanceamento
int get_balance(AVLNode* node) {
    return node ? get_height(node->left) - get_height(node->right) : 0;
}

// Cria um novo nó AVL
AVLNode* create_node(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Altura inicial é 1
    return node;
}

// Rotação simples à direita
AVLNode* rotate_right(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T = x->right;

    x->right = y;
    y->left = T;

    y->height = 1 + (get_height(y->left) > get_height(y->right) ? get_height(y->left) : get_height(y->right));
    x->height = 1 + (get_height(x->left) > get_height(x->right) ? get_height(x->left) : get_height(x->right));

    return x;
}

// Rotação simples à esquerda
AVLNode* rotate_left(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T = y->left;

    y->left = x;
    x->right = T;

    x->height = 1 + (get_height(x->left) > get_height(x->right) ? get_height(x->left) : get_height(x->right));
    y->height = 1 + (get_height(y->left) > get_height(y->right) ? get_height(y->left) : get_height(y->right));

    return y;
}

// Insere um valor na árvore AVL e retorna a nova raiz
AVLNode* insert(AVLNode* node, int key) {
    if (!node) return create_node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Não permite duplicatas

    node->height = 1 + (get_height(node->left) > get_height(node->right) ? get_height(node->left) : get_height(node->right));

    int balance = get_balance(node);

    // Rotação à direita
    if (balance > 1 && key < node->left->key)
        return rotate_right(node);

    // Rotação à esquerda
    if (balance < -1 && key > node->right->key)
        return rotate_left(node);

    // Rotação dupla: esquerda-direita
    if (balance > 1 && key > node->left->key) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    // Rotação dupla: direita-esquerda
    if (balance < -1 && key < node->right->key) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

// Nó com menor valor (usado para remoção)
AVLNode* find_min(AVLNode* node) {
    AVLNode* current = node;
    while (current->left)
        current = current->left;
    return current;
}

// Remove um valor da árvore AVL e retorna a nova raiz
AVLNode* delete(AVLNode* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = delete(root->left, key);
    else if (key > root->key)
        root->right = delete(root->right, key);
    else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            AVLNode* temp = find_min(root->right);
            root->key = temp->key;
            root->right = delete(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + (get_height(root->left) > get_height(root->right) ? get_height(root->left) : get_height(root->right));

    int balance = get_balance(root);

    // Rotação à direita
    if (balance > 1 && get_balance(root->left) >= 0)
        return rotate_right(root);

    // Rotação à esquerda
    if (balance < -1 && get_balance(root->right) <= 0)
        return rotate_left(root);

    // Rotação dupla: esquerda-direita
    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    // Rotação dupla: direita-esquerda
    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

// Exibe a árvore em ordem
void print_in_order(AVLNode* root) {
    if (root) {
        print_in_order(root->left);
        printf("%d ", root->key);
        print_in_order(root->right);
    }
}

// Libera a memória da árvore
void free_tree(AVLNode* root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

// Namespace com operações da árvore AVL
typedef struct avl_operations {
    AVLNode* (*insert)(AVLNode*, int);
    AVLNode* (*delete)(AVLNode*, int);
    void (*print)(AVLNode*);
    void (*free)(AVLNode*);
} AVLOperations;

AVLOperations avl = {
    .insert = insert,
    .delete = delete,
    .print = print_in_order,
    .free = free_tree,
};

// Função principal
int main() {
    AVLNode* root = NULL;

    root = avl.insert(root, 10);
    root = avl.insert(root, 20);
    root = avl.insert(root, 30);
    root = avl.insert(root, 40);
    root = avl.insert(root, 50);
    root = avl.insert(root, 25);

    printf("Árvore AVL em ordem: ");
    avl.print(root);
    printf("\n");

    root = avl.delete(root, 20);
    printf("Árvore AVL após remover 20: ");
    avl.print(root);
    printf("\n");

    avl.free(root);
    return 0;
}
