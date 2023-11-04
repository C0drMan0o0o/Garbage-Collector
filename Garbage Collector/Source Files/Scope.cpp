#include "Scope.hpp"

Scope::Scope(byte* memStart) : memStart(memStart) {}

byte* Scope::getMemStart() const {return this->memStart;}

byte* Scope::getMemEnd() const {return this->memEnd;}

size_t Scope::getSize() const {return this->memEnd - this->memStart;}

void Scope::setMemEnd(byte* memEnd) {this->memEnd = memEnd;}

bool Scope::checkScope(byte* ptr) const {
    return (ptr >= this->memStart || ptr <= this->memEnd);
}
