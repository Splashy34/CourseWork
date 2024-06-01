#pragma once
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class List
{
public:
    List() : head(nullptr), tail(nullptr), size(0), cachedNode(nullptr), cachedIndex(-1) {}
    ~List()
    {
        clear();
    }

    void add(T data)
    {
        Node* newnode = new Node(data);
        if (size == 0) {
            head = tail = newnode;
        }
        else {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }
        size++;
    }

    void insert(int index, T data)
    {
        if (index < 0 || index > size)
        {
            return;
        }
        if (index == size)
        {
            add(data);
            return;
        }
        Node* newnode = new Node(data);
        if (index == 0)
        {
            newnode->next = head;
            head->prev = newnode;
            head = newnode;
        }
        else
        {
            Node* current = getIndex(index);
            newnode->next = current;
            newnode->prev = current->prev;
            current->prev->next = newnode;
            current->prev = newnode;
        }
        cachedIndex = index;
        cachedNode = newnode;
        size++;
    }

    void removeAt(int index)
    {
        if (index < 0 || index >= size) return;
        Node* todel;
        if (index == 0)
        {
            todel = head;
            head = head->next;
            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            else {
                tail = nullptr;
                cachedNode = nullptr;
                cachedIndex = -1;
            }
        }
        else if (index == size - 1)
        {
            todel = tail;
            tail = tail->prev;
            tail->next = nullptr;
        }
        else {
            todel = getIndex(index);
            todel->next->prev = todel->prev;
            todel->prev->next = todel->next;
        }
        if (todel == cachedNode)
        {
            cachedNode = todel->prev;
            cachedIndex = max(0, index - 1);
        }
        else if (index < cachedIndex)
        {
            cachedIndex--;
        }
        delete todel;
        size--;
    }

    T elementAt(int index)
    {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        Node* node = getIndex(index);
        return node->data;
    }

    T& elementAtRef(int index)
    {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        Node* node = getIndex(index);
        return node->data;
    }

    void setElementAt(int index, T newData)
    {
        Node* current = getIndex(index);
        if (current != nullptr)
        {
            current->data = newData;
            cachedNode = current;
            cachedIndex = index;
        }
    }

    int count()
    {
        return size;
    }

    void clear()
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = cachedNode = nullptr;
        size = 0;
        cachedIndex = -1;
    }

private:
    class Node
    {
    public:
        T data;
        Node* next;
        Node* prev;
        Node(T data) : data(data), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    Node* tail;
    int size;
    Node* cachedNode;
    int cachedIndex;

    Node* reach_index(Node* startNode, int start, int end)
    {
        Node* current = startNode;
        if (start < end) {
            for (int i = start; i < end; ++i)
            {
                current = current->next;
            }
        }
        else
        {
            for (int i = start; i > end; --i)
            {
                current = current->prev;
            }
        }
        return current;
    }

    Node* getIndex(int index)
    {
        if (index < 0 || index >= size) return nullptr;
        Node* current = nullptr;
        if (cachedNode && abs(cachedIndex - index) <= index && abs(cachedIndex - index) <= size - index - 1) {
            current = reach_index(cachedNode, cachedIndex, index);
        }
        else if (index <= size - index - 1)
        {
            current = reach_index(head, 0, index);
        }
        else
        {
            current = reach_index(tail, size - 1, index);
        }
        cachedNode = current;
        cachedIndex = index;
        return current;
    }
};
