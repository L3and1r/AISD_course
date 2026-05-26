#pragma once
#include <iostream>

template <typename T>
class binTree;

template <typename T>
class node {
    T value;
    node<T>* right;
    node<T>* left;

    node(const T& value);

    friend class binTree<T>;
};

template <typename T>
class binTree {
private:
    node<T>* root;
    int nodeCount;

    node<T>* copyTree(node<T>* current);
    void clearTree(node<T>* current);
    node<T>* insertNode(node<T>* current, const T& val, bool& inserted);
    node<T>* removeNode(node<T>* current, const T& val, bool& removed);
    node<T>* findMin(node<T>* current);

public:
    binTree();
    binTree(const binTree<T>& other);
    ~binTree();

    void insert(const T& val);
    bool remove(const T& val);
    bool find(const T& val);

    bool isEmpty() const { return root == nullptr; }
    int getSize() const { return nodeCount; }

    void printTree();
};
