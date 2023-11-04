#pragma once
#include <iostream>
#include "Vec.h"
#include "GC.hpp"

using std::ostream;
using std::endl;
using std::flush;

struct MyPair : public garbageCollectedObject {
private:
    Vec* v1;
    Vec* v2;
//    void init(){
//        GC::getInstance()->getObjectGraph().addEdge(this, v1);
//        v1->createdWithinObject = true;
//        GC::getInstance()->getObjectGraph().addEdge(this, v2);
//        v2->createdWithinObject = true;
//    }
public:
    MyPair(){
        v1 = new Vec(0,0);
        v2 = new Vec(0,0);
//        this->init();
    }
    MyPair(Vec* v1, Vec* v2) : v1(v1), v2(v2) {
//        this->init();
    }
    size_t getSize() override {return sizeof(*this);}
    friend inline ostream& operator <<(ostream& stream, const MyPair& myPair){
        stream << "V1:" << endl;
        stream << *myPair.v1 << endl;
        stream << "V2:" << endl;
        stream << *myPair.v2 << flush;
        return stream;
    }
};
