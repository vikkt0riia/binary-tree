#include "tree.hpp"

// Вспомогательная функция для создания нового узла
tree_node* create_node(int val) {
    return new tree_node{val, nullptr, nullptr};
}

auto tree::insert(int val) -> tree_node* {
    // Если дерево пустое, создаем корневой узел
    if (!root) {
        root = create_node(val);
        return root;
    }

    // Инициализируем текущий узел и родительский
    tree_node* current = root;
    tree_node* parent = nullptr;

    while (current) {
        parent = current;
        if (val < current->value) {
            current = current->left;
        } else if (val > current->value) {
            current = current->right;
        } else {
            // Если значение уже есть в дереве, возвращаем его
            return current;
        }
    }

    // Создаем новый узел и вставляем его
    tree_node* new_node = create_node(val);
    if (val < parent->value) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    return new_node;
}

auto tree::remove(int val) -> bool {
    // Инициализируем текущий узел и родительский
    tree_node* current = root;
    tree_node* parent = nullptr;

    // Ищем узел с заданным значением
    while (current && current->value != val) {
        parent = current;
        if (val < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // Если узел не найден, возвращаем false
    if (!current) {
        return false;
    }

    // Узел с одним или без детей
    if (!current->left || !current->right) {
        tree_node* child = current->left ? current->left : current->right;
        if (!parent) {
            root = child;  // Удаление корня
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete current;
    } else {
        // Узел с двумя детьми
        tree_node* successor = current->right;
        tree_node* successor_parent = current;

        // Находим наименьший элемент в правом поддереве
        while (successor->left) {
            successor_parent = successor;
            successor = successor->left;
        }

        // Перемещаем значение наименьшего элемента
        current->value = successor->value;

        // Удаляем наименьший элемент
        if (successor_parent->left == successor) {
            successor_parent->left = successor->right;
        } else {
            successor_parent->right = successor->right;
        }
        delete successor;
    }

    return true;
}
