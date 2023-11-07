#pragma once

#include "garbageCollectedObject.hpp"
#include "MyGraph.hpp"
#include "MyLinkedList.hpp"
#include "GC_Heap.hpp"

#include <unordered_set>

// Singleton Class
class GC {
private:
    static GC* instancePtr;
    MyGraph objectGraph;
    GC_Heap* heap = new GC_Heap(100000);
    
    GC() = default;
    GC(const GC&) = delete;
    GC& operator =(const GC&) = delete;
public:
    static unsigned long generation;
    static GC* getInstance();
    void mark(unsigned long);
    void sweep();
    void enterScope();
    void exitScope();
    MyGraph& getObjectGraph();
    GC_Heap* getHeap();
};

#define ENTER_SCOPE GC::getInstance()->enterScope();

#define EXIT_SCOPE GC::getInstance()->exitScope();

template <typename T>
T* createArray(void* base, size_t numOfElements) {
    // Allocate memory for the array
    T* array = (T*) GC::getInstance()->getHeap()->allocate(numOfElements * sizeof(T));
    std::cout << "Array address = " << array << std::endl;

    // Initialise each element in the array using the default constructor of the templated object
    for (size_t i=0;i<numOfElements;i++) {
        GC::getInstance()->getObjectGraph().addObject((garbageCollectedObject*) (array + i));
        ::new (array + i) T(base);
        std::cout << "element address = " << &array[i] << std::endl;
    }

    return array;
}
