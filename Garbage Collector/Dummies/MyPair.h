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
public:
    MyPair(void* ptr) : garbageCollectedObject(ptr), v1(new Vec(this)), v2(new Vec(this)) {}
    size_t getSize() override {return sizeof(*this);}
    friend inline ostream& operator <<(ostream& stream, const MyPair& myPair){
        stream << "V1:" << endl;
        stream << *myPair.v1 << endl;
        stream << "V2:" << endl;
        stream << *myPair.v2 << flush;
        return stream;
    }
};
