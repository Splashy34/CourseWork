#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Tree
{
private:

    struct Node
    {
        int key;
        T data;
        Node* left;
        Node* right;
        Node(int key, T data) : key(key), data(data), left(nullptr), right(nullptr) {}
    };

    int size;
    Node* root;

    void clearnode(Node* node)
    {
        if (node == nullptr) return;
        clearnode(node->left);
        clearnode(node->right);
        delete node;
    }

    Node* deleteByMerging(Node*& node)
    {
        Node* tmp = node;
        if (node != nullptr)
        {
            if (!node->right) node = node->left;
            else if (node->left == nullptr) node = node->right;
            else
            {
                tmp = node->left;
                while (tmp->right != nullptr) tmp = tmp->right;
                tmp->right = node->right;
                tmp = node;
                node = node->left;
            }
            delete tmp;
            size--;
            return node;
        }
        return nullptr;
    }

    void traverseInfix(Node* node, T* arr, int& index) const
    {
        if (node == nullptr) return;
        traverseInfix(node->left, arr, index);
        arr[index++] = node->data;
        traverseInfix(node->right, arr, index);
    }

public:
    enum Order { Infix };

    Tree()
    {
        size = 0;
        root = nullptr;
    }

    ~Tree()
    {
        clear();
    }

    void add(int key, T data)
    {
        if (contains(key)) return;
        Node* newnode = new Node(key, data);
        if (root == nullptr)
        {
            root = newnode;
        }
        else
        {
            Node* current = root;
            while (true)
            {
                if (key < current->key)
                {
                    if (current->left == nullptr)
                    {
                        current->left = newnode;
                        break;
                    }
                    current = current->left;
                }
                else
                {
                    if (current->right == nullptr)
                    {
                        current->right = newnode;
                        break;
                    }
                    current = current->right;
                }
            }
        }
        size++;
    }

    void remove(int key)
    {
        Node* node = root, * prev = nullptr;
        while (node != nullptr)
        {
            if (node->key == key) break;
            prev = node;
            if (key < node->key) node = node->left;
            else node = node->right;
        }
        if (node != nullptr && node->key == key)
        {
            if (node == root) root = deleteByMerging(root);
            else if (prev->left == node) prev->left = deleteByMerging(prev->left);
            else prev->right = deleteByMerging(prev->right);
        }
    }

    bool contains(int key)
    {
        Node* current = root;
        while (current != nullptr)
        {
            if (current->key == key) return true;
            if (key < current->key) current = current->left;
            else current = current->right;
        }
        return false;
    }

    int count()
    {
        return size;
    }

    void clear()
    {
        clearnode(root);
        root = nullptr;
        size = 0;
    }

    Node* getRoot() const
    {
        return root;
    }

    T* ToArray(Order order)
    {
        T* arr = new T[size];
        int index = 0;
        traverseInfix(root, arr, index);
        return arr;
    }
};
