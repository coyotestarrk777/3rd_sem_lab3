#include <gtest/gtest.h>
#include "queue.h"

TEST(QueueTest, FullCoverage) {
    Queue *h = nullptr, *t = nullptr;

    // 1. Пустая очередь
    Queue::QDELETE(h, t);
    EXPECT_EQ(Queue::QPOP(h, t), "Очередь пуста");
    Queue::readQueue(h);

    // 2. Вставка и удаление последнего (покрывает обнуление tail)
    Queue::QPUSH(h, t, "first");
    EXPECT_EQ(Queue::countQueue(h), 1);
    EXPECT_EQ(Queue::QPOP(h, t), "first");
    EXPECT_EQ(h, nullptr);
    EXPECT_EQ(t, nullptr); // Проверка, что tail тоже обнулился
}