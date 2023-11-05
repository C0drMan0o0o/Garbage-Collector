#include <iostream>
#include "GC.hpp"
#include "garbageCollectedObject.hpp"
using std::cout;
using std::endl;
using std::ostream;
using std::byte;

bool garbageCollectedObject::isReachable() const {return this->marked;}

size_t garbageCollectedObject::totalSize = 0;

size_t garbageCollectedObject::getTotalSize(){return totalSize;}

garbageCollectedObject::garbageCollectedObject(void* parent){
    GC::getInstance()->getObjectGraph().addObject((garbageCollectedObject*) this);
    if(parent != nullptr){
        GC::getInstance()->getObjectGraph().addEdge((garbageCollectedObject*) parent, this);
        this->createdWithinObject = true;
        cout << "Added edge between two objects" << endl;
    }
    this->generation = GC::generation;
}

void* garbageCollectedObject::operator new(size_t size){
    void* ptr = GC::getInstance()->getHeap()->allocate(size);
    totalSize += size;
    GC::getInstance()->getObjectGraph().addObject((garbageCollectedObject*) ptr);
    cout << "(New) New object at = " << ptr << endl;
    return ptr;
}

void* garbageCollectedObject::operator new[](size_t size){
    // Allocate memory for the array
    void* array = GC::getInstance()->getHeap()->allocate(size);
    ((garbageCollectedObject*) array)->isArray = true;
    totalSize += size;
    GC::getInstance()->getObjectGraph().addObject((garbageCollectedObject*) array);
    std::cout << "Array address = " << array << std::endl;
    return array;
}

void garbageCollectedObject::operator delete(void* ptr, size_t size) {
    totalSize -= size;
    GC::getInstance()->getObjectGraph().removeObject((garbageCollectedObject*) ptr);
}

void garbageCollectedObject::operator delete[](void* ptr, size_t size) {
    totalSize -= size;
    GC::getInstance()->getObjectGraph().removeObject((garbageCollectedObject*) ptr, size);
}

unsigned int garbageCollectedObject::getRefCount() const {return this->refCount;}

garbageCollectedObject* garbageCollectedObject::addRef(){
    this->refCount++;
    return this;
}

garbageCollectedObject* garbageCollectedObject::removeRef(){
    this->refCount--;
    return this;
}
