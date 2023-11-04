#pragma once
#include <iostream>
#include "Person.h"

struct Animal : public garbageCollectedObject {
    int age;
    std::string name;
    Person* innerP = new Person;
    size_t getSize() override {return sizeof(*this);};
//    Animal(){
//        GC::getInstance()->getObjectGraph().addEdge(this, innerP);
//        innerP->createdWithinObject = true;
//    }
};

