#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include "GC.hpp"

GC* GC::instancePtr = nullptr;

unsigned long GC::generation = 0;

GC* GC::getInstance() {
    if(instancePtr == nullptr){
        instancePtr = new GC;
        return instancePtr;
    }
    else{
        return instancePtr;
    }
}


void GC::mark(unsigned long generation) {
    for(garbageCollectedObject* obj : this->getObjectGraph().getObjects()){
        if(obj->generation >= GC::generation && obj->getRefCount() == 1){
            obj->marked = false;
        }
    }
    cout << "\nAfter Marking:" << endl;
    this->getObjectGraph().printGraph();
}

void GC::sweep() {
    // Create a set to keep track of live objects
    std::unordered_set<garbageCollectedObject*> liveObjects;

    // Mark objects as live based on reachability

    // Add live objects to the set
    for (garbageCollectedObject* obj : objectGraph.getObjects()) {
        if (obj->isReachable()) {
            liveObjects.insert(obj);
        }
    }

    // Remove unreachable objects from the object graph and deallocate their memory
    std::vector<garbageCollectedObject*> objectsToRemove;

    for (garbageCollectedObject* obj : objectGraph.getObjects()) {
        if (!liveObjects.count(obj)) {
            objectsToRemove.push_back(obj);
        }
    }

    // Remove unreachable objects from the object graph and deallocate their memory
    for (garbageCollectedObject* obj : objectsToRemove) {
        // check if the object is an array, if yes, delete it as an array, else delete it as a single object
        if(obj->isArray) {
            delete[] obj;
        }
        else {
            delete obj;
        }
    }
    cout << "\nAfter Sweeping:" << endl;
    this->getObjectGraph().printGraph();
}


bool GC::exceedsSize(size_t size){
    return garbageCollectedObject::getTotalSize() > size;
}

void GC::enterScope() {
    GC::generation++;
}

void GC::exitScope() {
    this->mark(GC::generation);
    this->sweep();
    
    GC::generation--;
}

MyGraph& GC::getObjectGraph() {return this->objectGraph;}

MyStack& GC::getScopeStack() {return this->scopeStack;}

GC_Heap* GC::getHeap() {return this->heap;}

