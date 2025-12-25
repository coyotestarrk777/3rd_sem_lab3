#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Подключаем ваши заголовочные файлы
#include "array.h"
#include "LList.h"
#include "DList.h"
#include "cbt.h"
#include "hash.h"
#include "stack.h"
#include "queue.h"

using namespace std;

class DataManager {
private:
    // Помощник для записи строк в бинарный файл
    static void writeStringBin(ofstream& out, const string& s) {
        size_t len = s.size();
        out.write((char*)&len, sizeof(len));
        out.write(s.c_str(), len);
    }

    // Помощник для чтения строк из бинарного файла
    static string readStringBin(ifstream& in) {
        size_t len;
        if (!in.read((char*)&len, sizeof(len))) return "";
        string s(len, ' ');
        in.read(&s[0], len);
        return s;
    }

public:
    // 1. МАССИВ (Array)
    static void processArray(Array& obj, const string& path, bool save, bool isBin) {
        if (save) {
            ofstream out(path, isBin ? ios::binary : ios::out);
            int size = obj.getSize();
            if (isBin) {
                out.write((char*)&size, sizeof(size));
                for (int i = 0; i < size; i++) writeStringBin(out, obj.getElementAt(i));
            } else {
                out << size << "\n";
                for (int i = 0; i < size; i++) out << obj.getElementAt(i) << "\n";
            }
        } else {
            ifstream in(path, isBin ? ios::binary : ios::in);
            int size;
            if (isBin) in.read((char*)&size, sizeof(size)); else in >> size;
            for (int i = 0; i < size; i++) {
                string v; if (isBin) v = readStringBin(in); else in >> v;
                obj.addMasAtEnd(v);
            }
        }
    }

    // 2. ОДНОСВЯЗНЫЙ СПИСОК (OdSpis)
    static void processLList(OdSpis*& head, const string& path, bool save, bool isBin) {
        OdSpis helper;
        if (save) {
            ofstream out(path, isBin ? ios::binary : ios::out);
            int size = helper.SizeList(head);
            if (isBin) out.write((char*)&size, sizeof(size)); else out << size << "\n";
            OdSpis* curr = head;
            while (curr) {
                if (isBin) writeStringBin(out, curr->getName()); else out << curr->getName() << "\n";
                curr = curr->getNext();
            }
        } else {
            helper.cleanupList(head);
            ifstream in(path, isBin ? ios::binary : ios::in);
            int size;
            if (isBin) in.read((char*)&size, sizeof(size)); else in >> size;
            for (int i = 0; i < size; i++) {
                string v; if (isBin) v = readStringBin(in); else in >> v;
                if (head == nullptr) helper.AddToBegin(head, v); else helper.AddToEnd(head, v);
            }
        }
    }

    // 3. ДВУСВЯЗНЫЙ СПИСОК (StudentGroup)
    static void processDList(StudentGroup& list, const string& path, bool save, bool isBin) {
        if (save) {
            ofstream out(path, isBin ? ios::binary : ios::out);
            vector<string> data;
            StudentGroup temp = list;
            while (!temp.isEmpty()) {
                data.push_back(temp.getFirst());
                temp.deleteStudentFromStart();
            }
            int size = data.size();
            if (isBin) out.write((char*)&size, sizeof(size)); else out << size << "\n";
            for (const string& s : data) {
                if (isBin) writeStringBin(out, s); else out << s << "\n";
            }
        } else {
            list.clear();
            ifstream in(path, isBin ? ios::binary : ios::in);
            int size;
            if (isBin) in.read((char*)&size, sizeof(size)); else in >> size;
            for (int i = 0; i < size; i++) {
                string v; if (isBin) v = readStringBin(in); else in >> v;
                list.addStudentToEnd(v);
            }
        }
    }

