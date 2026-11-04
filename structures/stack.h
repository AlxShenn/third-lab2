#ifndef STACK_H
#define STACK_H
#include <string>
#include <iostream>

class Stack {
private:
    struct Node {
        std::string text;
        Node* next;
    };
    Node* head;

public:
    Stack();
    ~Stack();
    void push(const std::string& value);
    void pop(std::string& outValue);
    bool isEmpty() const;
    void print() const;
    void clear();
};
#endif