#pragma once
#include <iostream>
#include <vector>
#include "Vec.h"
#include "GC.hpp"

struct Test : public garbageCollectedObject {
private:
    std::vector<int> myVector;
    Vec* innerV = new Vec;
public:
//    Test(){
//        GC::getInstance()->getObjectGraph().addEdge(this, innerV);
//        innerV->createdWithinObject = true;
//    }
    size_t getSize() override {return sizeof(*this);}
};

