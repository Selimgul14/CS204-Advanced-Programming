#ifndef DYNQUEUE_H
#define DYNQUEUE_H

//Created by Selim Gul 29200


#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <typeinfo> //to decide whether the type is integer, string or char
using namespace std;

template <typename T>
struct QueueNode { // this is the basic node for DynQueue
    T value;
    QueueNode* next;
    QueueNode() {}
    QueueNode(T num, QueueNode* ptr = NULL) {
        value = num;
        next = ptr;
    }   
};

template <class T> //class and some of the functions are declared to state that they are template functions
class DynQueue;

template <class T>
ostream& operator << (ostream& os, DynQueue<T>&);


template <class T>
istream& operator >> (istream& is, DynQueue<T>& val);


template <class T>
DynQueue<T> operator + (const DynQueue<T>& q1, const DynQueue<T>& q2);



template <class T>
class DynQueue {
private:
    QueueNode<T>* front; //head of the queue
    QueueNode<T>* rear; //tail of the queue
    T value; //value stored in queue nodes
public:
    DynQueue(void); //default constructor
    DynQueue(const DynQueue&); //deep copy constructor
    ~DynQueue(); //destructor
    void enqueue(T); 
    void dequeue(T&);
    bool isEmpty(void) const;
    void clear(void);
    const DynQueue& operator = (const DynQueue&);
    QueueNode<T>* createClone() const;
    const DynQueue& operator *= (T);
    const DynQueue& operator += (T);

    friend DynQueue operator + <>(const DynQueue& q1, const DynQueue& q2);
    friend istream& operator >> <>(istream& is, DynQueue& val);
    friend ostream& operator << <>(ostream& os, DynQueue<T>& val);

};


template <class T>
DynQueue<T>::DynQueue() {
    front = NULL;
    rear = NULL;
}

template <class T>
QueueNode<T>* DynQueue<T>::createClone() const { //this is a modified version of the function from DynIntQueue.cpp, clones the nodes and return the nodes, performing deep copy
    if (front == NULL) { //if the queue is empty, it returns empty
        return NULL;
    }
    QueueNode<T>* headClone = new QueueNode<T>(front->value, NULL); //if it is not empty, creates a new node that's value is equal to head's value and points to null
    QueueNode<T>* ptr = front->next; //creates a new node that points to
    QueueNode<T>* ptrClone = headClone; 
    while (ptr != NULL) { //while it reach to end of the queue
        ptrClone->next = new QueueNode<T>(ptr->value, NULL); //copy next node with cloning its value
        ptr = ptr->next; //iterate to next node
        ptrClone = ptrClone->next; 
    }
    return headClone;
}

template <class T> //deep copy consturctor using the createClone function
DynQueue<T>::DynQueue(const DynQueue& copy) {
    front = copy.createClone();

}

template <class T>
void DynQueue<T>::enqueue(T num) {
    if (isEmpty()) { //if the queue is empty already 
        front = new QueueNode<T>(num); //it creates a new node
        rear = front; //make head equal to tail
    }
    else {
        rear->next = new QueueNode<T>(num); //it creates a new node
        rear = rear->next; //continue from tail
    }
}

template <class T>
void DynQueue<T>::dequeue(T& num) {
    QueueNode<T>* temp;
    if (isEmpty()) { //if the queue is empty already 
        exit(1); //exit without executing operation
    }
    else {
        num = front->value; //make the heads value equal to reference parameter 
        temp = front; //create a temporary node
        front = front->next; //iterate front to the next node to not lose track of head
        delete temp; //delete the temporary node which was the head node
    }
}

template <class T>
bool DynQueue<T>::isEmpty(void) const { //check if the queue is empty
    if (front == NULL) {
        return true; //if the queue is empty, return true
    }
    else {
        return false; //if queue is not empty, return false
    }
}

template <class T>
void DynQueue<T>::clear(void) { //clear the queue using dequeue function
    T value;
    while (!isEmpty()) { //perform dequeue operation until the queue is emptied
        dequeue(value);
    }
}

