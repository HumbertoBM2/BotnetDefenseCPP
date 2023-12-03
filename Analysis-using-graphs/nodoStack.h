/* ----------------------------------------------------------------------------------------------------
Clase nodoStack.h que sirve para crear los nodos de un stack.


- Humberto Barrera Martinez

Fecha: 21 de noviembre del 2023
-----------------------------------------------------------------------------------------------------*/

#pragma once

#include <cstddef>

template <class T> class nodoStack {
  // Atributos privados
private:
  T data;
  nodoStack<T> *next;
  // Atributos publicos
public:
  // Constructores
  nodoStack(T);
  nodoStack(T, nodoStack<T> *);
  // Getters
  T getData();
  nodoStack<T> *getNext();
  // Setters
  void setData(T);
  void setNext(nodoStack<T> *);
};

// Constructores

template <class T> nodoStack<T>::nodoStack(T _data) {
  data = _data;
  next = NULL;
}

template <class T> nodoStack<T>::nodoStack(T _data, nodoStack<T> *_next) {
  data = _data;
  next = _next;
}

// Getters

template <class T> T nodoStack<T>::getData() { return data; }

template <class T> nodoStack<T> *nodoStack<T>::getNext() { return next; }

// Setters

template <class T> void nodoStack<T>::setData(T _data) { data = _data; }

template <class T> void nodoStack<T>::setNext(nodoStack<T> *_next) {
  next = _next;
}
