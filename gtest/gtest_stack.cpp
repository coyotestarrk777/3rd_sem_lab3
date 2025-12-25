#include <gtest/gtest.h>
#include "stack.h"

TEST(StackTest, FullCoverage) {
    Stack* s = nullptr;

    // 1. Тест на пустой стек (покрывает ветки if (ptr == nullptr))
    Stack::SDELETE(s); 
    EXPECT_EQ(Stack::SPOP(s), "");
    EXPECT_EQ(Stack::countStack(s), 0);
    Stack::readStack(s);

    // 2. Стандартная работа
    Stack::SPUSH(s, "A");
    Stack::SPUSH(s, "B");
    EXPECT_EQ(Stack::countStack(s), 2);
    
    // 3. Очистка (покрывает цикл удаления)
    Stack::clearStack(s);
    EXPECT_EQ(s, nullptr);
}