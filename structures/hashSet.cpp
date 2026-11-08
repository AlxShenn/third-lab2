#include "hashSet.h"

template <typename T>
size_t HashSet<T>::hash(const T& key) const {
    return std::hash<T>{}(key) % capacity;
}

template <typename T>
HashSet<T>::HashSet(size_t cap) : capacity(cap), size(0) {
    table.resize(capacity, nullptr);
}

template <typename T>
HashSet<T>::~HashSet() { 
    free(); 
}

template <typename T>
void HashSet<T>::free() {
    for (size_t i = 0; i < capacity; ++i) {
        Node* cur = table[i];
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        table[i] = nullptr;
    }
    size = 0;
}

template <typename T>
void HashSet<T>::add(const T& value) {
    size_t idx = hash(value);
    Node* cur = table[idx];
    while (cur) {
        if (cur->data == value) return;
        cur = cur->next;
    }
    table[idx] = new Node(value, table[idx]);
    size++;
}

template <typename T>
bool HashSet<T>::remove(const T& value) {
    size_t idx = hash(value);
    Node* cur = table[idx];
    Node* prev = nullptr;
    while (cur) {
        if (cur->data == value) {
            if (prev) prev->next = cur->next;
            else table[idx] = cur->next;
            delete cur;
            size--;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

template <typename T>
bool HashSet<T>::contains(const T& value) const {
    size_t idx = hash(value);
    Node* cur = table[idx];
    while (cur) {
        if (cur->data == value) return true;
        cur = cur->next;
    }
    return false;
}

template <typename T>
size_t HashSet<T>::getSize() const { return size; }

template <typename T>
vector<T> HashSet<T>::getAll() const {
    vector<T> result;
    for (size_t i = 0; i < capacity; ++i) {
        Node* cur = table[i];
        while (cur) {
            result.push_back(cur->data);
            cur = cur->next;
        }
    }
    return result;
}

template class HashSet<string>;