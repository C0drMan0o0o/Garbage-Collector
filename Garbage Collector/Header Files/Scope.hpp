#pragma once
#include <iostream>

using std::byte;

class Scope {
private:
    byte* memStart;
    byte* memEnd;
public:
    Scope(byte*);
    byte* getMemStart() const;
    byte* getMemEnd() const;
    size_t getSize() const;
    void setMemEnd(byte*);
    bool checkScope(byte*) const;
};
