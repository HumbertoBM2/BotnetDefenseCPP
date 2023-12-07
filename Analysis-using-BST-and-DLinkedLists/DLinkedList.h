/*
------------------------------------------------------------------------------------------------------
Clase DLinkedList que sirve para manejar listas doblemente ligadas

- Humberto Barrera Martínez

Fecha: 15 de octubre del 2023
------------------------------------------------------------------------------------------------------
*/

#ifndef DLinkedList_h
#define DLinkedList_h

#include "Node.h"
#include "accesoFallido.h"
#include <bits/stdc++.h>

using namespace std;

template <class T> class DLinkedList {

private:
    /// Atributos privados de la clase
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    // Constructores
    DLinkedList();
    DLinkedList(T data);
    // Destructor
    ~DLinkedList();
    // Getters
    Node<T>* getHead();
    Node<T>* getElementAt(int index);
    int getSize();
    // Setters
    void setHead(Node<T>* head);
    void setSize(int size);
    // Métodos
    void first();
    void addFirst(T data);
    void addLast(T data);
    void addAt(int index, T data);
    void deleteFirst();
    void deleteLast();
    bool isEmpty() const;
    void deleteAt(int index);
    void print();
    void readAt(int index);
    T operator[](int index);
    void update(int index, T data);
    void clear();
    void printToFile(string fileName);
};

// Constructores
template <class T> DLinkedList<T>::DLinkedList() {
    this->head = nullptr;
    this->size = 0;
}

template <class T> DLinkedList<T>::DLinkedList(T data) {
    this->head = new Node<T>(data);
    this->size = 1;
}

// Destructor
template <class T> DLinkedList<T>::~DLinkedList() {
    Node<T>* current = this->head;
    Node<T>* next;
    while (current != nullptr) {
        next = current->getNext();
        delete current;
        current = next;
    }
}

// Getters
template <class T> Node<T>* DLinkedList<T>::getHead() { return this->head; }

template <class T> Node<T>* DLinkedList<T>::getElementAt(int index) {
    if (index < 0 || index >= this->size) {
        cout << "Indice invalido" << endl;
        return nullptr;
    }
    Node<T>* current = this->head;
    for (int i = 0; i < index; i++) {
        current = current->getNext();
    }
    return current;
}

template <class T> int DLinkedList<T>::getSize() { return this->size; }

// Setters
template <class T> void DLinkedList<T>::setHead(Node<T>* head) {
    this->head = head;
}

template <class T> void DLinkedList<T>::setSize(int size) { this->size = size; }

// Métodos

// Metodo para imprimir el primer elemento de la lista
// Complejidad: O(1)
template <class T> void DLinkedList<T>::first() {
    if (this->head == nullptr) {
        cout << "La lista esta vacia" << endl;
        return;
    }
    cout << this->head->getData() << endl;
}

// Metodo para agregar un elemento al inicio de la lista
// Complejidad: O(1)
template <class T> void DLinkedList<T>::addFirst(T data) {
    Node<T>* newNode = new Node<T>(data);
    newNode->setNext(this->head);
    this->head = newNode;
    this->size++;
}

// Metodo para agregar un elemento al final de la lista
// Complejidad: O(n)
template <class T> void DLinkedList<T>::addLast(T data) {
    Node<T>* newNode = new Node<T>(data);
    if (this->head == nullptr) {
        this->head = newNode;
    }
    else {
        Node<T>* current = this->head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(newNode);
    }
    this->size++;
}

// Metodo para agregar un elemento en una posicion especifica de la lista
// Complejidad: O(n)
template <class T> void DLinkedList<T>::addAt(int index, T data) {
    if (index < 0 || index > this->size) {
        cout << "Indice invalido" << endl;
        return;
    }
    if (index == 0) {
        this->addFirst(data);
        return;
    }
    if (index == this->size) {
        this->addLast(data);
        return;
    }
    Node<T>* newNode = new Node<T>(data);
    Node<T>* current = this->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->getNext();
    }
    newNode->setNext(current->getNext());
    current->setNext(newNode);
    this->size++;
}

