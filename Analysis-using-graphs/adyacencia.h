/* ----------------------------------------------------------------------------------------------------
Clase adyacencia.h que sirve para manejar las adyacencias de los nodos de un
grafo.

- Humberto Barrera Martinez

Fecha: 21 de noviembre del 2023
-----------------------------------------------------------------------------------------------------*/

#pragma once

#include <iostream>
#include <string>

class adyacencia {
    // Atributos privados
private:
    std::string id;
    adyacencia* next = nullptr;
    // Metodos publicos
public:
    // Constructor
    adyacencia(std::string);
    // Getters
    std::string Id();
    adyacencia* getNext();
    // Setters
    void setNext(adyacencia*);
};

// Constructor
adyacencia::adyacencia(std::string id) { this->id = id; }

// Getters
std::string adyacencia::Id() { return id; }

adyacencia* adyacencia::getNext() { return next; }

// Setters
void adyacencia::setNext(adyacencia* next) { this->next = next; }