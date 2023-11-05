#pragma once

#include "garbageCollectedObject.hpp"
#include "MyGraph.hpp"
#include "MyLinkedList.hpp"
#include "MyStack.hpp"
#include "GC_Heap.hpp"

#include <unordered_set>

// Singleton Class
class GC {
private:
    static GC* instancePtr;
    MyGraph objectGraph;
    MyStack scopeStack;
    GC_Heap* heap = new GC_Heap(100000);
    
    GC() = default;
    GC(const GC&) = delete;
    GC& operator =(const GC&) = delete;
public:
    static unsigned long generation;
    static GC* getInstance();
    void mark(unsigned long);
    void sweep();
    bool exceedsSize(size_t);
    void enterScope();
    void exitScope();
    MyGraph& getObjectGraph();
    MyStack& getScopeStack();
    GC_Heap* getHeap();
};

#define ENTER_SCOPE GC::getInstance()->enterScope();

#define EXIT_SCOPE GC::getInstance()->exitScope();