    // 4. СТЕК (Stack)
    static void processStack(Stack*& ptr, const string& path, bool save, bool isBin) {
        if (save) {
            vector<string> tempVec;
            while (ptr != nullptr) tempVec.push_back(Stack::SPOP(ptr));
            ofstream out(path, isBin ? ios::binary : ios::out);
            int size = tempVec.size();
            if (isBin) out.write((char*)&size, sizeof(size)); else out << size << "\n";
            for (int i = size - 1; i >= 0; i--) {
                if (isBin) writeStringBin(out, tempVec[i]); else out << tempVec[i] << "\n";
                Stack::SPUSH(ptr, tempVec[i]); // Возвращаем в стек
            }
        } else {
            Stack::clearStack(ptr);
            ifstream in(path, isBin ? ios::binary : ios::in);
            int size;
            if (isBin) in.read((char*)&size, sizeof(size)); else in >> size;
            for (int i = 0; i < size; i++) {
                string v; if (isBin) v = readStringBin(in); else in >> v;
                Stack::SPUSH(ptr, v);
            }
        }
    }

    // 5. ОЧЕРЕДЬ (Queue)
    static void processQueue(Queue*& head, Queue*& tail, const string& path, bool save, bool isBin) {
        if (save) {
            ofstream out(path, isBin ? ios::binary : ios::out);
            int size = Queue::countQueue(head);
            if (isBin) out.write((char*)&size, sizeof(size)); else out << size << "\n";
            Queue* curr = head;
            while (curr) {
                if (isBin) writeStringBin(out, curr->getToy()); else out << curr->getToy() << "\n";
                curr = curr->getSite();
            }
        } else {
            Queue::clearQueue(head, tail);
            ifstream in(path, isBin ? ios::binary : ios::in);
            int size;
            if (isBin) in.read((char*)&size, sizeof(size)); else in >> size;
            for (int i = 0; i < size; i++) {
                string v; if (isBin) v = readStringBin(in); else in >> v;
                Queue::QPUSH(head, tail, v);
            }
        }
    }

    // 6. ДЕРЕВО (CompleteBinaryTree)
    static void processCBT(CompleteBinaryTree& tree, const string& path, bool save, bool isBin) {
        if (save) {
            ofstream out(path, isBin ? ios::binary : ios::out);
            int size = tree.size();
            if (isBin) out.write((char*)&size, sizeof(size)); else out << size << "\n";
            for (int i = 0; i < size; i++) {
                int val = tree.getElement(i);
                if (isBin) out.write((char*)&val, sizeof(val)); else out << val << " ";
            }
        } else {
            // В CBT на базе вектора элементы просто добавляются в конец
            ifstream in(path, isBin ? ios::binary : ios::in);
            int size, val;
            if (isBin) in.read((char*)&size, sizeof(size)); else in >> size;
            for (int i = 0; i < size; i++) {
                if (isBin) in.read((char*)&val, sizeof(val)); else in >> val;
                tree.insert(val);
            }
        }
    }

    // 7. ХЕШ-ТАБЛИЦА (DoubleHashTable)
    static void processHash(DoubleHashTable& table, const string& path, bool save, bool isBin) {
        if (save) {
            int keys[HASH_SIZE]; string values[HASH_SIZE]; int count;
            table.getAllElements(keys, values, count);
            ofstream out(path, isBin ? ios::binary : ios::out);
            if (isBin) out.write((char*)&count, sizeof(count)); else out << count << "\n";
            for (int i = 0; i < count; i++) {
                if (isBin) {
                    out.write((char*)&keys[i], sizeof(int));
                    writeStringBin(out, values[i]);
                } else out << keys[i] << " " << values[i] << "\n";
            }
        } else {
            table.INIT_HASH_TABLE();
            ifstream in(path, isBin ? ios::binary : ios::in);
            int count, k; string v;
            if (isBin) in.read((char*)&count, sizeof(count)); else in >> count;
            for (int i = 0; i < count; i++) {
                if (isBin) { in.read((char*)&k, sizeof(int)); v = readStringBin(in); }
                else in >> k >> v;
                table.insert(k, v);
            }
        }
    }
};

