#include <iostream>
#include <sstream>

using namespace std;

// Размер хеш-таблицы
const int hashsize = 100;

// Структура для самописного множества
class Set {
private:
    // Хеш-таблица для хранения элементов
    bool table[hashsize] = {false};  // Массив для хранения наличия элементов (true/false)

    // Хеш-функция
    int hash(int key) const {
        return key % hashsize;
    }

public:
    // Добавление элемента в множество
    void add(int element) {
        int index = hash(element);
        table[index] = true;  // Отметка о том, что элемент существует в множестве
    }

    // Проверка наличия элемента в множестве
    bool contains(int element) const {
        int index = hash(element);
        return table[index];  // Если элемент есть, возвращаем true
    }

    // Пересечение двух множеств
    Set intersection(const Set& other) const {
        Set result;
        for (int i = 0; i < hashsize; ++i) {
            if (table[i] && other.table[i]) {
                result.add(i);  // Если элементы пересекаются, добавляем их в результат
            }
        }
        return result;
    }

    // Количество элементов в множестве
    int size() const {
        int count = 0;
        for (int i = 0; i < hashsize; ++i) {
            if (table[i]) {
                count++;
            }
        }
        return count;
    }

    // Вывод множества
    void print() const {
        cout << "{";
        bool first = true;
        for (int i = 0; i < hashsize; ++i) {
            if (table[i]) {
                if (!first) cout << ", ";
                cout << i;
                first = false;
            }
        }
        cout << "}";
    }
};

// Функция для нахождения двух множеств с максимальным пересечением
void findMaxIntersection(Set sets[], int n) {
    int maxIntersectionCount = 0;
    Set set1, set2;

    // Перебор всех пар множеств
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            Set intersectionSet = sets[i].intersection(sets[j]);
            int intersectionSize = intersectionSet.size();
            
            // Если текущее пересечение больше, чем максимальное, обновляем
            if (intersectionSize > maxIntersectionCount) {
                maxIntersectionCount = intersectionSize;
                set1 = sets[i];
                set2 = sets[j];
            }
        }
    }

    // Вывод результатов
    cout << "Множества с максимальным пересечением: \n";
    set1.print();
    cout << " и ";
    set2.print();
    cout << ", количество общих элементов: " << maxIntersectionCount << endl;
}

int main() {
    int n;
    cout << "Введите количество множеств: ";
    cin >> n;
    cin.ignore(); // Игнорируем остатки в буфере ввода

    // Создание массивов множеств
    Set sets[n];

    // Ввод данных для каждого множества
    for (int i = 0; i < n; ++i) {
        cout << "Введите элементы для множества " << i + 1 << " (через пробел): ";
        string line;
        getline(cin, line);
        stringstream ss(line);

        int value;
        while (ss >> value) {
            sets[i].add(value);
        }
    }

    // Нахождение максимального пересечения
    findMaxIntersection(sets, n);

    return 0;
}
