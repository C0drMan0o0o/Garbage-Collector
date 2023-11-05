#include <iostream>
#include "Dummies/Animal.h"
#include "Dummies/Person.h"
#include "Dummies/Test.h"
#include "Dummies/Vec.h"
#include "Dummies/MyPair.h"
#include "Dummies/Derived.h"
#include "Header Files/GC.hpp"
#include <vector>

using std::cout;
using std::endl;

void process(garbageCollectedObject*);

static vector<garbageCollectedObject*> myVector;

GC* gc = GC::getInstance();

int main(){
    ENTER_SCOPE
    cout << "Size of each object of Vec = " << sizeof(Vec) << " bytes" << "\n" << endl;
    Vec* v1 = new Vec(nullptr);
    process(v1);
    Vec* survivor = nullptr;
    ENTER_SCOPE
    for(int i=2;i<=4;i++){
        Vec* v = new Vec(nullptr);
        process(v);
        if(i == 2){
            myVector.emplace_back(v->addRef());
            survivor = v;
        }
    }
    cout << "Before Garbage Collection:" << endl;
    GC::getInstance()->getObjectGraph().printGraph();
    cout << "\nGarbage Collection Begins:" << endl;
    EXIT_SCOPE
    std::remove(myVector.begin(), myVector.end(), survivor->removeRef());
    EXIT_SCOPE
}

void process(garbageCollectedObject*){}
