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

inline void demo();

inline void useCase1();

inline void useCase2();

inline void useCase3();

inline void useCase4();

inline void useCase5();

GC* gc = GC::getInstance();

struct innerStruct : public garbageCollectedObject {
    innerStruct(void *ptr) : garbageCollectedObject(ptr) {}
    size_t getSize() override {return sizeof(*this);}
};

struct myStruct : public garbageCollectedObject {
    innerStruct* inner1;
    innerStruct* inner2;
    innerStruct* inner3;
    myStruct(void* ptr) : garbageCollectedObject(ptr), inner1(new innerStruct(this)), inner2(new innerStruct(this)), inner3(new innerStruct(this)) {}
    size_t getSize() override {return sizeof(*this);}
};

struct testStruct : public garbageCollectedObject {
    int length;
    Vec* innerVecArray;
    testStruct(void* ptr, int length) : garbageCollectedObject(ptr), length(length), innerVecArray(createArray<Vec>(this, length)) {}
    size_t getSize() override {return sizeof(*this);}
};

int main(){
    demo();
}

void process(garbageCollectedObject*){}

inline void demo(){
    cout << "Size of each object of Vec = " << sizeof(Vec) << " bytes" << "\n" << endl;
    for(int i=0;i<3;i++){
        ENTER_SCOPE
        Vec* v = new Vec(nullptr);
        process(v);
        gc->getObjectGraph().printGraph();
        cout << "Total Size Before Sweeping = " << garbageCollectedObject::getTotalSize() << " bytes" << endl;
        cout << endl;
        EXIT_SCOPE
        cout << "Total Size After Sweeping = " << garbageCollectedObject::getTotalSize() << " bytes" << endl;
        cout << "==================================================="<<endl;
    }
    cout << "\nFinal Total Size = " << garbageCollectedObject::getTotalSize() << " bytes" << endl;
}

inline void useCase1(){
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

inline void useCase2(){
    for(int i=0;i<3;i++){
        ENTER_SCOPE
        myStruct* t = new myStruct(nullptr);
        process(t);
        EXIT_SCOPE
    }
}

inline void useCase3(){
    ENTER_SCOPE
    Vec* vecArray = createArray<Vec>(nullptr, 5);
    process(vecArray);
    EXIT_SCOPE
}

inline void useCase4(){
    ENTER_SCOPE
    int length = 5;
    MyPair* MyPairArray = createArray<MyPair>(nullptr, length);
    process(MyPairArray);
    EXIT_SCOPE
}

inline void useCase5(){
    ENTER_SCOPE
    testStruct* testStructObj = new testStruct(nullptr, 5);
    process(testStructObj);
    EXIT_SCOPE
}
