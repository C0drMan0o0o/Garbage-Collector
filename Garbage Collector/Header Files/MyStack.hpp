#pragma once
#include <iostream>

#include "garbageCollectedObject.hpp"
#include "Scope.hpp"

class MyStack {
private:
    struct Node {
        Scope* data;
        Node* next;
        Node(Scope* data, Node* next = NULL) : data(data), next(next) {}
    };
    Node* top;
    int count = 0;
public:
    MyStack();
    void push(Scope*);
    Scope* pop();
    Scope* peek() const;
    bool isEmpty() const;
    int getCount() const;
    void print() const;
};
