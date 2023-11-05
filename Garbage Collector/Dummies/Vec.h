#pragma once
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include "garbageCollectedObject.hpp"

class Vec : public garbageCollectedObject {
private:
    float f1, f2;
public:
    Vec(void* parent) : garbageCollectedObject(parent), f1(0), f2(0) {cout << "Default Vec Constructor Called" << endl;}

    Vec(void* parent, float f1, float f2) : garbageCollectedObject(parent), f1(f1), f2(f2) {cout << "Vec Constructor Called" << endl;}
    
    Vec(void* parent, const Vec& v) : garbageCollectedObject(parent) {cout << "Copy Constructor Called!" << endl;}
    
    size_t getSize() override {return sizeof(*this);}
    
    friend inline ostream& operator <<(ostream& stream, const Vec& v){
        stream << "f1 - " << v.f1 << endl;
        stream << "f2 - " << v.f2 << endl;
        return stream;
    }
};
