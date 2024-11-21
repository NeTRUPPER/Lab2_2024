#pragma once

class BinarySearchTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Вспомогательный метод для вставки элемента и вычисления глубины
    int insert(Node*& node, int value, int depth) {
        if (!node) {
            node = new Node(value);
            return depth;
        }
        if (value < node->data) {
            return insert(node->left, value, depth + 1);
        } else if (value > node->data) {
            return insert(node->right, value, depth + 1);
        }
        // Если элемент уже есть, возвращаем -1
        return -1;
    }

    // Очистка дерева
    void clear(Node* node) {
        if (!node) return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        clear(root);
    }

    // Вставка элемента и возвращение глубины
    int insert(int value) {
        return insert(root, value, 1);
    }
};
