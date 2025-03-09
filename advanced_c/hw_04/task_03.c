#include <stdio.h>

/**
 * @brief Элемент двоичного дерева.
 */
typedef struct tree {
    int key; //!< Ключ.
    struct tree *left; //!< Левое поддерево.
    struct tree *right; //!< Правое поддерево.
    struct tree *parent; //!< Родительский элемент.
} tree;

/**
 * @brief Найти по ключу элемент двоичного дерева.
 * @param root Элемент двоичного дерева.
 * @param key Ключ, по которому осуществляется поиск.
 * @return Искомый элемент, если он найден, иначе - NULL.
 */
tree *findNode(tree *root, int key) {
    if (root == NULL) {
        return NULL;
    }
    if (key == root->key) {
        return root;
    }
    if (key < root->key) {
        return findNode(root->left, key);
    }
    if (key > root->key) {
        return findNode(root->right, key);
    }
    return NULL;
}

/**
 * @brief Найти по ключу соседний элемент в двоичном дереве поиска.
 * @param root Элемент двоичного дерева поиска.
 * @param key Ключ, по которому осуществляется поиск.
 * @return Искомый элемент, если он найден, иначе - NULL.
 */
tree *findBrother(tree *root, int key) {
    if (root == NULL) {
        return NULL;
    }
    tree *keyNode = findNode(root, key);
    if (keyNode == NULL) {
        return NULL;
    }
    tree *parentNode = keyNode->parent;
    if (parentNode == NULL) {
        return NULL;
    }
    if (parentNode->left && (parentNode->left != keyNode)) {
        return parentNode->left;
    }
    if (parentNode->right && (parentNode->right != keyNode)) {
        return parentNode->right;
    }
    return NULL;
}
