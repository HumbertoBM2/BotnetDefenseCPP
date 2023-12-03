/* ----------------------------------------------------------------------------------------------------
Clase stack.h que sirve para manejar pilas.

- Humberto Barrera Martinez

Fecha: 21 de noviembre del 2023
-----------------------------------------------------------------------------------------------------*/

#pragma once

#include <iostream>
#include <string>

#include "nodoStack.h"

template <class T> class stack {
  // Atributos privados
private:
  nodoStack<T> *top;
  int size;
  // Atributos publicos
public:
  // Constructores
  stack();
  // Destructor
  ~stack();
  // Metodos
  void push(T);
  T Top();
  void pop();
  bool isFull();
  bool isEmpty();
};

// Constructores
template <class T> stack<T>::stack() {
  top = nullptr;
  size = 0;
}

// Destructor
template <class T> stack<T>::~stack() {
  nodoStack<T> *next;
  next = top->getNext();
  while (top != NULL) {
    delete top;
    top = next;
  }
}

// Metodos

// Agrega un elemento a la pila
// Complejidad: O(1)
template <class T> void stack<T>::push(T data) {
  nodoStack<T> *newNode;
  newNode = new nodoStack<T>(data, top);
  top = newNode;
  size++;
}

// Elimina un elemento de la pila
// Complejidad: O(1)
template <class T> void stack<T>::pop() {
  nodoStack<T> *next;
  next = top->getNext();
  delete top;
  top = next;
  size--;
}

// Regresa el elemento en el tope de la pila
// Complejidad: O(1)
template <class T> T stack<T>::Top() { return top->getData(); }

// Regresa true si la pila esta llena
// Complejidad: O(1)
template <class T> bool stack<T>::isFull() {
  nodoStack<T> *newNode;
  newNode = new nodoStack<T>();
  if (newNode == NULL) {
    return true;
  } else {
    delete newNode;
    return false;
  }
}

// Regresa true si la pila esta vacia
// Complejidad: O(1)
template <class T> bool stack<T>::isEmpty() {
  if (top == NULL) {
    return true;
  } else {
    return false;
  }
}
