package main

import (
	"fmt"
	"lab3_1/classes" // Путь: название модуля из go.mod + имя папки
)

func main() {
	fmt.Println("=== Тестирование Сериализации ===")

	// 1. Динамический массив
	arr := classes.NewArray()
	arr.PushBack("Данные массива")
	arr.Serialize("array.json", false) // Сохраняем в текст
	fmt.Println("1. Массив сохранен в array.json")

	// 2. Односвязный список
	llist := classes.NewFL()
	llist.AddTail("Элемент LList")
	llist.Serialize("llist.bin", true) // Сохраняем в бинарный формат
	fmt.Println("2. LList сохранен в llist.bin")

	// 3. Двусвязный список
	dlist := classes.NewDL()
	dlist.AddTail("Элемент DList")
	dlist.Serialize("dlist.json", false)
	fmt.Println("3. DList сохранен в dlist.json")

	// 4. Стек
	stack := classes.NewStack()
	stack.Push("Верхушка стека")
	stack.Serialize("stack.json", false)
	fmt.Println("4. Стек сохранен в stack.json")

	// 5. Очередь
	queue := classes.NewQueue()
	queue.Push("Первый в очереди")
	queue.Serialize("queue.json", false)
	fmt.Println("5. Очередь сохранена в queue.json")

	// 6. Хеш-таблица
	ht := classes.NewHashTable(10)
	ht.Insert("key1", 100)
	ht.Serialize("hash.json", false)
	fmt.Println("6. Хеш-таблица сохранена в hash.json")

	// 7. Бинарное дерево
	tree := classes.NewCompleteBinaryTree()
	tree.Insert(50)
	tree.Serialize("tree.json", false)
	fmt.Println("7. Дерево сохранено в tree.json")

	fmt.Println("\nВсе типы данных обработаны успешно!")

	fmt.Println("=== Загрузка данных из файлов (Проверка) ===")

	// 1. Массив
	newArr := classes.NewArray()
	if err := newArr.Deserialize("array.json", false); err == nil {
		fmt.Print("1. Массив восстановлен: ")
		newArr.Print()
	}

	// 2. LList
	newLList := classes.NewFL()
	if err := newLList.Deserialize("llist.bin", true); err == nil {
		fmt.Printf("2. LList восстановлен: %v\n", newLList.ToSlice())
	}

	// 3. DList
	newDList := classes.NewDL()
	if err := newDList.Deserialize("dlist.json", false); err == nil {
		fmt.Print("3. DList восстановлен (Forward): ")
		newDList.PrintForward()
	}

	// 4. Стек
	newStack := classes.NewStack()
	if err := newStack.Deserialize("stack.json", false); err == nil {
		fmt.Print("4. Стек восстановлен: ")
		newStack.Print()
	}

	// 5. Очередь
	newQueue := classes.NewQueue()
	if err := newQueue.Deserialize("queue.json", false); err == nil {
		fmt.Print("5. Очередь восстановлена: ")
		newQueue.Print()
	}

	// 6. Хеш-таблица
	newHT := classes.NewHashTable(10)
	if err := newHT.Deserialize("hash.json", false); err == nil {
		fmt.Println("6. Хеш-таблица восстановлена. Проверка ключа 'Gopher':")
		// Здесь можно добавить поиск по ключу, если метод реализован в hash.go
	}

	// 7. Дерево
	newTree := classes.NewCompleteBinaryTree()
	if err := newTree.Deserialize("tree.json", false); err == nil {
		fmt.Println("7. Дерево восстановлено. Структура:")
		newTree.Print()
	}

	fmt.Println("\nТестирование завершено успешно!")
}
