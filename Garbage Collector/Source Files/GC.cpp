#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include "GC.hpp"

GC* GC::instancePtr = nullptr;

GC* GC::getInstance() {
    if(instancePtr == nullptr){
        instancePtr = new GC;
        return instancePtr;
    }
    else{
        return instancePtr;
    }
}

void GC::setMarkedTrue(garbageCollectedObject* ptr){ptr->marked = true;}

void GC::setMarkedFalse(garbageCollectedObject* ptr){ptr->marked = false;}

void GC::mark(Scope* scope) {
    for(garbageCollectedObject* obj : this->getObjectGraph().getObjects()){
        if((byte*) obj >= scope->getMemStart() && (byte*) obj < scope->getMemEnd() && obj->getRefCount() == 1){
            this->setMarkedFalse(obj);
        }
    }
    cout << "\nAfter Marking:" << endl;
    this->getObjectGraph().printGraph();
}

void GC::sweep(Scope* scope) {
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
    Scope* scope = new Scope(this->getHeap()->getCurrentPtr());
    this->getScopeStack().push(scope);
}

void GC::exitScope() {
    Scope* currentScope = this->getScopeStack().pop();
    currentScope->setMemEnd(this->getHeap()->getCurrentPtr());
    
    this->mark(currentScope);
    this->sweep(currentScope);
    
    delete currentScope;
}

MyGraph& GC::getObjectGraph() {return this->objectGraph;}

MyStack& GC::getScopeStack() {return this->scopeStack;}

GC_Heap* GC::getHeap() {return this->heap;}

