#include "GC_Heap.hpp"

#include "GC.hpp"

using std::cout;
using std::endl;

GC_Heap::GC_Heap(size_t size) : size(size) {
    memStart = static_cast<byte*>(std::malloc(size));
    if (memStart == nullptr) {
        std::cerr << "Failed to initialise GC heap. Out of memory." << std::endl;
        std::exit(1); // Terminate the program due to memory allocation failure
    }
    currentPtr = memStart;
}

byte* GC_Heap::getMemStart() const {return this->memStart;}

byte* GC_Heap::getMemEnd() const {return this->memStart + this->size;}

byte* GC_Heap::getCurrentPtr() const {return this->currentPtr;}

byte* GC_Heap::allocate(size_t allocationSize) {
    if (!freeList.isEmpty()) {
        // Iterate through nodes in freeList to find a suitable free block.
        for (const auto* node : freeList.getNodes()) {
            if (!node->allocated && node->memEnd - node->memStart >= allocationSize) {
                // Found a suitable block in the free list.
                byte* allocationAddress = node->memStart;

                // Mark the block as allocated.
                freeList.editNode(node->memStart, node->memEnd, true);

                // Check if we can split the block into two (part for the allocation, part remains free).
                if (node->memEnd - allocationAddress > allocationSize) {
                    byte* newFreeBlockPtr = allocationAddress + allocationSize;
                    freeList.insertAtTail(newFreeBlockPtr, node->memEnd, false); // Mark as free
                }

                // Update currentPtr to point to the end of the allocated object.
                currentPtr = allocationAddress + allocationSize;

                return allocationAddress;
            }
        }
    }

    // If no suitable block is found in freeList, create a new node.
    if (allocationSize <= size - (currentPtr - memStart)) {
        byte* allocationAddress = currentPtr;
        currentPtr += allocationSize;

        freeList.insertAtTail(allocationAddress, allocationAddress + allocationSize, true);

        return allocationAddress;
    }

    // If there is not enough memory, handle the out-of-memory condition.
    std::cerr << "Out of memory in GC heap." << std::endl;
    std::exit(1); // Terminate the program gracefully due to heap overflow
}

void GC_Heap::deallocate(byte* ptr, size_t deallocationSize) {
    // Add the deallocated block back to the free list.
    freeList.editNode(ptr, ptr + deallocationSize, false);

    // currentPtr is placed at the beginning of the address where the most recent object was deallocated
    if (ptr < currentPtr) {
        currentPtr = ptr;
    }
}

void GC_Heap::printFreeList() const {this->freeList.print();}

vector<MyLinkedList::Node*> GC_Heap::getNodes() const {
    return this->freeList.getNodes();
}