template <class T>
const DynQueue<T>& DynQueue<T>::operator = (const DynQueue<T>& copy) { //overloading the assingment operator the perform deep copy operation
    DynQueue tmp(copy); //call the deep copy constructor
    T value;
    if (&copy != this) {
        while (!isEmpty()) {
            dequeue(value);
        }
        while (!tmp.isEmpty()) {
            tmp.dequeue(value);
            enqueue(value);
        }
    }
    return *this; //return queue
}

template <class T> //destructor
DynQueue<T>::~DynQueue() {
    QueueNode<T>* temp; //create a temporary node to not lose the track of head
    while (front != NULL) { //until it is fully deleted
        temp = front; //set the temporary node equal to head node
        front = front->next; //move head node to next node
        delete temp; //delete the temporary node
    }
}

template <class T>
istream& operator >> (istream& is, DynQueue<T>& val) { //overloading the >> operator
    T temp;
    while (!is.eof()) { //until end of the file has reached
        is >> temp; //read the values into temp
        val.enqueue(temp); //push temp into queue
    }
    return is;
}

template <class T>
ostream& operator << (ostream& os, DynQueue<T>& val) { //overloading the << operator
    T value;
    DynQueue<T> temp;
    while (!val.isEmpty()) { 
        val.dequeue(value); //dequeue all the values until the queue is emptied
        os << value << " "; //print the dequeued values
        temp.enqueue(value); //push the dequeued values into temporary queue
    }
    while (!temp.isEmpty()) {
        temp.dequeue(value); //dequeue all values from temporary
        val.enqueue(value); //and push back to original queue
    }
    return os;
}

template <class T>
DynQueue<T> operator + (DynQueue<T>& q1, DynQueue<T>& q2) { //overloading the + operator
    DynQueue<T> q3, tmp1, tmp2;
    T value1, value2, summed;
    while (!q1.isEmpty()) { //assuming that both queues will have same amount of elements
        q1.dequeue(value1); //dequeue values
        q2.dequeue(value2);
        summed = value1 + value2; //sum the values
        q3.enqueue(summed); //push the values to the requested queue
        tmp1.enqueue(value1); //push values back to temporary queue
        tmp2.enqueue(value2);
    }
    while (!tmp1.isEmpty()) {
        tmp1.dequeue(value1); //dequeue temporary queues
        tmp2.dequeue(value2);
        q1.enqueue(value1); //push the values back to originial queues
        q2.enqueue(value2);
    }
    return q3; //this should return the queue but I wasn't able to return it...
}

template <class T>
const DynQueue<T>& DynQueue<T>::operator += (T num) { //overloading of the += operator
    enqueue(num); //push the requested item typed T with enqueue function
    return *this; //return the queue
}

template <class T>
const DynQueue<T>& DynQueue<T>::operator *= (T num) { //overloading the operator *=
    int i, j;
    string s;
    char c;
    j = num;
    if (typeid(num) == typeid(i)) { //if the type of values inside the queue is integer
        DynQueue<T> tmp;
        T value;
        while (!isEmpty()) { //until the original queue is emptied
            dequeue(value); //dequeue the values
            value = value * num; //multiply the values with requested number
            tmp.enqueue(value); //pust the values to temporary queue
        }
        while (!tmp.isEmpty()) { //until the temporary queue is emptied
            tmp.dequeue(value); //dequeue the values
            enqueue(value); //push the values back to original queue
        }
        return *this;
    }
    if (typeid(num) == typeid(s) || typeid(num) == typeid(c)) { //if the type of values inside the queue is char or string
        DynQueue<T> tmp;
        T value;
        while (!isEmpty()) {
            dequeue(value); //dequeue the values
            for (int k = 0; k < j; k++) {
                tmp.enqueue(value); //push the values inside the temporary queue, but push the same values as the same amount of the right hand operand
            }
        }
        while (!tmp.isEmpty()) { //until the temporary queue is emptied
            tmp.dequeue(value); //dequeue the values
            enqueue(value); //push the values back to original queue
        }
        return *this;
    }
    return *this;
}
#endif
