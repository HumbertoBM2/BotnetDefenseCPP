/*
------------------------------------------------------------------------------------------------------
Clase Node que sirve para manejar nodos de una lista doblemente ligada

- Humberto Barrera Martínez

Fecha: 15 de octubre del 2023
------------------------------------------------------------------------------------------------------
*/

#ifndef Node_h
#define Node_h

#include <bits/stdc++.h>
using namespace std;

template <class T> class Node {

private:
    /// Atributos privados de la clase
    T data;
    Node<T>* next;
    Node<T>* prev;

public:
    // Constructores
    Node(T data);
    Node(T data, Node<T>* next);
    // Getters
    T getData();
    Node<T>* getNext();
    Node<T>* getPrev();
    // Setters
    void setData(T data);
    void setNext(Node<T>* next);
    void setPrev(Node<T>* prev);
};

// Constructores
template <class T> Node<T>::Node(T data) {
    this->data = data;
    this->next = nullptr;
}

template <class T> Node<T>::Node(T data, Node<T>* next) {
    this->data = data;
    this->next = next;
}

// Getters
template <class T> T Node<T>::getData() { return this->data; }

template <class T> Node<T>* Node<T>::getNext() { return this->next; }

template <class T> Node<T>* Node<T>::getPrev() { return this->prev; }

// Setters
template <class T> void Node<T>::setData(T data) { this->data = data; }

template <class T> void Node<T>::setNext(Node<T>* next) { this->next = next; }

template <class T> void Node<T>::setPrev(Node<T>* prev) { this->prev = prev; }

#endif