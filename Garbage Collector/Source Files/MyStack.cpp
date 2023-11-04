#include "MyStack.hpp"

using std::cout;
using std::endl;

MyStack::MyStack() {top = NULL;}

void MyStack::push(Scope* data){
    top = new Node(data, top);
    count++;
}

Scope* MyStack::pop(){
    if(top == NULL){
        cout << "Stack is empty!" << endl;
        return nullptr;
    }
    else{
        Scope* delData = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        count--;
        return delData;
    }
}

Scope* MyStack::peek() const {
    return top->data;
}

bool MyStack::isEmpty() const {
    return top == NULL;
}

int MyStack::getCount() const {return this->count;}

void MyStack::print() const {
    Node* current = top;
    cout << "MyStack:" << endl;
    while(current != NULL){
        cout << current->data << endl;
        current = current->next;
    }
    delete current;
}
