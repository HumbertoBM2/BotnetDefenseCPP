
/* ----------------------------------------------------------------------------------------------------
Clase nodeT que sirve que sirve para crear nodos de un árbol binario AVL.

- Humberto Barrera Martínez

Fecha: 9 de noviembre del 2023
-----------------------------------------------------------------------------------------------------*/

#ifndef nodeT_h
#define nodeT_h

#include <iostream>

template <class T> class nodeT {

    // Atributos privados de la clase
private:
    T data;
    nodeT<T>* left;
    nodeT<T>* right;

    // Atributos públicos de la clase
public:
    // Constructores
    nodeT();
    nodeT(T data);
    // Destructor
    ~nodeT();
    // Getters
    T getData();
    nodeT<T>* getLeft();
    nodeT<T>* getRight();
    // Setters
    void setData(T data);
    void setLeft(nodeT<T>* left);
    void setRight(nodeT<T>* right);
};

// Constructores
template <class T> nodeT<T>::nodeT() {
    this->data = 0;
    this->left = NULL;
    this->right = NULL;
}

template <class T> nodeT<T>::nodeT(T data) {
    this->data = data;
    this->left = NULL;
    this->right = NULL;
}

// Destructor
template <class T> nodeT<T>::~nodeT() {
    this->left = NULL;
    this->right = NULL;
}

// Getters
template <class T> T nodeT<T>::getData() { return this->data; }

template <class T> nodeT<T>* nodeT<T>::getLeft() { return this->left; }

template <class T> nodeT<T>* nodeT<T>::getRight() { return this->right; }

// Setters
template <class T> void nodeT<T>::setData(T data) { this->data = data; }

template <class T> void nodeT<T>::setLeft(nodeT<T>* left) { this->left = left; }

template <class T> void nodeT<T>::setRight(nodeT<T>* right) {
    this->right = right;
}

#endif