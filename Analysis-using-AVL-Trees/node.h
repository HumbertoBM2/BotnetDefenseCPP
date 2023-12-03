
/* ----------------------------------------------------------------------------------------------------
Clase node que sirve que sirve para crear nodos de una queue

- Humberto Barrera Martínez

Fecha: 9 de noviembre del 2023
-----------------------------------------------------------------------------------------------------*/

#ifndef node_h
#define node_h

#include <iostream>

template <class T> class node {

  // Atributos privados de la clase
private:
  T data;
  node<T> *next;

  // Atributos públicos de la clase
public:
  // Constructores
  node(T data);
  node(T data, node<T> *next);
  // Destructor
  ~node();
  // Getters
  T getData();
  node<T> *getNext();
  // Setters
  void setData(T data);
  void setNext(node<T> *next);
};

// Constructores
template <class T> node<T>::node(T data) {
  this->data = data;
  this->next = NULL;
}

template <class T> node<T>::node(T data, node<T> *next) {
  this->data = data;
  this->next = next;
}

// Destructor
template <class T> node<T>::~node() { this->next = NULL; }

// Getters
template <class T> T node<T>::getData() { return this->data; }

template <class T> node<T> *node<T>::getNext() { return this->next; }

// Setters
template <class T> void node<T>::setData(T data) { this->data = data; }

template <class T> void node<T>::setNext(node<T> *next) { this->next = next; }

#endif