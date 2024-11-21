#include <iostream>
#include <string>
#include "hashtable.h"

using namespace std;

string intToRoman(int num) {
    // Создаем хеш-таблицу и заполняем её значениями
    HashTable<string, int> romanMap(13);
    romanMap.insert("M", 1000);
    romanMap.insert("CM", 900);
    romanMap.insert("D", 500);
    romanMap.insert("CD", 400);
    romanMap.insert("C", 100);
    romanMap.insert("XC", 90);
    romanMap.insert("L", 50);
    romanMap.insert("XL", 40);
    romanMap.insert("X", 10);
    romanMap.insert("IX", 9);
    romanMap.insert("V", 5);
    romanMap.insert("IV", 4);
    romanMap.insert("I", 1);

    string romanSymbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    string result = "";

    // Преобразуем число в римскую строку
    for (const string& symbol : romanSymbols) {
        int value = romanMap.get(symbol); // Получаем значение римского символа из хеш-таблицы
        while (num >= value) {
            result += symbol; // Добавляем символ в результат
            num -= value;     // Вычитаем значение из числа
        }
    }

    return result;
}

int main() {
    int number;
    cout << "Введите число: ";
    cin >> number;

    if (number < 1 || number > 3999) {
        cout << "Число должно быть в диапазоне от 1 до 3999" << endl;
        return 1;
    }

    string romanNumeral = intToRoman(number);
    cout << "Римское представление: " << romanNumeral << endl;

    return 0;
}
