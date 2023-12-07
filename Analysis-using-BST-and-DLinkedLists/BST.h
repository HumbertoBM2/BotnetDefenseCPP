/*
------------------------------------------------------------------------------------------------------
Clase BST que implementa un arbol binario de busqueda.

- Humberto Barrera Martínez

Fecha: 15 de octubre del 2023
------------------------------------------------------------------------------------------------------
*/

#ifndef BST_h
#define BST_h

#include "accesoFallido.h"
#include "nodeT.h"
#include <bits/stdc++.h>
using namespace std;

template <class T> class BST {

    // Atributos privados de la clase
private:
    nodeT<T>* root;

    // Atributos publicos de la clase
public:
    // Constructores
    BST();
    // Destructor
    ~BST();
    // Metodos
    bool search(T data);
    void push(T data);
    void pop(T data);
    void update(T data, T newData);
    void print();
    void begin();
    void end();
    void inorder(nodeT<T>* currNode);
    void printInorder();
    void printInOrderAndInRangeAux(nodeT<T>* currNode, T min, T max);
    void printInOrderAndInRange(T min, T max);
    void size();
    void printToFile(string nombreArchivo);
    void printToFileInOrder(string nombreArchivo);
    void printToFileInOrderaux(nodeT<T>* currNode, ofstream& archivo);
};

// Constructores
template <class T> BST<T>::BST() { this->root = NULL; }

// Destructor
template <class T> BST<T>::~BST() { this->root = NULL; }

// Metodos

// Metodo para buscar un dato en el arbol
// Complejidad: O(log(n))
template <class T> bool BST<T>::search(T data) {
    nodeT<T>* currNode = this->root;
    while (currNode != NULL) {
        if (currNode->getData() == data) {
            return true;
        }
        else if (currNode->getData() > data) {
            currNode = currNode->getLeft();
        }
        else {
            currNode = currNode->getRight();
        }
    }
    return false;
}

// Metodo para insertar un dato en el arbol
// Complejidad: O(log(n))
template <class T> void BST<T>::push(T data) {
    nodeT<T>* newNode = new nodeT<T>(data);
    if (this->root == NULL) {
        this->root = newNode;
    }
    else {
        nodeT<T>* currNode = this->root;
        nodeT<T>* parentNode = NULL;
        while (currNode != NULL) {
            parentNode = currNode;
            if (currNode->getData() > data) {
                currNode = currNode->getLeft();
            }
            else {
                currNode = currNode->getRight();
            }
        }
        if (parentNode->getData() > data) {
            parentNode->setLeft(newNode);
        }
        else {
            parentNode->setRight(newNode);
        }
    }
}

// Metodo para eliminar un dato del arbol
// Complejidad: O(log(n))
template <class T> void BST<T>::pop(T data) {
    nodeT<T>* currNode = this->root;
    nodeT<T>* parentNode = NULL;
    while (currNode != NULL && currNode->getData() != data) {
        parentNode = currNode;
        if (currNode->getData() > data) {
            currNode = currNode->getLeft();
        }
        else {
            currNode = currNode->getRight();
        }
    }
    if (currNode == NULL) {
        cout << "El dato no existe en el arbol" << endl;
    }
    else {
        int childCount = 0;
        if (currNode->getLeft() != NULL) {
            childCount++;
        }
        if (currNode->getRight() != NULL) {
            childCount++;
        }
        switch (childCount) {
        case 0:
            if (parentNode == NULL) {
                this->root = NULL;
            }
            else {
                if (parentNode->getData() > data) {
                    parentNode->setLeft(NULL);
                }
                else {
                    parentNode->setRight(NULL);
                }
            }
            delete currNode;
            break;
        case 1:
            if (parentNode == NULL) {
                if (currNode->getLeft() != NULL) {
                    this->root = currNode->getLeft();
                }
                else {
                    this->root = currNode->getRight();
                }
            }
            else {
                if (parentNode->getData() > data) {
                    if (currNode->getLeft() != NULL) {
                        parentNode->setLeft(currNode->getLeft());
                    }
                    else {
                        parentNode->setLeft(currNode->getRight());
                    }
                }
                else {
                    if (currNode->getLeft() != NULL) {
                        parentNode->setRight(currNode->getLeft());
                    }
                    else {
                        parentNode->setRight(currNode->getRight());
                    }
                }
            }
            delete currNode;
            break;
        case 2:
            nodeT<T> *succesor = currNode->getRight();
            nodeT<T>* succesorParent = currNode;
            while (succesor->getLeft() != NULL) {
                succesorParent = succesor;
                succesor = succesor->getLeft();
            }
            if (succesorParent->getData() > succesor->getData()) {
                succesorParent->setLeft(succesor->getRight());
            }
            else {
                succesorParent->setRight(succesor->getRight());
            }
            currNode->setData(succesor->getData());
            delete succesor;
            break;
        }
    }
}

// Metodo para actualizar un dato del arbol
// Complejidad: O(n)
template <class T> void BST<T>::update(T data, T newData) {
    this->pop(data);
    this->push(newData);
}

// Metodo para imprimir el arbol
// Complejidad: O(n)
template <class T> void BST<T>::print() {
    queue<nodeT<T>*> aux;
    nodeT<T>* currNode = this->root;
    aux.push(currNode);
    while (!aux.empty()) {
        currNode = aux.front();
        aux.pop();
        // Verificar si el nodo es de tipo accesoFallido
        if (typeid(currNode->getData()) == typeid(accesoFallido)) {
            accesoFallido acceso = currNode->getData();
            acceso.muestraDatos(); // Utilizar el método muestraDatos()
        }
        if (currNode->getLeft() != NULL) {
            aux.push(currNode->getLeft());
        }
        if (currNode->getRight() != NULL) {
            aux.push(currNode->getRight());
        }
    }
    cout << endl;
}

