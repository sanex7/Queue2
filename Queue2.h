#ifndef TEMPLATE_CLASSES_H
#define TEMPLATE_CLASSES_H

#include <iostream>
#include <stdexcept>


template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
        }
        else {
            head = newNode;
        }
        tail = newNode;
        size++;
    }

    void dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
        size--;
    }

    T front() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return head->data;
    }

    bool isEmpty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }
};


template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    void append(const T& value) {
        Node* newNode = new Node(value);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
        }
        else {
            head = newNode;
        }
        tail = newNode;
        size++;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    DoublyLinkedList* clone() const {
        DoublyLinkedList* newList = new DoublyLinkedList();
        for (Node* current = head; current != nullptr; current = current->next) {
            newList->append(current->data);
        }
        return newList;
    }

    DoublyLinkedList operator+(const DoublyLinkedList& other) const {
        DoublyLinkedList result;
        for (Node* current = head; current != nullptr; current = current->next) {
            result.append(current->data);
        }
        for (Node* current = other.head; current != nullptr; current = current->next) {
            result.append(current->data);
        }
        return result;
    }

    DoublyLinkedList operator*(const DoublyLinkedList& other) const {
        DoublyLinkedList result;
        for (Node* current = head; current != nullptr; current = current->next) {
            for (Node* otherCurrent = other.head; otherCurrent != nullptr; otherCurrent = otherCurrent->next) {
                if (current->data == otherCurrent->data) {
                    result.append(current->data);
                }
            }
        }
        return result;
    }
};


template <typename T>
class Array {
private:
    T* data;
    size_t size;
    size_t capacity;
    int growFactor;

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Array(int initialSize = 0, int grow = 1)
        : size(0), capacity(initialSize), growFactor(grow) {
        data = new T[capacity];
    }

    ~Array() {
        delete[] data;
    }

    size_t GetSize() const {
        return size;
    }

    void SetSize(int newSize, int grow = 1) {
        if (newSize > capacity) {
            resize(newSize);
        }
        size = newSize;
        growFactor = grow;
    }

    int GetUpperBound() const {
        return size > 0 ? size - 1 : -1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
        if (size < capacity) {
            resize(size);
        }
    }

    void RemoveAll() {
        delete[] data;
        data = new T[capacity];
        size = 0;
    }

    T GetAt(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void SetAt(int index, const T& value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = value;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void Add(const T& value) {
        if (size == capacity) {
            resize(capacity + growFactor);
        }
        data[size++] = value;
    }

    void Append(const Array& other) {
        for (size_t i = 0; i < other.size; ++i) {
            Add(other.data[i]);
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            growFactor = other.growFactor;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    T* GetData() const {
        return data;
    }

    void InsertAt(int index, const T& value) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }
        if (size == capacity) {
            resize(capacity + growFactor);
        }
        for (size_t i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        size--;
    }
};

#endif
