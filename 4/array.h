#pragma once

#include <iostream>

using namespace std;

template <typename T>
class MyArray {
private:
    T* arr;       // Указатель на массив
    int size;     // Размер массива
    int capacity; // Вместимость массива

public:
    // Конструктор для инициализации массива
    MyArray(int cap) : size(0), capacity(cap) {
        arr = new T[capacity];  // Выделение памяти под массив
    }

    // Деструктор для освобождения памяти
    ~MyArray() {
        delete[] arr;
    }

    // Метод для получения размера массива
    int getSize() const {
        return size;
    }

    // Оператор индексации для доступа к элементам
    T& operator[](int index) {
        return arr[index];
    }

    // Метод для добавления элемента в массив
    void add(const T& value) {
        if (size < capacity) {
            arr[size++] = value;
        } else {
            cout << "Array is full!" << endl;
        }
    }

    // Метод для вывода массива
    void print() const {
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};
