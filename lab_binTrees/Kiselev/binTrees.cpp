#include "binTrees.h"

// ============= node =============
template <typename T>
node<T>::node(const T& val)
    : value(val), right(nullptr), left(nullptr) {
}

// ============= binTree =============

template <typename T>
binTree<T>::binTree() {
    root = nullptr;
    nodeCount = 0;
}

template <typename T>
node<T>* copyTree(node<T>* current) {
    if (current == nullptr) {
        return nullptr;
    }
    node<T>* newNode = new node<T>(current->value);
    newNode->left = copyTree(current->left);
    newNode->right = copyTree(current->right);
    return newNode;
}

template <typename T>
binTree<T>::binTree(const binTree<T>& other) {
    root = copyTree(other.root);
    nodeCount = other.nodeCount;
}

template <typename T>
void clearTree(node<T>* current) {
    if (current != nullptr) {
        clearTree(current->left);
        clearTree(current->right);
        delete current;
    }
}

template <typename T>
binTree<T>::~binTree() {
    clearTree(root);
}

template <typename T>
node<T>* insertNode(node<T>* current, const T& val, bool& inserted) {
    if (current == nullptr) {
        inserted = true;
        return new node<T>(val);
    }
    
    if (val < current->value) {
        current->left = insertNode(current->left, val, inserted);
    } else if (val > current->value) {
        current->right = insertNode(current->right, val, inserted);
    } else {
        inserted = false;
    }
    return current;
}

template <typename T>
void binTree<T>::insert(const T& val) {
    bool inserted = false;
    root = insertNode(root, val, inserted);
    if (inserted) {
        nodeCount++;
    }
}

template <typename T>
node<T>* findMin(node<T>* current) {
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

template <typename T>
node<T>* removeNode(node<T>* current, const T& val, bool& removed) {
    if (current == nullptr) {
        removed = false;
        return nullptr;
    }

    if (val < current->value) {
        current->left = removeNode(current->left, val, removed);
    } else if (val > current->value) {
        current->right = removeNode(current->right, val, removed);
    } else {

        removed = true;

        if (current->left == nullptr) {
            node<T>* temp = current->right;
            delete current;
            return temp;
        } else if (current->right == nullptr) {
            node<T>* temp = current->left;
            delete current;
            return temp;
        }

        node<T>* temp = findMin(current->right);
        current->value = temp->value;

        bool dummy;
        current->right = removeNode(current->right, temp->value, dummy);
    }
    return current;
}

template <typename T>
bool binTree<T>::remove(const T& val) {
    bool removed = false;
    root = removeNode(root, val, removed);
    if (removed) {
        nodeCount--;
    }
    return removed;
}

template <typename T>
bool binTree<T>::find(const T& val) {
    node<T>* current = root;
    while (current != nullptr) {
        if (val == current->value) {
            return true;
        } else if (val < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}