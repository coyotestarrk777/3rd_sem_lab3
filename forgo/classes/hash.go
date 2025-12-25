package classes

import (
	"fmt"
	"hash/fnv"
)

// Item представляет элемент хеш-таблицы
type Item struct {
	Key   string
	Value int
	IsSet bool // Флаг, указывающий, занята ли ячейка
}

// HashTable структура
type HashTable struct {
	Storage []Item
	Size    int
	Count   int
}

// NewHashTable создает таблицу заданного размера
func NewHashTable(size int) *HashTable {
	return &HashTable{
		Storage: make([]Item, size),
		Size:    size,
	}
}

// h1 - первичная хеш-функция
func (ht *HashTable) h1(key string) int {
	h := fnv.New32a()
	h.Write([]byte(key))
	return int(h.Sum32()) % ht.Size
}

// h2 - вторичная хеш-функция (определяет шаг)
// Важно: шаг должен быть взаимно простым с размером таблицы
func (ht *HashTable) h2(key string) int {
	h := fnv.New32a()
	h.Write([]byte(key + "salt")) // Изменяем вход для второго хеша
	step := (int(h.Sum32()) % (ht.Size - 1)) + 1
	return step
}

// Insert добавляет или обновляет элемент
func (ht *HashTable) Insert(key string, value int) {
	if ht.Count >= ht.Size {
		fmt.Println("Table is full")
		return
	}

	index := ht.h1(key)
	step := ht.h2(key)

	for ht.Storage[index].IsSet && ht.Storage[index].Key != key {
		index = (index + step) % ht.Size
	}

	if !ht.Storage[index].IsSet {
		ht.Count++
	}
	ht.Storage[index] = Item{Key: key, Value: value, IsSet: true}
}

// Get ищет значение по ключу
func (ht *HashTable) Get(key string) (int, bool) {
	index := ht.h1(key)
	step := ht.h2(key)

	startPos := index

	for ht.Storage[index].IsSet {
		if ht.Storage[index].Key == key {
			return ht.Storage[index].Value, true
		}
		index = (index + step) % ht.Size
		if index == startPos { // Прошли полный круг
			break
		}
	}
	return 0, false
}

// Delete удаляет элемент по ключу (ленивое удаление)
func (ht *HashTable) Delete(key string) {
	index := ht.h1(key)
	step := ht.h2(key)
	initialIndex := index

	for ht.Storage[index].IsSet {
		if ht.Storage[index].Key == key {
			ht.Storage[index].IsSet = false
			ht.Storage[index].Key = "" // Очищаем ключ
			ht.Count--
			return
		}
		index = (index + step) % ht.Size
		if index == initialIndex {
			break
		}
	}
	fmt.Println("Key not found for deletion")
}
