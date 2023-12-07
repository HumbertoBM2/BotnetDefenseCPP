/* ----------------------------------------------------------------------------------------------------
Clase nodo.h que sirve para crear los nodos de un grafo.

- Humberto Barrera Martinez

Fecha: 21 de noviembre del 2023
-----------------------------------------------------------------------------------------------------*/

#pragma once

#include <iostream>
#include <string>

#include "adyacencia.h"

// Enumerador para el estatus de los nodos
enum estatus {
    enEspera,
    procesado,
    listo,
};

class nodo {
    // Atributos privados
private:
    std::string id;
    int numAdyacencias = 0;
    nodo* next = nullptr;
    adyacencia* conexiones = nullptr;
    estatus estado;
    // Atributos publicos
public:
    // Constructor
    nodo(std::string);
    // Destructor
    ~nodo();
    // Getters
    std::string Id();
    int getNumAdyacencias();
    adyacencia* getAdyacencia();
    nodo* getNext();
    estatus getEstatus();
    // Setters
    void setNext(nodo*);
    void setEstatus(estatus);
    // Metodos
    void addAdyacencia(std::string);
};

// Constructor
nodo::nodo(std::string id) { this->id = id, this->numAdyacencias = 0; }

// Destructor
nodo::~nodo() {
    adyacencia* last = conexiones, * next;
    while (last != nullptr) {
        next = last->getNext();
        delete last;
        last = next;
    }
}

// Getters

// Regresa el id del nodo
// Complejidad: O(1)
std::string nodo::Id() { return id; }

// Regresa el numero de adyacencias del nodo
// Complejidad: O(1)
int nodo::getNumAdyacencias() { return numAdyacencias; }

// Regresa la adyacencia del nodo
// Complejidad: O(1)
adyacencia* nodo::getAdyacencia() { return conexiones; }

// Regresa el siguiente nodo
// Complejidad: O(1)
nodo* nodo::getNext() { return next; }

// Regresa el estatus del nodo
// Complejidad: O(1)
estatus nodo::getEstatus() { return estado; }

// Setters

// Establece el siguiente nodo
// Complejidad: O(1)
void nodo::setNext(nodo* next) { this->next = next; }

// Establece el estatus del nodo
// Complejidad: O(1)
void nodo::setEstatus(estatus estado) { this->estado = estado; }

// Metodos

// Agrega una adyacencia al nodo
// Complejidad: O(n)
void nodo::addAdyacencia(std::string id) {
    adyacencia* nueva = new adyacencia(id);
    numAdyacencias++;
    if (conexiones == nullptr) {
        conexiones = nueva;
        return;
    }
    adyacencia* last = conexiones;
    while (last->getNext() != nullptr) {
        last = last->getNext();
    }
    last->setNext(nueva);
}
