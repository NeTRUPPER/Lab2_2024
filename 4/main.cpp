#include <iostream>
#include <sstream>
#include "array.h"

using namespace std;

// Функция для проверки наличия элемента в подмассиве
template <typename T>
bool contains(T* subarray, int subarraySize, T value) {
    for (int i = 0; i < subarraySize; ++i) {
        if (subarray[i] == value) {
            return true;
        }
    }
    return false;
}

// Функция для вывода всех подмножеств массива
template <typename T>
void printSubarrays(MyArray<T>& arr) {
    int n = arr.getSize();
    
    // Перебираем все подмножества с помощью битовой маски
    for (int i = 0; i < (1 << n); ++i) {
        T subarray[10]; // Максимально 10 элементов в подмассиве
        int subarraySize = 0;

        // Перебираем все биты числа i
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                if (!contains(subarray, subarraySize, arr[j])) {
                    subarray[subarraySize++] = arr[j]; // Добавляем элемент в подмассив
                }
            }
        }

        // Выводим подмассив
        cout << "{";
        for (int j = 0; j < subarraySize; ++j) {
            cout << subarray[j];
            if (j < subarraySize - 1) {
                cout << ", ";
            }
        }
        cout << "}" << endl;
    }
}

int main() {
    // Создаем массив с заданным размером
    cout << "Введите размер массива: ";
    int size;
    cin >> size;
    cin.ignore(); // Игнорируем остатки в буфере ввода

    MyArray<string> arr(size); // Пример с массивом строк

    cout << "Введите элементы массива через пробел: ";
    string line;
    getline(cin, line);
    stringstream ss(line);

    string value;
    while (ss >> value) {
        arr.add(value);
    }

    cout << "Все подмножества массива:\n";
    printSubarrays(arr);

    return 0;
}
