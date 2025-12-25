#include <gtest/gtest.h>
#include "array.h"

// Тест конструкторов
TEST(ArrayTest, ConstructorTest) {
    Array emptyArr;
    // Проверка размера через метод (размер должен быть 0)
    // Так как RazmerMas выводит в консоль, лучше добавить геттер getSize(), 
    // но в рамках текущего кода проверяем создание.
    
    Array capacityArr(5);
    capacityArr.addMasAtEnd("test");
    // Если добавить геттер, можно проверить size == 1
}

// Тест добавления в конец
TEST(ArrayTest, AddAtEnd) {
    Array arr(2);
    arr.addMasAtEnd("first");
    arr.addMasAtEnd("second");
    
    // Попытка добавить в полный массив (покрытие ветки size >= capacity)
    testing::internal::CaptureStdout();
    arr.addMasAtEnd("third");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Массив заполнен.\n");
}

// Тест добавления по индексу (сдвиг элементов)
TEST(ArrayTest, AddAtIndex) {
    Array arr(5);
    arr.addMasAtEnd("1");
    arr.addMasAtEnd("3");
    
    // Вставляем "2" между "1" и "3"
    arr.addMasAtInd(1, "2");
    
    // Проверяем корректность вставки через поиск
    testing::internal::CaptureStdout();
    arr.poiskMasPoInd(1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "2\n");
}

// Тест ошибок при добавлении по индексу
TEST(ArrayTest, AddAtIndexErrors) {
    Array arr(5);
    
    testing::internal::CaptureStdout();
    arr.addMasAtInd(10, "error"); // Индекс > capacity
    string output1 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output1, "Индекс вне диапазона емкости массива.\n");

    testing::internal::CaptureStdout();
    arr.addMasAtInd(2, "error"); // Индекс > size
    string output2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output2, "Индекс превышает текущий размер массива.\n");
}

// Тест удаления элемента
TEST(ArrayTest, DeleteAtIndex) {
    Array arr(5);
    arr.addMasAtEnd("A");
    arr.addMasAtEnd("B");
    arr.addMasAtEnd("C");
    
    arr.deleteMasPoInd(1); // Удаляем "B"
    
    testing::internal::CaptureStdout();
    arr.poiskMasPoInd(1); // На месте "B" должна быть "C"
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "C\n");
}

// Тест замены и размера
TEST(ArrayTest, ReplaceAndSize) {
    Array arr(5);
    arr.addMasAtEnd("Old");
    arr.ZamenaMas(0, "New");
    
    testing::internal::CaptureStdout();
    arr.poiskMasPoInd(0);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "New\n");
    
    testing::internal::CaptureStdout();
    arr.RazmerMas();
    string sizeOutput = testing::internal::GetCapturedStdout();
    EXPECT_EQ(sizeOutput, "1\n");
}

// Тест чтения пустого массива
TEST(ArrayTest, ReadEmpty) {
    Array arr(5);
    testing::internal::CaptureStdout();
    arr.readMas();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Массив пустой, Ваша честь.\n");
}