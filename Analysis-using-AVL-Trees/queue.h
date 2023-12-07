
/* ----------------------------------------------------------------------------------------------------
Clase queue que sirve que sirve para crear filas

- Humberto Barrera Martínez

Fecha: 9 de noviembre del 2023
-----------------------------------------------------------------------------------------------------*/

#ifndef queue_h
#define queue_h

#include "node.h"
#include <iostream>

template <class T> class queue {

    // Atributos privados de la clase
private:
    node<T>* front;
    node<T>* back;
    int size;

    // Atributos públicos de la clase
public:
    // Constructores
    queue();
    // Destructor
    ~queue();
    // Metodos
    void push(T data);
    void pop();
    T getFront();
    T getBack();
    bool isEmpty();
    int getSize();
    void print();
};

// Constructores
template <class T> queue<T>::queue() {
    this->front = NULL;
    this->back = NULL;
    this->size = 0;
}

// Destructor
template <class T> queue<T>::~queue() {
    this->front = NULL;
    this->back = NULL;
}

// Metodos
template <class T> void queue<T>::push(T data) {
    node<T>* newNode = new node<T>(data);
    if (this->front == NULL) {
        this->front = newNode;
        this->back = newNode;
    }
    else {
        this->back->setNext(newNode);
        this->back = newNode;
    }
    this->size++;
}

template <class T> void queue<T>::pop() {
    if (this->front != NULL) {
        node<T>* aux = this->front;
        this->front = this->front->getNext();
        delete aux;
        this->size--;
    }
}

template <class T> T queue<T>::getFront() {
    if (this->front != NULL) {
        return this->front->getData();
    }
    return 0;
}

template <class T> T queue<T>::getBack() {
    if (this->back != NULL) {
        return this->back->getData();
    }
    return 0;
}

template <class T> bool queue<T>::isEmpty() { return this->front == NULL; }

template <class T> int queue<T>::getSize() { return this->size; }

template <class T> void queue<T>::print() {
    node<T>* curr = this->front;
    while (curr != NULL) {
        std::cout << curr->getData() << " ";
        curr = curr->getNext();
    }
    std::cout << std::endl;
}

#endif