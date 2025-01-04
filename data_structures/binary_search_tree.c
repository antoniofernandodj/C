#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Função para criar um novo nó
TreeNode* create_node(int data) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!new_node) {
        printf("Erro ao alocar memória para o nó.\n");
        return NULL;
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Função para inserir um valor na árvore
TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

// Função para buscar um valor na árvore
TreeNode* search(TreeNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search(root->left, data);
    }

    return search(root->right, data);
}

// Função para encontrar o menor valor em uma árvore
TreeNode* find_min(TreeNode* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Função para remover um valor da árvore
TreeNode* delete(TreeNode* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        // Nó encontrado
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // Nó com dois filhos
        TreeNode* temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }

    return root;
}

// Função para exibir a árvore em ordem (in-order traversal)
void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Função para exibir a árvore em pré-ordem (pre-order traversal)
void preorder(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Função para exibir a árvore em pós-ordem (post-order traversal)
void postorder(TreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Função para liberar a memória da árvore
void free_tree(TreeNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

// Função principal para testar a árvore binária de busca
int main() {
    TreeNode* root = NULL;

    // Inserção de valores
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Exibição in-order: ");
    inorder(root);
    printf("\n");

    printf("Exibição pré-ordem: ");
    preorder(root);
    printf("\n");

    printf("Exibição pós-ordem: ");
    postorder(root);
    printf("\n");

    // Busca de um valor
    int value = 40;
    if (search(root, value)) {
        printf("Valor %d encontrado na árvore.\n", value);
    } else {
        printf("Valor %d não encontrado na árvore.\n", value);
    }

    // Remoção de um valor
    printf("Removendo o valor 50...\n");
    root = delete(root, 50);

    printf("Exibição in-order após remoção: ");
    inorder(root);
    printf("\n");

    // Liberação da memória
    free_tree(root);
    return 0;
}
