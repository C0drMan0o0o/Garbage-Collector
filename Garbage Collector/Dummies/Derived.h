#pragma once
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include "garbageCollectedObject.hpp"

struct Derived : public garbageCollectedObject {
    int num;
    
    size_t getSize() override {return sizeof(*this);}
    Derived(int num = 0) : num(num) {cout << "Derived object with num = " << this->num << " allocated" << endl;}
    ~Derived(){cout << "Derived object with num = " << this->num << " deallocated" << endl;}
    
    friend ostream& operator <<(ostream& stream, const Derived& d){
        return stream << "Num = " << d.num << flush;
    }
};
