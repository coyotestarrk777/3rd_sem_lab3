#include <gtest/gtest.h>
#include "DList.h" // Убедитесь, что путь к заголовку верный

// Тест конструкторов и базового состояния
TEST(StudentGroupTest, BasicConstructors) {
    StudentGroup emptyGroup;
    EXPECT_TRUE(emptyGroup.isEmpty());
    EXPECT_EQ(emptyGroup.getFirst(), "");

    StudentGroup singleGroup("Alice");
    EXPECT_FALSE(singleGroup.isEmpty());
    EXPECT_EQ(singleGroup.getFirst(), "Alice");
    EXPECT_EQ(singleGroup.getLast(), "Alice");
}

// Тест добавления элементов в начало и конец
TEST(StudentGroupTest, AddStartEnd) {
    StudentGroup group;
    group.addStudentToStart("Bob");      // [Bob]
    group.addStudentToEnd("Charlie");    // [Bob, Charlie]
    group.addStudentToStart("Alice");    // [Alice, Bob, Charlie]

    EXPECT_EQ(group.getFirst(), "Alice");
    EXPECT_EQ(group.getLast(), "Charlie");
    EXPECT_TRUE(group.contains("Bob"));
}

// Тест позиционной вставки (Before/After)
TEST(StudentGroupTest, PositionalInsert) {
    StudentGroup group("Alice");
    group.addStudentToEnd("Charlie");
    
    // Вставка между элементами
    group.addStudentAfter("Alice", "Bob");   // [Alice, Bob, Charlie]
    // Вставка перед головой
    group.addStudentBefore("Alice", "Zero"); // [Zero, Alice, Bob, Charlie]
    // Вставка после хвоста
    group.addStudentAfter("Charlie", "End"); // [Zero, Alice, Bob, Charlie, End]

    EXPECT_EQ(group.getFirst(), "Zero");
    EXPECT_EQ(group.getLast(), "End");
    EXPECT_TRUE(group.contains("Bob"));
    
    // Попытка вставки к несуществующему элементу (не должна менять список)
    group.addStudentAfter("Unknown", "Ghost");
    EXPECT_FALSE(group.contains("Ghost"));
}

// Тест удаления элементов
TEST(StudentGroupTest, DeletionMethods) {
    StudentGroup group;
    group.addStudentToEnd("A");
    group.addStudentToEnd("B");
    group.addStudentToEnd("C");
    group.addStudentToEnd("D"); // [A, B, C, D]

    group.deleteStudentAfter("B");  // Удаляет C -> [A, B, D]
    EXPECT_FALSE(group.contains("C"));

    group.deleteStudentBefore("B"); // Удаляет A -> [B, D]
    EXPECT_EQ(group.getFirst(), "B");

    group.deleteStudentFromEnd();   // [B]
    EXPECT_EQ(group.getLast(), "B");

    group.deleteStudentFromStart(); // Пусто
    EXPECT_TRUE(group.isEmpty());
}

// Тест удаления по значению и специфических случаев
TEST(StudentGroupTest, DeleteByValue) {
    StudentGroup group;
    group.addStudentToEnd("Alice");
    group.addStudentToEnd("Bob");
    group.addStudentToEnd("Charlie");

    group.deleteStudentByValue("Bob"); // Удаление из середины
    EXPECT_FALSE(group.contains("Bob"));

    group.deleteStudentByValue("Alice"); // Удаление головы
    EXPECT_EQ(group.getFirst(), "Charlie");

    group.deleteStudentByValue("Charlie"); // Удаление последнего
    EXPECT_TRUE(group.isEmpty());
    
    // Попытка удаления несуществующего (проверка вывода в консоль/отсутствия краша)
    group.deleteStudentByValue("Missing");
}

// Тест конструктора копирования и оператора присваивания
TEST(StudentGroupTest, CopyAndAssignment) {
    StudentGroup original;
    original.addStudentToEnd("1");
    original.addStudentToEnd("2");

    // Конструктор копирования
    StudentGroup copy(original);
    EXPECT_EQ(copy.getFirst(), "1");
    EXPECT_EQ(copy.getLast(), "2");

    // Оператор присваивания
    StudentGroup assigned;
    assigned.addStudentToEnd("Old");
    assigned = original;
    EXPECT_EQ(assigned.getFirst(), "1");
    EXPECT_FALSE(assigned.contains("Old"));

    // Самоприсваивание
    assigned = assigned;
    EXPECT_EQ(assigned.getFirst(), "1");
}

// Тест печати (чтобы убедиться в отсутствии ошибок при обходе)
TEST(StudentGroupTest, PrintSafety) {
    StudentGroup group;
    group.addStudentToEnd("X");
    group.addStudentToEnd("Y");
    
    // Проверяем, что вызовы не вызывают сегфолтов
    testing::internal::CaptureStdout();
    group.printForward();
    string outputF = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputF.c_str(), "X Y \n");
    testing::internal::CaptureStdout();
    group.printReverse();
    string outputR = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputR.c_str(), "Y X \n");
}