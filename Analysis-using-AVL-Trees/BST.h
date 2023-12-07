
/* ----------------------------------------------------------------------------------------------------
Clase BST que sirve que sirve para manejar arboles de busqueda binaria


- Humberto Barrera Martinez


Fecha: 9 de noviembre del 2023
-----------------------------------------------------------------------------------------------------*/

#ifndef BST_h
#define BST_h

#include "IPCount.h"
#include "nodeT.h"
#include "queue.h"
#include <iostream>

template <class T> class BST {

    // Atributos protegidos de la clase
protected:
    nodeT<T>* root;

    // Atributos públicos de la clase
public:
    // Constructores
    BST();
    // Destructor
    void destroyTree(nodeT<T>* r);
    ~BST();
    // Metodos
    bool search(T data);
    void push(T data);
    void pop(T data);
    void update(T data, T newData);
    void size();
    int getSize();
    void height();
    bool empty();
    void clear();
    void printPreOrder();
    void preOrder(nodeT<T>* r);
    void printInOrder();
    void inOrder(nodeT<T>* r);
    void printPostOrder();
    void postOrder(nodeT<T>* r);
    void printLevelByLevel();
    void levelByLevel(nodeT<T>* r);
    T getNode(T data);
};

// Constructores
template <class T> BST<T>::BST() { this->root = NULL; }

// Destructor auxiliar
template <class T> void BST<T>::destroyTree(nodeT<T>* r) {
    if (r != nullptr) {
        destroyTree(r->getLeft());
        destroyTree(r->getRight());
        delete r;
    }
}

// Destructor
template <class T> BST<T>::~BST() { destroyTree(this->root); }

// Metodos

// Metodo para buscar un elemento en el arbol
// Complejidad: O(n)
template <class T> bool BST<T>::search(T data) {
    nodeT<T>* curr = this->root;
    while (curr != NULL) {
        if (curr->getData() == data) {
            return true;
        }
        else if (curr->getData() > data) {
            curr = curr->getLeft();
        }
        else {
            curr = curr->getRight();
        }
    }
    return false;
}

// Metodo para insertar un elemento en el arbol
// Complejidad: O(n)
template <class T> void BST<T>::push(T data) {
    nodeT<T>* curr = this->root;
    nodeT<T>* father = NULL;
    while (curr != NULL) {
        if (curr->getData() == data) {
            return;
        }
        father = curr;
        curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
    }
    if (father == NULL) {
        this->root = new nodeT<T>(data);
    }
    else {
        if (father->getData() > data) {
            father->setLeft(new nodeT<T>(data));
        }
        else {
            father->setRight(new nodeT<T>(data));
        }
    }
}

// Metodo para eliminar un elemento en el arbol
// Complejidad: O(log(n))
template <class T> void BST<T>::pop(T data) {
    nodeT<T>* curr = this->root;
    nodeT<T>* father = NULL;
    while (curr != NULL) {
        if (curr->getData() == data) {
            break;
        }
        father = curr;
        curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
    }
    if (curr == NULL) {
        return;
    }
    if (curr->getLeft() == NULL && curr->getRight() == NULL) {
        if (father == NULL) {
            this->root = NULL;
        }
        else {
            if (father->getData() > data) {
                father->setLeft(NULL);
            }
            else {
                father->setRight(NULL);
            }
        }
        delete curr;
    }
    else if (curr->getLeft() != NULL && curr->getRight() == NULL) {
        if (father == NULL) {
            this->root = curr->getLeft();
        }
        else {
            if (father->getData() > data) {
                father->setLeft(curr->getLeft());
            }
            else {
                father->setRight(curr->getLeft());
            }
        }
        delete curr;
    }
    else if (curr->getLeft() == NULL && curr->getRight() != NULL) {
        if (father == NULL) {
            this->root = curr->getRight();
        }
        else {
            if (father->getData() > data) {
                father->setLeft(curr->getRight());
            }
            else {
                father->setRight(curr->getRight());
            }
        }
        delete curr;
    }
    else {
        nodeT<T>* curr2 = curr->getLeft();
        nodeT<T>* father2 = curr;
        while (curr2->getRight() != NULL) {
            father2 = curr2;
            curr2 = curr2->getRight();
        }
        curr->setData(curr2->getData());
        if (father2->getData() > curr2->getData()) {
            father2->setLeft(curr2->getLeft());
        }
        else {
            father2->setRight(curr2->getLeft());
        }
        delete curr2;
    }
}

// Metodo para actualizar un elemento en el arbol
// Complejidad: O(log(n))
template <class T> void BST<T>::update(T data, T newData) {
    this->pop(data);
    this->push(newData);
}

