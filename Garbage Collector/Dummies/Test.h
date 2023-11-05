#pragma once
#include <iostream>
#include <vector>
#include "Vec.h"
#include "GC.hpp"

struct Test : public garbageCollectedObject {
private:
    std::vector<int> myVector;
    Vec* innerV;
public:
    Test(void* ptr) : garbageCollectedObject(ptr), innerV(new Vec(this)) {}
    size_t getSize() override {return sizeof(*this);}
};