// Metodo para obtener el primer elemento del arbol
// Complejidad: O(n)
template <class T> void BST<T>::begin() {
    nodeT<T>* currNode = this->root;
    while (currNode->getLeft() != NULL) {
        currNode = currNode->getLeft();
    }
    // Verificar si el nodo es de tipo accesoFallido
    if (typeid(currNode->getData()) == typeid(accesoFallido)) {
        accesoFallido acceso = currNode->getData();
        acceso.muestraDatos(); // Utilizar el método muestraDatos()
    }
}

// Metodo para obtener el ultimo elemento del arbol
// Complejidad: O(n)
template <class T> void BST<T>::end() {
    nodeT<T>* currNode = this->root;
    while (currNode->getRight() != NULL) {
        currNode = currNode->getRight();
    }
    // Verificar si el nodo es de tipo accesoFallido
    if (typeid(currNode->getData()) == typeid(accesoFallido)) {
        accesoFallido acceso = currNode->getData();
        acceso.muestraDatos(); // Utilizar el método muestraDatos()
    }
}

// Metodo para recorrer el arbol en orden
// Complejidad: O(n)
template <class T> void BST<T>::inorder(nodeT<T>* currNode) {
    if (currNode != NULL) {
        inorder(currNode->getLeft());
        // Verificar si el nodo es de tipo accesoFallido
        if (typeid(currNode->getData()) == typeid(accesoFallido)) {
            accesoFallido acceso = currNode->getData();
            acceso.muestraDatos(); // Utilizar el método muestraDatos()
        }
        inorder(currNode->getRight());
    }
}

// Metodo auxiliar para imprimir el arbol en orden y en un rango
// Complejidad: O(n)
template <class T>
void BST<T>::printInOrderAndInRangeAux(nodeT<T>* currNode, T min, T max) {
    if (currNode != NULL) {
        printInOrderAndInRangeAux(currNode->getLeft(), min, max);
        // Verificar si el nodo es de tipo accesoFallido
        if (typeid(currNode->getData()) == typeid(accesoFallido)) {
            accesoFallido acceso = currNode->getData();
            if (acceso.getIp() >= min.getIp() && acceso.getIp() <= max.getIp()) {
                acceso.muestraDatos(); // Utilizar el método muestraDatos()
            }
        }
        printInOrderAndInRangeAux(currNode->getRight(), min, max);
    }
}

// Metodo para imprimir el arbol en orden y en un rango
// Complejidad: O(n)
template <class T> void BST<T>::printInOrderAndInRange(T min, T max) {
    printInOrderAndInRangeAux(this->root, min, max);
    cout << endl;
}

// Metodo para imprimir el arbol en orden
// Complejidad: O(n)
template <class T> void BST<T>::printInorder() {
    inorder(this->root);
    cout << endl;
}

// Metodo para obtener el tamaño del arbol
// Complejidad: O(n)
template <class T> void BST<T>::size() {
    int size = 0;
    queue<nodeT<T>*> aux;
    nodeT<T>* currNode = this->root;
    aux.push(currNode);
    while (!aux.empty()) {
        currNode = aux.front();
        aux.pop();
        size++;
        if (currNode->getLeft() != NULL) {
            aux.push(currNode->getLeft());
        }
        if (currNode->getRight() != NULL) {
            aux.push(currNode->getRight());
        }
    }
    cout << "El tamaño del arbol es: " << size << endl;
}

// Metodo para imprimir el arbol en un archivo
// Complejidad: O(n)
template <class T> void BST<T>::printToFile(string nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << endl;
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    else {
        queue<nodeT<T>*> aux;
        nodeT<T>* currNode = this->root;
        aux.push(currNode);
        while (!aux.empty()) {
            currNode = aux.front();
            aux.pop();
            // Verificar si el nodo es de tipo accesoFallido
            if (typeid(currNode->getData()) == typeid(accesoFallido)) {
                accesoFallido acceso = currNode->getData();
                archivo << acceso.getMesString() << " " << acceso.getDia() << " "
                    << acceso.getHora() << " " << acceso.getIp() << " "
                    << acceso.getRazon()
                    << endl; // Utilizar el método muestraDatos()
            }
            if (currNode->getLeft() != NULL) {
                aux.push(currNode->getLeft());
            }
            if (currNode->getRight() != NULL) {
                aux.push(currNode->getRight());
            }
        }
        archivo.close();
        cout << endl;
        cout << "Archivo creado correctamente" << endl;
    }
}

// Metodo auxiliar para imprimir el arbol inorden en un archivo
// Complejidad: O(n)
template <class T>
void BST<T>::printToFileInOrderaux(nodeT<T>* currNode, ofstream& archivo) {
    if (currNode == nullptr) {
        return;
    }
    printToFileInOrderaux(currNode->getLeft(), archivo);
    // Verificar si el nodo es de tipo accesoFallido
    if (typeid(currNode->getData()) == typeid(accesoFallido)) {
        accesoFallido acceso = currNode->getData();
        archivo << acceso.getMesString() << " " << acceso.getDia() << " "
            << acceso.getHora() << " " << acceso.getIp() << " "
            << acceso.getRazon() << endl; // Utilizar el método muestraDatos()
    }
    printToFileInOrderaux(currNode->getRight(), archivo);
}

// Metodo para imprimir el arbol en un archivo
// Complejidad: O(n)
template <class T> void BST<T>::printToFileInOrder(string nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << endl;
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    else {
        printToFileInOrderaux(this->root, archivo);
        archivo.close();
        cout << endl;
        cout << "Archivo creado correctamente" << endl;
    }
}

#endif