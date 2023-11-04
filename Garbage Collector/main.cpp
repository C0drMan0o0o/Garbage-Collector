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

inline void run();

inline void useCase1();

inline void useCase2();

GC* gc = GC::getInstance();

//void test(){
//    char array[10000];
//
//    for(int i=0;i<10000;i++){
//        array[i] = 0;
//    }
//    cout << "Address of char array = " << &array << endl;
//}
//
//Vec* getArray(){
//    Vec* array = createArray<Vec>(3);
//    for(int i=0;i<3;i++){
//        array[i] = {(float) i+100, (float) i+100};
//    }
//    return array;
//}
//
//int main(){
//    int length = 3;
//    Vec* vecArray = createArray<Vec>(length);
//
//    for(int i=0;i<length;i++){
//        cout << vecArray[i] << endl;
//    }
//
//    for(int i=0;i<length;i++){
//        vecArray[i] = {(float) i+1, (float) i+1};
//    }
//
//    for(int i=0;i<length;i++){
//        cout << vecArray[i] << endl;
//    }
//
//    Vec* testArray = getArray();
//    cout << "Address of testArray = " << testArray << endl;
//
//    test();
//
//    cout << endl;
//    for(int i=0;i<3;i++){
//        cout << testArray[i] << endl;
//    }
//}

//inline void testCase(){
//    Vec* array = createArray<Vec>(1);
//    process(array);
//    cout << "\nObject Graph:" << endl;
//    GC::getInstance()->getObjectGraph().printGraph();
//}

//int main(){
//    ENTER_SCOPE
//    size_t length = 3;
////    Vec* v = createArray<Vec>(length);
//    Vec* v = new Vec[length];
//
//    cout << endl;
//    for(int i=0;i<length;i++){
//        cout << "Address of v[" << i << "] = " << v+i << endl;
//    }
//    cout << endl;
//
//    for(int i=0;i<length;i++){
//        cout << v[i] << endl;
//    }
//
//    for(int i=0;i<length;i++){
//        v[i] = {(float) i+1, (float) i+1};
//    }
//
//    for(int i=0;i<length;i++){
//        cout << v[i] << endl;
//    }
//
//    GC::getInstance()->getHeap()->printFreeList();
//
////    useCase2();
//    EXIT_SCOPE
//}

struct innerStruct : public garbageCollectedObject {
    size_t getSize() override {return sizeof(*this);}
};

struct myStruct : public garbageCollectedObject {
    innerStruct* inner1 = new innerStruct;
    innerStruct* inner2 = new innerStruct;
    innerStruct* inner3 = new innerStruct;
    size_t getSize() override {return sizeof(*this);}
};

int main(){
    ENTER_SCOPE
    for(int i=0;i<3;i++){
        Test* t = new Test;
        process(t);
    }
    EXIT_SCOPE
    

//    useCase1();
}

void process(garbageCollectedObject*){}

inline void run(){
    cout << "Size of each object of Vec = " << sizeof(Vec) << " bytes" << "\n" << endl;
    for(int i=0;i<8;i++){
        ENTER_SCOPE
        Vec* v = new Vec;
        process(v);
        gc->getObjectGraph().printGraph();
        cout << "Total Size = " << garbageCollectedObject::getTotalSize() << " bytes" << endl;
        cout << endl;
        EXIT_SCOPE
    }
    cout << "\nFinal Total Size = " << garbageCollectedObject::getTotalSize() << " bytes" << endl;
}

inline void useCase1(){
    ENTER_SCOPE
    cout << "Size of each object of Vec = " << sizeof(Vec) << " bytes" << "\n" << endl;
    Vec* v1 = new Vec;
    process(v1);
    Vec* survivor = nullptr;
    ENTER_SCOPE
    for(int i=2;i<=4;i++){
        Vec* v = new Vec;
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
    ENTER_SCOPE
    int length = 5;
    MyPair* MyPairArray = createArray<MyPair>(length);
    cout << "MyPair array = " << &MyPairArray << endl;
    process(MyPairArray);
    EXIT_SCOPE
}