// Metodo para imprimir el tamaño del arbol
// Complejidad: O(n)
template <class T> void BST<T>::size() {
    int size = 0;
    nodeT<T>* curr = this->root;
    queue<nodeT<T>*> q;
    q.push(curr);
    while (!q.isEmpty()) {
        curr = q.getFront();
        q.pop();
        size++;
        if (curr->getLeft() != NULL) {
            q.push(curr->getLeft());
        }
        if (curr->getRight() != NULL) {
            q.push(curr->getRight());
        }
    }
    std::cout << "Size: " << size << std::endl;
}

// Metodo para obtener el tamaño del arbol
// Complejidad: O(n)
template <class T> int BST<T>::getSize() {
    int size = 0;
    nodeT<T>* curr = this->root;
    queue<nodeT<T>*> q;
    q.push(curr);
    while (!q.isEmpty()) {
        curr = q.getFront();
        q.pop();
        size++;
        if (curr->getLeft() != NULL) {
            q.push(curr->getLeft());
        }
        if (curr->getRight() != NULL) {
            q.push(curr->getRight());
        }
    }
    return size;
}

// Metodo para obtener la altura del arbol
// Complejidad: O(n)
template <class T> void BST<T>::height() {
    int height = 0;
    nodeT<T>* curr = this->root;
    queue<nodeT<T>*> q;
    q.push(curr);
    while (!q.empty()) {
        int size = q.size();
        while (size > 0) {
            curr = q.front();
            q.pop();
            if (curr->getLeft() != NULL) {
                q.push(curr->getLeft());
            }
            if (curr->getRight() != NULL) {
                q.push(curr->getRight());
            }
            size--;
        }
        height++;
    }
    std::cout << "Height: " << height << std::endl;
}

// Metodo para verificar si el arbol esta vacio
// Complejidad: O(1)
template <class T> bool BST<T>::empty() { return this->root == NULL; }

// Metodo para limpiar el arbol
// Complejidad: O(n)
template <class T> void BST<T>::clear() {
    this->destroyTree(this->root);
    this->root = NULL;
}

// Metodo para imprimir el arbol en preorden
// Complejidad: O(n)
template <class T> void BST<T>::printPreOrder() {
    this->preOrder(this->root);
    std::cout << std::endl;
}

// Metodo auxiliar para imprimir el arbol en preorden
// Complejidad: O(n)
template <class T> void BST<T>::preOrder(nodeT<T>* r) {
    if (r != NULL) {
        std::cout << r->getData() << " ";
        this->preOrder(r->getLeft());
        this->preOrder(r->getRight());
    }
}

// Metodo para imprimir el arbol en orden
// Complejidad: O(n)
template <class T> void BST<T>::printInOrder() {
    this->inOrder(this->root);
    std::cout << std::endl;
}

// Metodo auxiliar para imprimir el arbol en orden
// Complejidad: O(n)
template <class T> void BST<T>::inOrder(nodeT<T>* r) {
    if (r != NULL) {
        this->inOrder(r->getLeft());
        std::cout << r->getData() << " ";
        this->inOrder(r->getRight());
    }
}

// Metodo para imprimir el arbol en postorden
// Complejidad: O(n)
template <class T> void BST<T>::printPostOrder() {
    this->postOrder(this->root);
    std::cout << std::endl;
}

// Metodo auxiliar para imprimir el arbol en postorden
// Complejidad: O(n)
template <class T> void BST<T>::postOrder(nodeT<T>* r) {
    if (r != NULL) {
        this->postOrder(r->getLeft());
        this->postOrder(r->getRight());
        std::cout << r->getData() << " ";
    }
}

// Metodo para imprimir el arbol por niveles
// Complejidad: O(n)
template <class T> void BST<T>::printLevelByLevel() {
    this->levelByLevel(this->root);
    std::cout << std::endl;
}

// Metodo auxiliar para imprimir el arbol por niveles
// Complejidad: O(n)
template <class T> void BST<T>::levelByLevel(nodeT<T>* r) {
    nodeT<T>* curr = r;
    queue<nodeT<T>*> q;
    q.push(curr);
    while (!q.empty()) {
        curr = q.front();
        q.pop();
        std::cout << curr->getData() << " ";
        if (curr->getLeft() != NULL) {
            q.push(curr->getLeft());
        }
        if (curr->getRight() != NULL) {
            q.push(curr->getRight());
        }
    }
}

// Metodo para obtener un nodo del arbol
// Complejidad: O(n)
template <class T> T BST<T>::getNode(T data) {
    nodeT<T>* curr = this->root;
    while (curr != NULL) {
        if (curr->getData() == data) {
            return curr->getData();
        }
        else if (curr->getData() > data) {
            curr = curr->getLeft();
        }
        else {
            curr = curr->getRight();
        }
    }
    return NULL;
}

#endif