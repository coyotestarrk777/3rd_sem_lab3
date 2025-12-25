#ifndef COMPLETE_BINARY_TREE_H
#define COMPLETE_BINARY_TREE_H

#include <vector>

class CompleteBinaryTree {
private:
    std::vector<int> tree; 

public:
    // Основные операции
    void insert(int value);
    void removeLast();
    
    // Доступ к данным
    int getElement(int index) const;
    int size() const;
    bool isEmpty() const;

    // Навигация (возвращают индексы)
    int getLeftChildIndex(int parentIndex) const;
    int getRightChildIndex(int parentIndex) const;
    int getParentIndex(int childIndex) const;

    void printTree() const;
};

#endif