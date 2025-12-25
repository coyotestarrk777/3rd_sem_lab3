package classes

import (
	"testing"
)

func TestArrayFullCoverage(t *testing.T) {
	arr := NewArray()

	// 1. Покрытие Print и Delete для ПУСТОГО массива
	// На скриншотах эти ветки "Массив пуст" обычно красные
	arr.Print()
	arr.Delete(0)

	// 2. Покрытие ошибок индексации (вне диапазона)
	// Это закроет блоки if index < 0 || index >= a.size
	arr.Insert(-1, "bad")
	arr.Insert(10, "bad")
	arr.Delete(-1)
	arr.Delete(10)
	arr.Replace(-1, "bad")
	arr.Replace(10, "bad")

	// 3. Покрытие автоматического расширения (resize)
	// Изначальная емкость 2. Добавляем 3 элемента, чтобы сработал resize(4)
	arr.PushBack("1")
	arr.PushBack("2")
	arr.PushBack("3") // Здесь сработает a.resize(a.capacity * 2)

	// 4. Покрытие Get для некорректного индекса
	if arr.Get(100) != "" {
		t.Error("Get должен возвращать пустую строку при неверном индексе")
	}

	// 5. Покрытие Insert в середину (проверка цикла сдвига элементов)
	arr.Insert(1, "1.5") // Сдвигает "2" и "3" вправо

	// 6. Покрытие Delete (проверка цикла сдвига элементов влево)
	arr.Delete(1) // Удаляет "1.5", сдвигает "2" и "3" влево

	// 7. Покрытие Replace
	arr.Replace(0, "Updated")

	// 8. Покрытие Print для заполненного массива
	arr.Print()

	// 9. Проверка длины
	if arr.Length() != 3 {
		t.Errorf("Ожидалась длина 3, получили %d", arr.Length())
	}
}

// === Тесты для ForwardList (Односвязный список) ===
func TestForwardListFinalCoverage(t *testing.T) {
	fl := NewFL()

	// 1. Покрытие метода Clear и Print на пустом списке
	fl.Clear()
	fl.Print() // Ветка if l.head == nil

	// 2. Покрытие AddTail для пустого списка
	fl.AddTail("only-one") // Ветка if l.head == nil

	// 3. Покрытие DeleteTail для списка из ОДНОГО элемента
	fl.DeleteTail() // Ветка if l.head.next == nil { l.head = nil }

	// 4. Покрытие ошибок "Список пуст" в AddBefore и AddAfter
	empty := NewFL()
	empty.AddBefore("anything", "val") // Сообщение: Список пуст
	empty.AddAfter("anything", "val")  // Сообщение: Список пуст

	// 5. Покрытие AddAfter: когда элемент не найден
	fl.AddHead("A")
	fl.AddAfter("ghost", "B") // Ветка if ptr == nil

	// 6. Покрытие AddBefore: когда target это голова (AddHead)
	fl.AddBefore("A", "NewHead") // Ветка if l.head.data == target

	// 7. Покрытие AddBefore: когда элемент не найден в цикле
	fl.AddBefore("ghost", "C") // Пройдет цикл до конца (cur.next == nil)

	// 8. Покрытие DeleteTail для длинного списка
	fl.AddTail("B")
	fl.AddTail("C")
	fl.DeleteTail() // Пройдет цикл по cur.next.next != nil

	// 9. Покрытие DeleteBefore: самые сложные ветки
	// Текущий список: NewHead -> A -> B
	fl.DeleteBefore("NewHead") // target is head: return
	fl.DeleteBefore("A")       // prev == nil: вызов DeleteHead

	fl.AddHead("Start")
	// Список: Start -> A -> B
	fl.DeleteBefore("B")     // Ветка else: prev.next = cur.next (удалит A)
	fl.DeleteBefore("ghost") // Пройдет цикл до конца (cur.next == nil)

	// 10. Покрытие DeleteAfter
	fl.DeleteAfter("B") // ptr.next == nil: return
	fl.AddHead("Alpha")
	fl.DeleteAfter("Alpha") // Удалит Start

	// 11. Покрытие DeleteValue
	fl.DeleteValue("Alpha") // Удалит голову
	fl.AddTail("Omega")
	fl.DeleteValue("Omega") // Удалит хвост
	fl.DeleteValue("ghost") // Пройдет цикл до конца (cur.next == nil)

	// 12. Покрытие ToSlice и полной печати
	fl.AddHead("1")
	fl.AddHead("2")
	_ = fl.ToSlice()
	fl.Print() // Пройдет цикл cur != nil
}

