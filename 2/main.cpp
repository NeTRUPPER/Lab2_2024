#include "hashtable.h"
#include <iostream>
#include <string>

using namespace std;

class Set {
private:
    HashTable<string, bool> hashTable; // Используем string как ключ, bool как фиктивное значение

public:
    // Конструктор множества
    Set(size_t capacity = 100) : hashTable(capacity) {}

    // Добавление элемента
    void add(const string& element) {
        hashTable.insert(element, true); // true - фиктивное значение
    }

    // Удаление элемента
    void remove(const string& element) {
        hashTable.remove(element);
    }

    // Проверка наличия элемента
    bool contains(const string& element) const {
        try {
            hashTable.get(element);
            return true;
        } catch (const out_of_range&) {
            return false;
        }
    }

    // Сохранение множества в файл
    void save_to_file(const string& filename) const {
        ofstream file(filename, ios::out | ios::trunc);  // Открытие файла для записи
        if (file.is_open()) {
            hashTable.save_to_file(filename);  // Вызываем метод для сохранения
            file.close();  // Закрытие файла после записи
        } else {
            cerr << "Failed to open file for saving: " << filename << endl;
        }
    }

    // Загрузка множества из файла
    void load_from_file(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            hashTable.load_from_file(filename);
            file.close();
        } else {
            cerr << "Failed to open file for loading: " << filename << endl;
            throw runtime_error("File not found");
        }
    }

    // Вывод множества (для отладки)
    void print() const {
        hashTable.print();
    }
};

// Обработка команд
void process_query(Set& set, const string& command, const string& arg) {
    if (command == "SETADD") {
        set.add(arg);
        cout << "Element added: " << arg << endl;
    } else if (command == "SETDEL") {
        set.remove(arg);
        cout << "Element removed: " << arg << endl;
    } else if (command == "SET_AT") {
        if (set.contains(arg)) {
            cout << "Element exists: " << arg << endl;
        } else {
            cout << "Element does not exist: " << arg << endl;
        }
    } else {
        cerr << "Unknown command: " << command << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Usage: ./program --file <file> --query <command> <arg>" << endl;
        return 1;
    }

    string file_path = argv[2];
    string command = argv[4];
    string arg = argc > 5 ? argv[5] : "";

    Set set;
    try {
        set.load_from_file(file_path);
    } catch (const runtime_error&) {
        cerr << "File not found, creating new set." << endl;
    }

    process_query(set, command, arg);

    // Сохраняем данные в файл
    set.save_to_file(file_path);
    return 0;
}
