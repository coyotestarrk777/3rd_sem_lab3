#include "cbt.h"
#include <iostream>
#include <stdexcept>

void CompleteBinaryTree::insert(int value) {
    tree.push_back(value);
}

void CompleteBinaryTree::removeLast() {
    if (isEmpty()) throw std::out_of_range("Tree is empty");
    tree.pop_back();
}

int CompleteBinaryTree::getElement(int index) const {
    if (index < 0 || index >= (int)tree.size()) {
        throw std::out_of_range("Index out of bounds");
    }
    return tree[index];
}

int CompleteBinaryTree::getLeftChildIndex(int parentIndex) const {
    int index = 2 * parentIndex + 1;
    return (index < (int)tree.size()) ? index : -1;
}

int CompleteBinaryTree::getRightChildIndex(int parentIndex) const {
    int index = 2 * parentIndex + 2;
    return (index < (int)tree.size()) ? index : -1;
}

int CompleteBinaryTree::getParentIndex(int childIndex) const {
    if (childIndex <= 0) return -1;
    return (childIndex - 1) / 2;
}

int CompleteBinaryTree::size() const {
    return (int)tree.size();
}

bool CompleteBinaryTree::isEmpty() const {
    return tree.empty();
}

void CompleteBinaryTree::printTree() const {
    for (int val : tree) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}