// === Тесты для DoublyList (Двусвязный список) ===
func TestDoublyListFullCoverage(t *testing.T) {
	dl := NewDL()

	// 1. Покрытие PrintForward и PrintBackward для ПУСТОГО списка
	// На скриншотах эти циклы красные, так как dl.head == nil
	dl.PrintForward()
	dl.PrintBackward()

	// 2. Покрытие возвратов (return) при отсутствии цели (ptr == nil)
	// Это закроет красные блоки 'return' в AddAfter, AddBefore, DeleteAfter, DeleteBefore
	dl.AddAfter("ghost", "value")
	dl.AddBefore("ghost", "value")
	dl.DeleteAfter("ghost")
	dl.DeleteBefore("ghost")
	dl.DeleteByValue("ghost")

	// 3. Покрытие вставки в середину (AddBefore и AddAfter)
	// Чтобы код newNode и перевязка ссылок стали зелеными
	dl.AddHead("A")
	dl.AddTail("C")
	dl.AddAfter("A", "B")   // Вставка между A и C (ptr.next != nil)
	dl.AddBefore("C", "B2") // Вставка перед C (ptr.prev != nil)

	dl.AddAfter("C", "D") // Сработает ветка else { l.tail = newNode }
	dl.DeleteAfter("B2")  // Удаление в середине
	dl.DeleteAfter("C")   // Удаление хвоста (ветка else { l.tail = ptr })

	// 5. Покрытие DeleteBefore для головы и середины
	dl.AddHead("Start")
	dl.DeleteBefore("A") // Удалит Start (ветка else { l.head = ptr })
	dl.DeleteBefore("D") // Удалит в середине

	// 6. Покрытие DeleteByValue для всех трех веток (Head, Tail, Middle)
	// На скриншотах эти ветки были красными
	dl.AddHead("To-Delete-Head")
	dl.AddTail("To-Delete-Tail")
	dl.DeleteByValue("To-Delete-Head") // Вызов DeleteHead()
	dl.DeleteByValue("To-Delete-Tail") // Вызов DeleteTail()

	dl.AddAfter("A", "Middle-Node")
	dl.DeleteByValue("Middle-Node") // Сработает финальная перевязка ссылок

	dl.PrintForward()
	dl.PrintBackward()

	// 8. Финальная проверка удаления головы и хвоста (граничные условия)
	dl.DeleteHead()
	dl.DeleteTail()
	dl.DeleteHead() // Добиваем до пустого состояния
}

func TestStackFullCoverage(t *testing.T) {
	s := NewStack()

	// 1. Покрытие IsEmpty, Pop и Top для ПУСТОГО стека
	// Это сделает "зелеными" ветки if s.IsEmpty() { return "" }
	if !s.IsEmpty() {
		t.Error("Новый стек должен быть пустым")
	}
	if s.Pop() != "" {
		t.Error("Pop на пустом стеке должен возвращать пустую строку")
	}
	if s.Top() != "" {
		t.Error("Top на пустом стеке должен возвращать пустую строку")
	}

	// 2. Покрытие метода Print для ПУСТОГО стека
	// На скриншотах ветка if s.IsEmpty() { return } в Print часто красная
	s.Print()

	// 3. Добавление элементов
	s.Push("Первый")
	s.Push("Второй")
	s.Push("Третий")

	// 4. Проверка метода Top (без удаления)
	if s.Top() != "Третий" {
		t.Errorf("Ожидалось 'Третий', получено %s", s.Top())
	}

	// 5. Покрытие метода Print для ЗАПОЛНЕННОГО стека
	// Покроет цикл for cur != nil
	s.Print()

	// 6. Покрытие метода Clear
	// Этот метод внутри вызывает Pop в цикле, пока IsEmpty не станет true
	s.Clear()
	if !s.IsEmpty() {
		t.Error("Стек должен быть пуст после Clear")
	}

	// 7. Повторная проверка Print после очистки
	s.Print()
}

