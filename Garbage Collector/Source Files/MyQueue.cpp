#include "MyQueue.hpp"

using std::cout;
using std::endl;

MyQueue::MyQueue(){
    front = NULL;
    rear = NULL;
}

void MyQueue::enqueue(garbageCollectedObject* data){
    Node* newNode = new Node(data);
    if(front == NULL){
        front = newNode;
        rear = newNode;
    }
    else{
        rear->next = newNode;
        rear = newNode;
    }
    count++;
}

garbageCollectedObject* MyQueue::dequeue(){
    if(front == NULL){
        cout << "Queue is already empty, can't dequeue!" << endl;
        return NULL;
    }
    else{
        Node* delNode = front;
        garbageCollectedObject* delData = delNode->data;
        front = front->next;
        delete delNode;
        count--;
        return delData;
    }
}

garbageCollectedObject* MyQueue::peek() const {
    if(front == NULL){
        cout << "Queue is empty!" << endl;
        return nullptr;
    }
    else{
        return front->data;
    }
}

int MyQueue::getCount() const {return this->count;}

bool MyQueue::isEmpty() const {
    return front == NULL;
}

void MyQueue::print() const {
    Node* current = front;
    cout << "MyQueue:" << endl;
    while(current != NULL){
        cout << current->data << endl;
        current = current->next;
    }
    delete current;
}

