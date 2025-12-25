#include <gtest/gtest.h>
#include "cbt.h"

// Тест начального состояния
TEST(CBTTest, InitialState) {
    CompleteBinaryTree cbt;
    EXPECT_TRUE(cbt.isEmpty());
    EXPECT_EQ(cbt.size(), 0);
}

// Тест вставки и получения элементов
TEST(CBTTest, InsertionAndAccess) {
    CompleteBinaryTree cbt;
    cbt.insert(10);
    cbt.insert(20);
    cbt.insert(30);

    EXPECT_EQ(cbt.size(), 3);
    EXPECT_FALSE(cbt.isEmpty());
    EXPECT_EQ(cbt.getElement(0), 10);
    EXPECT_EQ(cbt.getElement(1), 20);
    EXPECT_EQ(cbt.getElement(2), 30);
}

// Тест навигации по индексам (Родитель/Дети)
TEST(CBTTest, IndexNavigation) {
    CompleteBinaryTree cbt;
    // Заполняем дерево: 0:[10], 1:[20], 2:[30], 3:[40]
    for(int v : {10, 20, 30, 40}) cbt.insert(v);

    // Проверка левого ребенка
    EXPECT_EQ(cbt.getLeftChildIndex(0), 1);
    EXPECT_EQ(cbt.getLeftChildIndex(1), 3);
    EXPECT_EQ(cbt.getLeftChildIndex(2), -1); // Нет ребенка

    // Проверка правого ребенка
    EXPECT_EQ(cbt.getRightChildIndex(0), 2);
    EXPECT_EQ(cbt.getRightChildIndex(1), -1); // Нет ребенка

    // Проверка родителя
    EXPECT_EQ(cbt.getParentIndex(3), 1);
    EXPECT_EQ(cbt.getParentIndex(1), 0);
    EXPECT_EQ(cbt.getParentIndex(0), -1); // Корень
}

// Тест удаления последнего элемента
TEST(CBTTest, RemoveLast) {
    CompleteBinaryTree cbt;
    cbt.insert(100);
    cbt.insert(200);
    
    cbt.removeLast();
    EXPECT_EQ(cbt.size(), 1);
    EXPECT_EQ(cbt.getElement(0), 100);
    
    cbt.removeLast();
    EXPECT_TRUE(cbt.isEmpty());
}

// Тестирование исключений (Exceptions) — важно для высокого покрытия
TEST(CBTTest, ExceptionHandling) {
    CompleteBinaryTree cbt;

    // Ошибка при удалении из пустого дерева
    EXPECT_THROW(cbt.removeLast(), std::out_of_range);

    // Ошибка при обращении к неверному индексу
    cbt.insert(10);
    EXPECT_THROW(cbt.getElement(-1), std::out_of_range);
    EXPECT_THROW(cbt.getElement(5), std::out_of_range);
}

// Тест вывода (для покрытия функции printTree)
TEST(CBTTest, PrintMethod) {
    CompleteBinaryTree cbt;
    cbt.insert(1);
    cbt.insert(2);
    
    // Перехватываем стандартный вывод
    testing::internal::CaptureStdout();
    cbt.printTree();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "1 2 \n");
}