// Вспомогательная функция для проверки стека
void printStack(Stack* top) {
    if (!top) {
        cout << "Стек пуст" << endl;
        return;
    }
    Stack* temp = nullptr;
    vector<string> elements;
    
    // Извлекаем все элементы для просмотра
    while (top) {
        string value = Stack::SPOP(top);
        elements.push_back(value);
        Stack::SPUSH(temp, value);
    }
    
    // Возвращаем элементы обратно
    while (temp) {
        string value = Stack::SPOP(temp);
        Stack::SPUSH(top, value);
    }
    
    // Выводим элементы (снизу вверх)
    cout << "Элементы стека (снизу вверх): ";
    for (int i = elements.size() - 1; i >= 0; i--) {
        cout << elements[i] << " ";
    }
    cout << endl;
}

// Вспомогательная функция для проверки массива
void printArray(Array& arr) {
    cout << "Элементы массива: ";
    for (int i = 0; i < arr.getSize(); i++) {
        cout << arr.getElementAt(i) << " ";
    }
    cout << endl;
}

// Вспомогательная функция для проверки хеш-таблицы
void printHashTable(DoubleHashTable& table) {
    int keys[HASH_SIZE];
    string values[HASH_SIZE];
    int count;
    
    table.getAllElements(keys, values, count);
    
    cout << "Хеш-таблица (" << count << " элементов):" << endl;
    for (int i = 0; i < count; i++) {
        cout << "Ключ: " << keys[i] << ", Значение: " << values[i] << endl;
    }
}

int main() {
    // Демонстрация работы
    cout << "--- Тестирование Сериализации ---" << endl;

    // 1. Стек
    Stack* myStack = nullptr;
    Stack::SPUSH(myStack, "Stack_Data_1");
    Stack::SPUSH(myStack, "Stack_Data_2");
    DataManager::processStack(myStack, "stack.bin", true, true);
    cout << "1. Стек сохранен в бинарный файл." << endl;

    // 2. Массив
    Array myArr(10);
    myArr.addMasAtEnd("Array_Element_1");
    myArr.addMasAtEnd("Array_Element_2");
    DataManager::processArray(myArr, "array.txt", true, false);
    cout << "2. Массив сохранен в текстовый файл." << endl;

    // 3. Хеш-таблица
    DoubleHashTable myHash;
    myHash.insert(101, "Hash_Value_1");
    myHash.insert(202, "Hash_Value_2");
    myHash.insert(303, "Hash_Value_3");
    DataManager::processHash(myHash, "hash.bin", true, true);
    cout << "3. Хеш-таблица сохранена в бинарный файл." << endl;

    cout << "\n--- Тестирование Десериализации ---" << endl;

    // Загрузка стека в новый объект
    Stack* loadedStack = nullptr;
    DataManager::processStack(loadedStack, "stack.bin", false, true);
    cout << "1. Загруженный стек: ";
    printStack(loadedStack);

    // Загрузка массива
    Array loadedArr(10);
    DataManager::processArray(loadedArr, "array.txt", false, false);
    cout << "2. Загруженный массив: ";
    printArray(loadedArr);

    // Загрузка хеш-таблицы
    DoubleHashTable loadedHash;
    DataManager::processHash(loadedHash, "hash.bin", false, true);
    cout << "3. Загруженная хеш-таблица:" << endl;
    printHashTable(loadedHash);

    // Проверка работы загруженной таблицы
    cout << "\n--- Проверка работы загруженной таблицы ---" << endl;
    
    // Проверка ключей
    cout << "Ключ 202 существует: " << (loadedHash.containsKey(202) ? "Да" : "Нет") << endl;
    cout << "Ключ 999 существует: " << (loadedHash.containsKey(999) ? "Да" : "Нет") << endl;
    
    // Проверка элементов
    cout << "Элемент (202, 'Hash_Value_2') существует: " 
         << (loadedHash.contains(202, "Hash_Value_2") ? "Да" : "Нет") << endl;
    
    // Проверка количества элементов
    cout << "Количество элементов в таблице: " << loadedHash.elementCount() << endl;
    
    // Добавление нового элемента
    cout << "Добавление нового элемента (404, 'New_Value'): "
         << (loadedHash.insert(404, "New_Value") ? "Успешно" : "Ошибка") << endl;
    
    cout << "\nОбновленная хеш-таблица:" << endl;
    printHashTable(loadedHash);

    return 0;
}