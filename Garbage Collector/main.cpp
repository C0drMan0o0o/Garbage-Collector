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

inline void useCase6();

inline void useCase7();

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
    useCase7();
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

// Test to see that object is not deallocated if it is being referenced elsewhere outside the scope it was created in
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

// Test to see that marking and sweeping works for objects with multiple objects created within them
inline void useCase2(){
    for(int i=0;i<3;i++){
        ENTER_SCOPE
        myStruct* t = new myStruct(nullptr);
        process(t);
        EXIT_SCOPE
    }
}

// Test to see that marking and sweeping works for an array of given length
inline void useCase3(){
    ENTER_SCOPE
    Vec* vecArray = createArray<Vec>(nullptr, 5);
    process(vecArray);
    EXIT_SCOPE
}

// Test to see that marking and sweeping works for an array of given length in which each element has other objects within it
inline void useCase4(){
    ENTER_SCOPE
    int length = 5;
    MyPair* MyPairArray = createArray<MyPair>(nullptr, length);
    process(MyPairArray);
    EXIT_SCOPE
}

// Test to see that marking and sweeping works for an object which has an array within it which will be created with a given length
inline void useCase5(){
    ENTER_SCOPE
    testStruct* testStructObj = new testStruct(nullptr, 5);
    process(testStructObj);
    EXIT_SCOPE
}

// Test to see that only heap allocated objects are marked and sweeped
inline void useCase6(){
    ENTER_SCOPE
    Vec* heapAllocated = new Vec(nullptr, 1.3, 2.3);
    process(heapAllocated);
    Vec stackAllocated(nullptr, 1.2, 2.3);
    EXIT_SCOPE
}

// Test to see that an array is not deallocated if it is being referenced elsewhere outside the scope it was created in
inline void useCase7(){
    ENTER_SCOPE
    Vec* survivor = nullptr;

    auto lambda = [&](){
        ENTER_SCOPE
        Vec* vecArray = createArray<Vec>(nullptr, 3);
        survivor = vecArray;
        for(Vec* ptr = vecArray; ptr<vecArray+3; ptr++){
            ptr->addRef();
        }
        EXIT_SCOPE
    };

    lambda();

    for(Vec* ptr = survivor; ptr<survivor+3; ptr++){
        ptr->removeRef();
    }
    EXIT_SCOPE
}
