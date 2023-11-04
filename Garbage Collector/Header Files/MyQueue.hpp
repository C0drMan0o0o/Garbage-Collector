#pragma once
#include <iostream>

#include "garbageCollectedObject.hpp"

class MyQueue {
private:
    struct Node {
        garbageCollectedObject* data;
        Node* next;
        Node(garbageCollectedObject* data) : data(data), next(NULL) {}
    };
    Node* front;
    Node* rear;
    int count = 0;
public:
    MyQueue();
    void enqueue(garbageCollectedObject*);
    garbageCollectedObject* dequeue();
    garbageCollectedObject* peek() const;
    int getCount() const;
    bool isEmpty() const;
    void print() const;
};