// Metodo para eliminar el primer elemento de la lista
// Complejidad: O(1)
template <class T> void DLinkedList<T>::deleteFirst() {
    if (this->head == nullptr) {
        cout << "La lista esta vacia" << endl;
        return;
    }
    Node<T>* current = this->head;
    this->head = current->getNext();
    delete current;
    this->size--;
}

// Metodo para eliminar el ultimo elemento de la lista
// Complejidad: O(n)
template <class T> void DLinkedList<T>::deleteLast() {
    if (this->head == nullptr) {
        cout << "La lista esta vacia" << endl;
        return;
    }
    if (this->head->getNext() == nullptr) {
        delete this->head;
        this->head = nullptr;
        this->size--;
        return;
    }
    Node<T>* current = this->head;
    while (current->getNext()->getNext() != nullptr) {
        current = current->getNext();
    }
    delete current->getNext();
    current->setNext(nullptr);
    this->size--;
}

// Metodo para eliminar un elemento en una posicion especifica de la lista
// Complejidad: O(n)
template <class T> void DLinkedList<T>::deleteAt(int index) {
    if (index < 0 || index >= this->size) {
        cout << "Indice invalido" << endl;
        return;
    }
    if (index == 0) {
        this->deleteFirst();
        return;
    }
    if (index == this->size - 1) {
        this->deleteLast();
        return;
    }
    Node<T>* current = this->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->getNext();
    }
    Node<T>* toDelete = current->getNext();
    current->setNext(toDelete->getNext());
    delete toDelete;
    this->size--;
}

// Metodo para verificar si la lista esta vacia
// Complejidad: O(n)
template <typename T> bool DLinkedList<T>::isEmpty() const {
    return head == nullptr;
}

// Metodo para imprimir los elementos de la lista
// Complejidad: O(n)
template <class T> void DLinkedList<T>::print() {
    Node<T>* current = this->head;
    while (current != nullptr) {
        if (typeid(current->getData()) == typeid(accesoFallido)) {
            cout << current->getData().getMesString() << " ";
            cout << current->getData().getDia() << " ";
            cout << current->getData().getHora() << " ";
            cout << current->getData().getIp() << " ";
            cout << current->getData().getRazon() << " ";
            cout << endl;
            current = current->getNext();
        }
    }
    cout << endl;
}

// Metodo para imprimir el elemento en una posicion especifica de la lista
// Complejidad: O(n)
template <class T> void DLinkedList<T>::readAt(int index) {
    if (index < 0 || index >= this->size) {
        cout << "Indice invalido" << endl;
        return;
    }
    cout << this->getElementAt(index)->getData() << endl;
}

// Metodo para sobrecargar el operador []
// Complejidad: O(n)
template <class T> T DLinkedList<T>::operator[](int index) {
    return this->getElementAt(index)->getData();
}

// Metodo para actualizar el elemento en una posicion especifica de la lista
// Complejidad: O(n)
template <class T> void DLinkedList<T>::update(int index, T data) {
    this->getElementAt(index)->setData(data);
}

// Metodo para eliminar todos los elementos de la lista
// Complejidad: O(n)
template <class T> void DLinkedList<T>::clear() {
    Node<T>* current = this->head;
    Node<T>* next;
    while (current != nullptr) {
        next = current->getNext();
        delete current;
        current = next;
    }
    this->head = nullptr;
    this->size = 0;
}

// Metodo para imprimir los elementos de la lista en un archivo
// Complejidad: O(n)
template <class T> void DLinkedList<T>::printToFile(string fileName) {
    ofstream file;
    file.open(fileName);
    Node<T>* current = this->head;
    while (current != nullptr) {
        if (typeid(current->getData()) == typeid(accesoFallido)) {
            file << current->getData().getMesString() << " ";
            file << current->getData().getDia() << " ";
            file << current->getData().getHora() << " ";
            file << current->getData().getIp() << " ";
            file << current->getData().getRazon() << " ";
            file << endl;
            current = current->getNext();
        }
    }
    file.close();
}

#endif