#include <stdio.h>

/**
 * @brief Элемент двоичного дерева.
 */
typedef struct tree {
    int key; //!< Ключ.
    struct tree *left; //!< Левое поддерево.
    struct tree *right; //!< Правое поддерево.
} tree;

/**
 * @brief Распечатать левое поддерево,
 * начиная с наиболее удаленного от корня элемента.
 * @param root Элемент двоичного дерева.
 */
void printLeftBranch(tree *root) {
    if (root == NULL) {
        return;
    }
    if (root->left) {
        printLeftBranch(root->left);
    }
    printf("%d ", root->key);
}

/**
 * @brief Распечатать правое поддерево,
 * начиная с наиболее близкого к корню элемента.
 * @param root Элемент двоичного дерева.
 */
void printRightBranch(tree *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->key);
    if (root->right) {
        printRightBranch(root->right);
    }
}

/**
 * @brief Распечатать вид сверху двоичного дерева поиска.
 * @param root Корневой элемент двоичного дерева поиска.
 */
void btUpView(tree *root) {
    if (root == NULL) {
        return;
    }
    printLeftBranch(root->left);
    printf("%d ", root->key);
    printRightBranch(root->right);
}
