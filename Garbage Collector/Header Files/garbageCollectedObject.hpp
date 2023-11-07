#pragma once
#include <unordered_set>

class garbageCollectedObject {
    friend class GC;
public:
    bool createdWithinObject = false; // Set to true for any objects created on the heap within another object that derives from the garbageCollectedObject class
    unsigned long generation;
private:
    static size_t totalSize; // Size (in bytes) of all objects that of classes or structs that derive from this base class
    bool marked = true; // All objects are set to marked (reachable) when instantiated
    size_t size = 0; // Size (in bytes) of a single object of a class or struct that derives from this base class
    unsigned int refCount = 1;
    unsigned int getRefCount() const;
public:
    virtual size_t getSize() = 0;
    bool isReachable() const;
    static size_t getTotalSize();
    garbageCollectedObject(void*);
    virtual ~garbageCollectedObject(){}
    static void* operator new(size_t);
    void operator delete(void*, size_t);
    garbageCollectedObject* addRef();
    garbageCollectedObject* removeRef();
};
