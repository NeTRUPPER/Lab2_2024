#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

using namespace std;

// Реализация односвязного списка для хранения элементов с одинаковым хешем (коллизий)
template<typename K, typename V>
class LinkedList {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Метод для добавления элемента в список
    void insert_list(const K& key, const V& value) {
        Node* current = head;
        while (current) {
            if (current->key == key) {
                current->value = value; // Обновляем значение, если ключ существует
                return;
            }
            current = current->next;
        }
        // Добавляем новый элемент в начало списка
        Node* new_node = new Node(key, value);
        new_node->next = head;
        head = new_node;
    }

    // Метод для получения первого элемента
    Node* get_head() const {
        return head;
    }

    // Печать списка для отладки
    void print() const {
        Node* current = head;
        while (current) {
            cout << "[" << current->key << ": " << current->value << "] ";
            current = current->next;
        }
        cout <<endl;
    }

    // Проверка, содержит ли список элемент с указанным ключом
    bool contains(const K& key) const {
        Node* current = head;
        while (current) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Удаление элемента по ключу
    void remove_list(const K& key) {
        if (!head) return;
        if (head->key == key) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        while (current->next && current->next->key != key) {
            current = current->next;
        }

        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    // Запись списка в файл
    void save_to_file(ofstream& file) const {
        Node* current = head;
        while (current) {
            file << current->key << " " << current->value << "\n";
            current = current->next;
        }
    }
};



// Хеш-таблица с цепочками для решения коллизий
template<typename K, typename V>
class HashTable {
private:
    LinkedList<K, V>* table;
    size_t capacity;
    size_t size;

    // Простая хеш-функция для строк
    size_t hash(const string& key) const {
        size_t hash_value = 0;
        for (char ch : key) {
            hash_value = 37 * hash_value + ch;
        }
        return hash_value % capacity;
    }

    // Хеш-функция для целых чисел (для примера)
    size_t hash(int key) const {
        return key % capacity;
    }

public:
    HashTable(size_t table_size = 3) : capacity(table_size), size(0) {
        table = new LinkedList<K, V>[capacity];
    }

    ~HashTable() {
        delete[] table;
    }

    LinkedList<K, V>& get_list(size_t index) {
        return table[index];
    }

    // Добавление элемента
    void insert(const K& key, const V& value) {
        size_t index = hash(key);
        if (!table[index].contains(key)) {
            size++;
        }
        table[index].insert_list(key, value);
    }

    // Получение значения по ключу
    V get(const K& key) const {
        size_t index = hash(key);
        return table[index].get_list(key);
    }

    // Удаление элемента по ключу
    void remove(const K& key) {
        size_t index = hash(key);
        if (table[index].contains(key)) {
            size--;
        }
        table[index].remove_list(key);
    }

    // Печать всех элементов хеш-таблицы
    void print() const {
        for (size_t i = 0; i < capacity; ++i) {
            cout << "Index " << i << ": ";
            table[i].print();
        }
    }

    // Получение текущего размера хеш-таблицы
    size_t get_size() const {
        return size;
    }

    // Загрузка данных из файла
    void load_from_file(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            K key;
            V value;
            while (file >> key >> value) {
                insert(key, value);  // Корректная загрузка каждого элемента
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file for loading");
        }
    }

    // Сохранение данных в файл
    void save_to_file(const string& filename) const {
        ofstream file(filename, ios::out | ios::trunc);
        if (file.is_open()) {
            for (size_t i = 0; i < capacity; ++i) {
                table[i].save_to_file(file);  // вызываем метод save_to_file для каждого списка
                file << "\n";
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file for saving");
        }
    }
};
