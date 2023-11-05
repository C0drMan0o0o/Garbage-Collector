#pragma once
#include <iostream>
#include <vector>

#include "garbageCollectedObject.hpp"
using std::vector;
using std::byte;

class MyLinkedList {
public:
    struct Node {
        byte* memStart;
        byte* memEnd;
        bool allocated = false;
        Node* next;
        Node(byte* memStart, byte* memEnd, bool allocated) : memStart(memStart), memEnd(memEnd), allocated(allocated) {}
    };
    MyLinkedList();
    void insertAtTail(byte* memStart, byte* memEnd, bool allocated);
    void deleteNode(byte*, byte*, bool);
    void deleteAtHead();
    vector<Node*> getNodes() const;
    bool isEmpty() const;
    int getCount() const;
    void editNode(byte*, byte*, bool);
    void print() const;
private:
    Node* head;
    Node* tail;
    int count = 0;
};

