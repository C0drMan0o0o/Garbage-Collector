#include "MyLinkedList.hpp"

using std::cout;
using std::endl;

MyLinkedList::MyLinkedList() {this->head = NULL;}

void MyLinkedList::insertAtTail(byte* memStart, byte* memEnd, bool allocated){
    Node* newNode = new Node(memStart, memEnd, allocated);
    if(head == NULL){
        head = newNode;
    }
    else{
        Node* current = head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }
    newNode->next = NULL;
    count++;
}

void MyLinkedList::deleteNode(byte* memStart, byte* memEnd, bool allocated) {
    if (head == NULL) {
        return;
    } else if (head->memStart == memStart && head->memEnd == memEnd && head->allocated == allocated) {
        deleteAtHead();
        count--;
        return;
    } else {
        Node* current = head;
        while (current->next != NULL) {
            if (current->next->memStart == memStart && current->next->memEnd == memEnd && current->next->allocated == allocated) {
                Node* delNode = current->next;
                current->next = current->next->next;
                delete delNode;
                count--;
                return;
            }
            current = current->next;
        }
    }
}

void MyLinkedList::deleteAtHead(){
    if(head == NULL){
        return;
    }
    else{
        Node* delNode = head;
        head = head->next;
        delete delNode;
        count--;
    }
}

vector<MyLinkedList::Node*> MyLinkedList::getNodes() const {
    vector<Node*> nodeList;
    Node* current = head;
    while(current != NULL){
        nodeList.emplace_back(current);
        current = current->next;
    }
    delete current;
    return nodeList;
}

bool MyLinkedList::isEmpty() const {return this->head == nullptr;}

int MyLinkedList::getCount() const {return this->count;}

void MyLinkedList::editNode(byte* memStart, byte* memEnd, bool changeTo) {
    Node* current = head;
    
    while (current != NULL) {
        if (current->memStart == memStart && current->memEnd == memEnd) {
            current->allocated = changeTo;
            return;  // Node found and edited, exit the loop
        }
        current = current->next;
    }

    cout << "The node you're attempting to alter was not found!" << endl;
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
