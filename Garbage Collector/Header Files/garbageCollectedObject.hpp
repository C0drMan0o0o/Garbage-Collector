#pragma once
#include <unordered_set>

class garbageCollectedObject {
    friend class GC;
    template<typename T>
    friend T* createArray(size_t);
public:
    bool createdWithinObject = false; // Set to true for any objects created on the heap within another object that derives from the garbageCollectedObject class
private:
    static size_t totalSize; // Size (in bytes) of all objects that of classes or structs that derive from this base class
    bool marked = true; // All objects are set to marked (reachable) when instantiated
    bool isArray = false; // Set to true if object is an array
    size_t size = 0; // Size (in bytes) of a single object of a class or struct that derives from this base class
    unsigned int refCount = 1;
    unsigned int getRefCount() const;
public:
    virtual size_t getSize() = 0;
    bool isReachable() const;
    static size_t getTotalSize();
    garbageCollectedObject();
    virtual ~garbageCollectedObject(){}
    static void* operator new(size_t);
    static void* operator new[](size_t);
//    static void* operator new(size_t, void*); // Placement new operator
    void operator delete(void*, size_t);
    void operator delete[](void*, size_t);
    garbageCollectedObject* addRef();
    garbageCollectedObject* removeRef();
};

template <typename T>
T* createArray(size_t numOfElements) {
    // Allocate memory for the array
    T* array = (T*) malloc(sizeof(T) * numOfElements);
    std::cout << "Array address = " << array << std::endl;

    // Initialise each element in the array using the default constructor of the templated object
    for (size_t i=0;i<numOfElements;i++) {
        ::new (array + i) T;
//        array[i] = T();
        std::cout << "element address = " << &array[i] << std::endl;
    }

    return array;
}

// Templated method to create an array of a derived class of garbageCollectedObject
// This method is defined in the header file instead of the source file because it is a templated method and will only work if this is done
//template <typename T>
//T* createArray(size_t numOfElements) {
//    // Allocate memory for the array
//    T* array =  new T;
//
//    for (size_t i = 1; i < numOfElements; i++) {
//        // Use placement new to construct objects in the allocated memory
//        ::new (&array[i]) T;
//    }
//
//    return array;
//}
