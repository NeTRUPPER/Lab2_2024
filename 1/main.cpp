#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "stack.h"

using namespace std;

// Функция для проверки, является ли строка числом
bool is_number(const string& s) {
    if (s.empty()) return false;
    
    size_t st = 0;
    if (s[0] == '-') {
        st = 1; 
    }

    if (st == s.size()) return false; 

    for (size_t i = st; i < s.size(); ++i) {
        if (!isdigit(s[i])) return false;
    }
    
    return true;
}

// Функция для выполнения операций
double perform_operation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) throw runtime_error("Division by zero");
            return a / b;
        default:
            throw runtime_error("Unknown operator");
    }
}

// Функция для вычисления выражения в обратной польской записи
double evaluate_rpn(const string& expression) {
    Stack<double> stack;

    stringstream ss(expression);
    string token;

    while (ss >> token) {
        if (is_number(token)) {
            // Если токен — число, преобразуем его и добавляем в стек
            stack.push(stod(token));
        } else if (token.length() == 1 && string("+-*/").find(token) != string::npos) {
            // Если токен — оператор, извлекаем два числа из стека
            if (stack.get_size() < 2) {
                throw runtime_error("Invalid expression: not enough operands");
            }

            double b = stack.peek(); stack.pop();
            double a = stack.peek(); stack.pop();

            // Выполняем операцию и помещаем результат в стек
            double result = perform_operation(a, b, token[0]);
            stack.push(result);
        } else {
            throw runtime_error("Invalid token in expression: " + token);
        }
    }

    if (stack.get_size() != 1) {
        throw runtime_error("Invalid expression: leftover elements in stack");
    }

    return stack.peek();
}

int main() {
    string expression;
    cout << "Enter an expression in Reverse Polish Notation (RPN): ";
    getline(cin, expression);

    try {
        double result = evaluate_rpn(expression);
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
