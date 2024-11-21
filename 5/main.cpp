#include <iostream>
#include "bst.h"

using namespace std;

int main() {
    BinarySearchTree bst;

    // Массив фиксированного размера
    const int size = 100;
    int input[size];
    int n = 0;

    // Ввод данных
    cout << "Введите числа (через пробел, завершите ввод любым нечисловым символом): ";

    while (n < size) {
        int value;
        if (cin >> value) {
            input[n++] = value;
        } else {
            break; // Завершение ввода при нечисловом значении
        }
    }

    // Перенос строки после завершения ввода
    cin.clear();
    cin.ignore(10000, '\n');

    // Обработка данных
    for (int i = 0; i < n; ++i) {
        int depth = bst.insert(input[i]);
        if (depth != -1) {
            cout << depth << " ";
        }
    }

    cout << endl;
    return 0;
}
