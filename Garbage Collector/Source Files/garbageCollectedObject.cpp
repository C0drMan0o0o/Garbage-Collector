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

//garbageCollectedObject::garbageCollectedObject(){
//    // Check if this object is within another data structure in the object graph
//    vector<garbageCollectedObject*> objects = GC::getInstance()->getObjectGraph().getObjects();
//
//    for(garbageCollectedObject* obj : objects){
//        size_t objSize = 0;
//
//        for(auto node : GC::getInstance()->getHeap()->getNodes()){
//            if(obj == (garbageCollectedObject*) node->memStart){
//                objSize = ((byte*) node->memEnd - (byte*) node->memStart);
//                cout << "objSize for " << obj << " = " << objSize << endl;
//                break;
//            }
//        }
//
//        byte* objEndMem = (byte*) obj + objSize;
//
//        if(this > obj && this < (garbageCollectedObject*) objEndMem){
//            GC::getInstance()->getObjectGraph().addEdge(obj, this);
//            this->createdWithinObject = true;
//            cout << "createdWithinObject = " << this->createdWithinObject << endl;
//            break;
//        }
//    }
//}

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
//    cout << "New object at = " << ptr << endl;
//    cout << "\ncurrent object graph:" << endl;
//    GC::getInstance()->getObjectGraph().printGraph();
//    cout << endl;
    return ptr;
}

//void* garbageCollectedObject::operator new(size_t size, void* address){
//    void* newAddress = GC::getInstance()->getHeap()->allocate(size);
//    totalSize += size;
//    GC::getInstance()->getObjectGraph().addObject((garbageCollectedObject*) newAddress);
//    cout << "(Placement New) New object at = " << newAddress << " passed address = "<< address <<endl;
//    return newAddress;
//}

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
