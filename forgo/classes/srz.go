package classes

import (
	"encoding/gob"
	"encoding/json"
	"os"
)

// =================================================================
// ОБЩИЕ УТИЛИТЫ (Вспомогательные функции)
// =================================================================

func saveToFile(filename string, data interface{}, isBinary bool) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	if isBinary {
		return gob.NewEncoder(file).Encode(data)
	}
	return json.NewEncoder(file).Encode(data)
}

func loadFromFile(filename string, target interface{}, isBinary bool) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	if isBinary {
		return gob.NewDecoder(file).Decode(target)
	}
	return json.NewDecoder(file).Decode(target)
}

// =================================================================
// 1. ОДНОСВЯЗНЫЙ СПИСОК (ForwardList)
// =================================================================

func (l *ForwardList) Serialize(filename string, isBinary bool) error {
	// Используем ваш метод ToSlice из LList.go
	data := l.ToSlice()
	return saveToFile(filename, data, isBinary)
}

func (l *ForwardList) Deserialize(filename string, isBinary bool) error {
	var data []string
	if err := loadFromFile(filename, &data, isBinary); err != nil {
		return err
	}
	l.Clear() // Очищаем текущий список
	for _, v := range data {
		l.AddTail(v)
	}
	return nil
}

// =================================================================
// 2. ДВУСВЯЗНЫЙ СПИСОК (DoublyList)
// =================================================================

func (l *DoublyList) Serialize(filename string, isBinary bool) error {
	var data []string
	cur := l.head // Доступ к приватному полю head из DList.go
	for cur != nil {
		data = append(data, cur.data)
		cur = cur.next
	}
	return saveToFile(filename, data, isBinary)
}

func (l *DoublyList) Deserialize(filename string, isBinary bool) error {
	var data []string
	if err := loadFromFile(filename, &data, isBinary); err != nil {
		return err
	}
	// Очистка списка перед загрузкой
	l.head = nil
	l.tail = nil
	for _, v := range data {
		l.AddTail(v)
	}
	return nil
}

// =================================================================
// 3. ДИНАМИЧЕСКИЙ МАССИВ (Array)
// =================================================================

func (a *Array) Serialize(filename string, isBinary bool) error {
	data := a.data[:a.size] // Берем только реальные данные из array.go
	return saveToFile(filename, data, isBinary)
}

func (a *Array) Deserialize(filename string, isBinary bool) error {
	var data []string
	if err := loadFromFile(filename, &data, isBinary); err != nil {
		return err
	}
	a.data = make([]string, len(data))
	copy(a.data, data)
	a.size = len(data)
	a.capacity = len(data)
	return nil
}

// =================================================================
// 4. СТЕК (Stack)
// =================================================================

func (s *Stack) Serialize(filename string, isBinary bool) error {
	var data []string
	cur := s.head
	for cur != nil {
		data = append(data, cur.data)
		cur = cur.next
	}
	// Инвертируем, чтобы при загрузке через Push восстановить порядок
	for i, j := 0, len(data)-1; i < j; i, j = i+1, j-1 {
		data[i], data[j] = data[j], data[i]
	}
	return saveToFile(filename, data, isBinary)
}

func (s *Stack) Deserialize(filename string, isBinary bool) error {
	var data []string
	if err := loadFromFile(filename, &data, isBinary); err != nil {
		return err
	}
	s.Clear()
	for _, v := range data {
		s.Push(v)
	}
	return nil
}

// =================================================================
// 5. ОЧЕРЕДЬ (Queue)
// =================================================================

func (q *Queue) Serialize(filename string, isBinary bool) error {
	var data []string
	cur := q.front
	for cur != nil {
		data = append(data, cur.data)
		cur = cur.next
	}
	return saveToFile(filename, data, isBinary)
}

func (q *Queue) Deserialize(filename string, isBinary bool) error {
	var data []string
	if err := loadFromFile(filename, &data, isBinary); err != nil {
		return err
	}
	// Очистка и заполнение
	q.front = nil
	q.rear = nil
	for _, v := range data {
		q.Push(v)
	}
	return nil
}

// =================================================================
// 6. ХЕШ-ТАБЛИЦА (HashTable)
// =================================================================

func (ht *HashTable) Serialize(filename string, isBinary bool) error {
	data := make(map[string]int)
	for _, item := range ht.Storage {
		if item.IsSet {
			data[item.Key] = item.Value
		}
	}
	return saveToFile(filename, data, isBinary)
}

func (ht *HashTable) Deserialize(filename string, isBinary bool) error {
	var data map[string]int
	if err := loadFromFile(filename, &data, isBinary); err != nil {
		return err
	}
	// Перезаписываем данные в таблицу
	for k, v := range data {
		ht.Insert(k, v)
	}
	return nil
}

// =================================================================
// 7. БИНАРНОЕ ДЕРЕВО (CompleteBinaryTree)
// =================================================================

func (t *CompleteBinaryTree) Serialize(filename string, isBinary bool) error {
	var data []int
	if t.root != nil {
		// BFS обход для сохранения структуры CBT
		queue := []*treeNode{t.root}
		for len(queue) > 0 {
			cur := queue[0]
			queue = queue[1:]
			data = append(data, cur.data)
			if cur.left != nil {
				queue = append(queue, cur.left)
			}
			if cur.right != nil {
				queue = append(queue, cur.right)
			}
		}
	}
	return saveToFile(filename, data, isBinary)
}

func (t *CompleteBinaryTree) Deserialize(filename string, isBinary bool) error {
	var data []int
	if err := loadFromFile(filename, &data, isBinary); err != nil {
		return err
	}
	t.root = nil // Очистка корня
	for _, v := range data {
		t.Insert(v)
	}
	return nil
}
