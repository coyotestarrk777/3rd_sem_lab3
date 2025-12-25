#include <gtest/gtest.h>
#include "hash.h"

// Фикстура для тестов, чтобы создавать таблицу перед каждым тестом
class HashTest : public ::testing::Test {
protected:
    DoubleHashTable table;
};

// 1. Тест инициализации и пустого состояния
TEST_F(HashTest, InitialState) {
    EXPECT_EQ(table.elementCount(), 0);
    EXPECT_FALSE(table.containsKey(10));
    EXPECT_FALSE(table.contains(10, "value"));
}

// 2. Тест базовой вставки и поиска
TEST_F(HashTest, BasicInsertAndSearch) {
    EXPECT_TRUE(table.insert(1, "one"));
    EXPECT_TRUE(table.insert(2, "two"));
    
    EXPECT_TRUE(table.containsKey(1));
    EXPECT_TRUE(table.contains(2, "two"));
    EXPECT_EQ(table.elementCount(), 2);
    
    // Попытка вставить дубликат ключа (согласно коду ADD возвращает false)
    EXPECT_FALSE(table.insert(1, "duplicate"));
}

// 3. Тест удаления (SETDEL / remove)
TEST_F(HashTest, RemoveOperation) {
    table.insert(10, "data");
    EXPECT_TRUE(table.remove(10, "data"));
    
    EXPECT_FALSE(table.containsKey(10));
    EXPECT_FALSE(table.contains(10, "data"));
    EXPECT_EQ(table.elementCount(), 0);
    
    // Удаление несуществующего
    EXPECT_FALSE(table.remove(99, "none"));
}

// 4. Тест двойного хеширования и коллизий
// Мы предполагаем, что HASH_SIZE небольшой, чтобы вызвать коллизии 
// или вставляем много элементов.
TEST_F(HashTest, CollisionAndStep) {
    // Вставляем элементы, пока таблица не заполнится или не возникнут коллизии
    for (int i = 0; i < HASH_SIZE; i++) {
        table.insert(i, "val" + std::to_string(i));
    }
    
    EXPECT_EQ(table.elementCount(), HASH_SIZE);
    
    // Проверка поиска после коллизий
    EXPECT_TRUE(table.containsKey(HASH_SIZE - 1));
    
    // Попытка вставки в полную таблицу (должна вернуть false по лимиту attempts)
    EXPECT_FALSE(table.insert(HASH_SIZE + 1, "full"));
}

// 5. Тест метода getAllElements
TEST_F(HashTest, GetAllElements) {
    table.insert(1, "A");
    table.insert(2, "B");
    
    int keys[HASH_SIZE];
    string values[HASH_SIZE];
    int count = 0;
    
    table.getAllElements(keys, values, count);
    
    EXPECT_EQ(count, 2);
    // Проверяем наличие хотя бы одного
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(keys[i] == 1 && values[i] == "A") found = true;
    }
    EXPECT_TRUE(found);
}

// 6. Тест логики "isDeleted" при поиске
TEST_F(HashTest, SearchAfterDeletion) {
    table.insert(1, "A"); // Предположим, index = 5
    table.insert(11, "B"); // Коллизия, index = 5 + step
    
    table.remove(1, "A"); // Помечаем index 5 как isDeleted
    
    // Поиск "B" должен продолжаться через удаленную ячейку
    EXPECT_TRUE(table.containsKey(11));
}