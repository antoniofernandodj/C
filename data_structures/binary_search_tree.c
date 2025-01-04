#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Estrutura para agrupar todas as operações da árvore
typedef struct {
    TreeNode* (*create_node)(int data);
    TreeNode* (*insert)(TreeNode* root, int data);
    TreeNode* (*search)(TreeNode* root, int data);
    TreeNode* (*find_min)(TreeNode* root);
    TreeNode* (*delete)(TreeNode* root, int data);
    void (*inorder)(TreeNode* root);
    void (*preorder)(TreeNode* root);
    void (*postorder)(TreeNode* root);
    void (*free_tree)(TreeNode* root);
} TreeOperations;

// Implementações das funções
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

TreeNode* search(TreeNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return search(root->left, data);
    }
    return search(root->right, data);
}

TreeNode* find_min(TreeNode* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

TreeNode* delete(TreeNode* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        TreeNode* temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(TreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void free_tree(TreeNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

// Inicializador da estrutura TreeOperations
TreeOperations tree_ops = {
    .create_node = create_node,
    .insert = insert,
    .search = search,
    .find_min = find_min,
    .delete = delete,
    .inorder = inorder,
    .preorder = preorder,
    .postorder = postorder,
    .free_tree = free_tree
};

// Função principal para testar a árvore binária de busca
int main() {
    TreeNode* root = NULL;

    // Inserção de valores
    root = tree_ops.insert(root, 50);
    root = tree_ops.insert(root, 30);
    root = tree_ops.insert(root, 70);
    root = tree_ops.insert(root, 20);
    root = tree_ops.insert(root, 40);
    root = tree_ops.insert(root, 60);
    root = tree_ops.insert(root, 80);

    printf("Exibição in-order: ");
    tree_ops.inorder(root);
    printf("\n");

    printf("Exibição pré-ordem: ");
    tree_ops.preorder(root);
    printf("\n");

    printf("Exibição pós-ordem: ");
    tree_ops.postorder(root);
    printf("\n");

    // Busca de um valor
    int value = 40;
    if (tree_ops.search(root, value)) {
        printf("Valor %d encontrado na árvore.\n", value);
    } else {
        printf("Valor %d não encontrado na árvore.\n", value);
    }

    // Remoção de um valor
    printf("Removendo o valor 50...\n");
    root = tree_ops.delete(root, 50);

    printf("Exibição in-order após remoção: ");
    tree_ops.inorder(root);
    printf("\n");

    // Liberação da memória
    tree_ops.free_tree(root);
    return 0;
}
