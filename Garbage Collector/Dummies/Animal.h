#pragma once
#include <iostream>
#include "Person.h"

struct Animal : public garbageCollectedObject {
    int age;
    std::string name;
    Person* innerP;
    size_t getSize() override {return sizeof(*this);};
    Animal(void* ptr) : garbageCollectedObject(ptr), innerP(new Person(this)) {}
};

