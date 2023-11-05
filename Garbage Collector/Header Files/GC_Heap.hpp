#pragma once
#include <iostream>

#include "garbageCollectedObject.hpp"
#include "MyLinkedList.hpp"

using std::byte;

class GC_Heap {
private:
    MyLinkedList allocationList;
    byte* memStart;
    size_t size;
    byte* currentPtr;
public:
    GC_Heap(size_t);
    byte* getMemStart() const;
    byte* getMemEnd() const;
    byte* getCurrentPtr() const;
    byte* allocate(size_t);
    void deallocate(byte*, size_t);
    void printAllocationList() const;
    vector<MyLinkedList::Node*> getNodes() const;
};
