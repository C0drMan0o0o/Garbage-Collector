#pragma once
#include <iostream>
#include "Test.h"


struct Person : public garbageCollectedObject {
    int age;
    std::string name;
    Test* innerT;
    size_t getSize() override {return sizeof(*this);};
    Person(void* ptr) : garbageCollectedObject(ptr), innerT(new Test(this)) {}
};

