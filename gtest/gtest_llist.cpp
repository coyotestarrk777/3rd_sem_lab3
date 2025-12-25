#include <gtest/gtest.h>
#include "LList.h"

class OdSpisTest : public ::testing::Test {
protected:
    OdSpis* head = nullptr;
    OdSpis listManager; // Объект для вызова методов

    void SetUp() override {
        head = nullptr;
    }

    void TearDown() override {
        listManager.cleanupList(head);
    }
};

// --- Тесты добавления ---

TEST_F(OdSpisTest, AddToBeginAndEnd) {
    listManager.AddToBegin(head, "Node1"); // [Node1]
    EXPECT_EQ(head->getName(), "Node1");
    
    listManager.AddToEnd(head, "Node2");   // [Node1, Node2]
    EXPECT_EQ(listManager.SizeList(head), 2);
    EXPECT_EQ(head->getNext()->getName(), "Node2");
}

TEST_F(OdSpisTest, AddChelPosle) {
    listManager.AddToBegin(head, "A");
    OdSpis* a_ptr = listManager.FindElement(head, "A");
    listManager.AddChelPosle(a_ptr, "B"); // A -> B
    
    EXPECT_EQ(a_ptr->getNext()->getName(), "B");
    EXPECT_EQ(listManager.SizeList(head), 2);
}

TEST_F(OdSpisTest, AddChelDo) {
    listManager.AddToBegin(head, "C");
    OdSpis* c_ptr = listManager.FindElement(head, "C");
    
    // Вставка перед головой
    listManager.AddChelDo(head, c_ptr, "A"); // A -> C
    EXPECT_EQ(head->getName(), "A");
    
    // Вставка в середину
    listManager.AddChelDo(head, c_ptr, "B"); // A -> B -> C
    EXPECT_EQ(listManager.SizeList(head), 3);
    EXPECT_EQ(head->getNext()->getName(), "B");

    // Попытка вставки перед несуществующим элементом (покрытие ветки else)
    OdSpis* fake = new OdSpis("Fake", nullptr);
    listManager.AddChelDo(head, fake, "NoWay");
    EXPECT_EQ(listManager.SizeList(head), 3);
    delete fake;
}

// --- Тесты поиска ---

TEST_F(OdSpisTest, SearchMethods) {
    listManager.AddToBegin(head, "Target");
    EXPECT_TRUE(listManager.poisk(head, "Target"));
    EXPECT_FALSE(listManager.poisk(head, "Missing"));
    
    EXPECT_NE(listManager.FindElement(head, "Target"), nullptr);
    EXPECT_EQ(listManager.FindElement(head, "Missing"), nullptr);
}

// --- Тесты удаления ---

TEST_F(OdSpisTest, DeleteToBeginEnd) {
    listManager.AddToBegin(head, "End");
    listManager.AddToBegin(head, "Start"); // Start -> End
    
    listManager.deleteToBegin(head); // End
    EXPECT_EQ(head->getName(), "End");
    EXPECT_EQ(listManager.SizeList(head), 1);
    
    listManager.deleteToEnd(head); // Empty
    EXPECT_EQ(head, nullptr);
    
    // Проверка на пустом списке (защита от краша)
    listManager.deleteToBegin(head);
    listManager.deleteToEnd(head);
}

TEST_F(OdSpisTest, DeletePoZnach) {
    listManager.AddToBegin(head, "3");
    listManager.AddToBegin(head, "2");
    listManager.AddToBegin(head, "1"); // 1 -> 2 -> 3
    
    // Удаление из середины
    listManager.deletePoZnach(head, "2");
    EXPECT_FALSE(listManager.poisk(head, "2"));
    
    // Удаление головы
    listManager.deletePoZnach(head, "1");
    EXPECT_EQ(head->getName(), "3");
    
    // Удаление несуществующего (покрытие ветки else с cout)
    listManager.deletePoZnach(head, "Missing");
}

TEST_F(OdSpisTest, DeleteChelDoPosle) {
    listManager.AddToBegin(head, "D");
    listManager.AddToBegin(head, "C");
    listManager.AddToBegin(head, "B");
    listManager.AddToBegin(head, "A"); // A -> B -> C -> D
    
    OdSpis* c_ptr = listManager.FindElement(head, "C");
    
    // Удалить ПОСЛЕ C (удалит D)
    listManager.deleteChelPosle(c_ptr);
    EXPECT_FALSE(listManager.poisk(head, "D"));
    
    // Удалить ДО C (удалит B)
    listManager.deleteChelDo(head, c_ptr);
    EXPECT_FALSE(listManager.poisk(head, "B"));
    
    // Попытка удалить ДО головы (ничего не должно измениться)
    listManager.deleteChelDo(head, head);
    EXPECT_EQ(listManager.SizeList(head), 2);
}

// --- Утилиты ---

TEST_F(OdSpisTest, CleanupAndPrint) {
    listManager.AddToBegin(head, "Node");
    listManager.print(head); // Просто вызов для покрытия кода печати
    listManager.cleanupList(head);
    EXPECT_EQ(head, nullptr);
}