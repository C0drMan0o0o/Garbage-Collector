#pragma once
#include <iostream>
#include "Test.h"


struct Person : public garbageCollectedObject {
    int age;
    std::string name;
    Test* innerT = new Test;
    size_t getSize() override {return sizeof(*this);};
//    Person(){
//        GC::getInstance()->getObjectGraph().addEdge(this, innerT);
//        innerT->createdWithinObject = true;
//    }
};

