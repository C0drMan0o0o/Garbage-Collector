#include "MyLinkedList.hpp"

using std::cout;
using std::endl;

MyLinkedList::MyLinkedList() {this->head = NULL;}

void MyLinkedList::insertAtTail(byte* memStart, byte* memEnd, bool allocated){
    Node* newNode = new Node(memStart, memEnd, allocated);
    if(head == NULL){
        head = newNode;
        tail = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
    newNode->next = NULL;
    count++;
}

vector<MyLinkedList::Node*> MyLinkedList::getNodes() const {
    vector<Node*> nodeList;
    Node* current = head;
    while(current != NULL){
        nodeList.emplace_back(current);
        current = current->next;
    }
    return nodeList;
}

bool MyLinkedList::isEmpty() const {return this->head == nullptr;}

void MyLinkedList::editNode(byte* memStart, byte* memEnd, bool changeTo) {
    Node* current = head;
    
    while (current != NULL) {
        if (current->memStart == memStart && current->memEnd == memEnd) {
            current->allocated = changeTo;
            return;  // Node found and edited, exit the loop
        }
        current = current->next;
    }
}

void MyLinkedList::print() const {
    Node* current = head;
    cout << "MyFreeList:" << endl;
    while(current != NULL){
        cout << "memStart = " << current->memStart << endl;
        cout << "memEnd = " << current->memEnd << endl;
        cout << "Allocated = " << current->allocated << endl;
        current = current->next;
        cout << endl;
    }
    delete current;
}