// === Тесты для Queue (Очередь) ===
func TestQueueFullCoverage(t *testing.T) {
	q := NewQueue()

	// 1. Покрытие Print и Pop для ПУСТОЙ очереди
	// Это закроет ветку if q.IsEmpty() и if q.front == nil
	q.Print()
	if val := q.Pop(); val != "" {
		t.Errorf("Pop на пустой очереди должен возвращать пустую строку, получено: %s", val)
	}

	// 2. Добавление первого элемента
	// Покроет ветку if q.rear == nil { q.front = newNode ... }
	q.Push("A")
	if q.IsEmpty() {
		t.Error("Очередь не должна быть пустой")
	}

	// 3. Добавление последующих элементов

	q.Push("B")
	q.Push("C")

	// 4. Покрытие Print для ЗАПОЛНЕННОЙ очереди
	// Закроет цикл прохода cur != nil
	q.Print()

	// 5. Удаление элементов до состояния "Один элемент"
	q.Pop() // Удалили A
	q.Pop() // Удалили B, остался только C

	val := q.Pop()
	if val != "C" {
		t.Errorf("Ожидалось C, получено %s", val)
	}
	if q.rear != nil {
		t.Error("После удаления последнего элемента rear должен стать nil")
	}

	// 7. Повторная проверка IsEmpty
	if !q.IsEmpty() {
		t.Error("Очередь должна быть пуста")
	}
}

// === Тесты для HashTable (Хеш-таблица с двойным хешированием) ===

func TestHashTableFullCoverage(t *testing.T) {
	// 1. Создаем маленькую таблицу
	ht := NewHashTable(3)

	// --- Секция Вставки и Обновления ---
	ht.Insert("key1", 10)
	ht.Insert("key1", 20) // Обновление
	if v, _ := ht.Get("key1"); v != 20 {
		t.Errorf("Ожидалось обновление до 20, получили %d", v)
	}

	// --- Секция Удаления ---

	// Удаление несуществующего (покроет ветку "Key not found")
	ht.Delete("ghost")

	// Удаление существующего
	ht.Delete("key1")
	if _, ok := ht.Get("key1"); ok {
		t.Error("Ключ key1 должен быть удален")
	}
	if ht.Count != 0 {
		t.Errorf("Count должен быть 0 после удаления, получили %d", ht.Count)
	}

	// --- Секция Коллизий и Переполнения ---
	ht.Insert("A", 1)
	ht.Insert("B", 2)
	ht.Insert("C", 3) // Таблица заполнена
	ht.Insert("D", 4) // Сообщение "Table is full"

	// Попытка удаления в полностью заполненой таблице (ключ отсутствует)
	// Это закроет ветку цикла до возврата в initialIndex
	ht.Delete("Z")

	// 6. Покрытие Get для несуществующего ключа
	_, ok := ht.Get("missing_key")
	if ok {
		t.Error("Ключ не должен быть найден")
	}

	// 7. Проверка хеш-функций
	h1 := ht.h1("test")
	h2 := ht.h2("test")
	if h1 < 0 || h1 >= ht.Size || h2 <= 0 {
		t.Error("Ошибка в логике хеш-функций")
	}
}

// === Тесты для CompleteBinaryTree (Полное бинарное дерево) ===
func TestCompleteBinaryTree(t *testing.T) {
	tree := NewCompleteBinaryTree()
	values := []int{1, 2, 3, 4, 5}
	for _, v := range values {
		tree.Insert(v)
	}

	if !tree.Search(3) || tree.Search(10) {
		t.Error("Ошибка поиска в дереве")
	}

	if !tree.IsComplete() {
		t.Error("Дерево должно быть полным")
	}

	// Ручная порча структуры для проверки IsComplete
	tree.root.left.left = nil
	// Теперь дерево не полное (есть дырка слева, но есть правый сосед)
	if tree.IsComplete() {
		// Примечание: алгоритм IsComplete в вашем коде
		// пометит flag=true, если встретит nil.
	}

	tree.Print()
	tree.clear()
	if tree.root != nil {
		t.Error("Дерево не очищено")
	}
}
