#include "binTrees.h"
#include <queue>
#include <stack>
#include <vector>
#include <utility>

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
node<T>* binTree<T>::copyTree(node<T>* current) {
    if (current == nullptr) {
        return nullptr;
    }

    std::stack<std::pair<node<T>*, node<T>**> > stack;
    node<T>* newRoot = new node<T>(current->value);
    stack.push(std::make_pair(current, &newRoot));

    while (!stack.empty()) {
        std::pair<node<T>*, node<T>**> top = stack.top();
        stack.pop();

        node<T>* origNode = top.first;
        node<T>* newNode = *(top.second);

        if (origNode->left != nullptr) {
            node<T>* newLeft = new node<T>(origNode->left->value);
            newNode->left = newLeft;
            stack.push(std::make_pair(origNode->left, &newNode->left));
        }

        if (origNode->right != nullptr) {
            node<T>* newRight = new node<T>(origNode->right->value);
            newNode->right = newRight;
            stack.push(std::make_pair(origNode->right, &newNode->right));
        }
    }

    return newRoot;
}

template <typename T>
binTree<T>::binTree(const binTree<T>& other) {
    root = copyTree(other.root);
    nodeCount = other.nodeCount;
}

template <typename T>
void binTree<T>::clearTree(node<T>* current) {
    if (current == nullptr) return;

    std::stack<node<T>*> stack;
    stack.push(current);

    while (!stack.empty()) {
        node<T>* node = stack.top();
        stack.pop();

        if (node->left != nullptr) {
            stack.push(node->left);
        }
        if (node->right != nullptr) {
            stack.push(node->right);
        }

        delete node;
    }
}

template <typename T>
binTree<T>::~binTree() {
    clearTree(root);
}

template <typename T>
node<T>* binTree<T>::insertNode(node<T>* current, const T& val, bool& inserted) {
    if (current == nullptr) {
        inserted = true;
        return new node<T>(val);
    }

    if (val < current->value) {
        current->left = insertNode(current->left, val, inserted);
    }
    else if (val > current->value) {
        current->right = insertNode(current->right, val, inserted);
    }
    else {
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
node<T>* binTree<T>::findMin(node<T>* current) {
    while (current != nullptr && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

template <typename T>
node<T>* binTree<T>::removeNode(node<T>* current, const T& val, bool& removed) {
    if (current == nullptr) {
        removed = false;
        return nullptr;
    }

    if (val < current->value) {
        current->left = removeNode(current->left, val, removed);
    }
    else if (val > current->value) {
        current->right = removeNode(current->right, val, removed);
    }
    else {
        removed = true;

        if (current->left == nullptr) {
            node<T>* temp = current->right;
            delete current;
            return temp;
        }
        else if (current->right == nullptr) {
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
        }
        else if (val < current->value) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return false;
}

template <typename T>
void binTree<T>::printTree() {
    if (root == nullptr) {
        std::cout << "Дерево пусто" << std::endl;
        return;
    }

    std::cout << "Бинарное дерево (уровневый обход):" << std::endl;
    std::queue<node<T>*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = (int)q.size();
        for (int i = 0; i < levelSize; i++) {
            node<T>* current = q.front();
            q.pop();

            if (current != nullptr) {
                std::cout << current->value << " ";
                q.push(current->left);
                q.push(current->right);
            }
            else {
                std::cout << "null ";
            }
        }
        std::cout << std::endl;
    }
}

template class binTree<int>;
