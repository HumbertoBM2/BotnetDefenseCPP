/* ----------------------------------------------------------------------------------------------------
Clase grafo.h que sirve para manejar los nodos de un grafo.

- Humberto Barrera Martinez

Fecha: 21 de noviembre del 2023
-----------------------------------------------------------------------------------------------------*/

#pragma once

#include <iostream>
#include <queue>
#include <string>

#include "nodo.h"
#include "stack.h"

class grafo {
  // Atributos privados
private:
  nodo *head = nullptr;
  // Atributos publicos
public:
  int count;
  // Destructor
  ~grafo();
  // Metodos
  nodo *addNodo(std::string);
  void addAdyacencia(nodo *, std::string);
  void BreadthFirst();
  void DepthFirst();
  nodo *getNodoByID(std::string);
};

// Destructor
grafo::~grafo() {
  nodo *last = head, *next;
  while (last != nullptr) {
    next = last->getNext();
    delete last;
    last = next;
  }
}

// Metodos

// Agrega un nodo al grafo
// Complejidad: O(n)
nodo *grafo::addNodo(std::string id) {
  nodo *nuevo = new nodo(id);
  if (head == nullptr) {
    head = nuevo;
    return nuevo;
  }
  nodo *last = head;
  while (last->getNext() != nullptr) {
    last = last->getNext();
  }
  last->setNext(nuevo);
  return nuevo;
}

// Agrega una adyacencia a un nodo
// Complejidad: O(n)
void grafo::addAdyacencia(nodo *nodo, std::string id) {
  nodo->addAdyacencia(id);
}

// Obtiene un nodo por su id
// Complejidad: O(n)
nodo *grafo::getNodoByID(std::string id) {
  nodo *v = head;
  while (v != nullptr) {
    if (v->Id() == id) {
      return v;
    }
    v = v->getNext();
  }
  return nullptr;
}

// Recorrido por anchura
// Complejidad: O(n)
void grafo::BreadthFirst() {
  nodo *v = head;
  while (v != nullptr) {
    v->setEstatus(enEspera);
    v = v->getNext();
  }
  v = head;
  std::queue<nodo *> fila;
  while (v != nullptr) {
    if (v->getEstatus() == enEspera) {
      fila.push(v);
      while (!fila.empty()) {
        nodo *u = fila.front();
        fila.pop();
        std::cout << u->Id() << " ";
        u->setEstatus(procesado);
        adyacencia *adyacencias = u->getAdyacencia();
        while (adyacencias != nullptr) {
          nodo *a = getNodoByID(adyacencias->Id());
          if (a->getEstatus() == enEspera) {
            fila.push(a);
            a->setEstatus(listo);
          }
          adyacencias = adyacencias->getNext();
        }
      }
    }
    v = v->getNext();
  }
  std::cout << std::endl;
}

// Recorrido por profundidad
// Complejidad: O(n)
void grafo::DepthFirst() {
  // Marcar todos los nodos como no visitados
  for (nodo *v = head; v != nullptr; v = v->getNext()) {
    v->setEstatus(enEspera);
  }
  stack<nodo *> pila;
  for (nodo *v = head; v != nullptr; v = v->getNext()) {
    if (v->getEstatus() == enEspera) {
      pila.push(v);
      while (!pila.isEmpty()) {
        nodo *u = pila.Top();
        if (u->getEstatus() == enEspera) {
          std::cout << u->Id() << " ";
          u->setEstatus(procesado);
          adyacencia *adyacencias = u->getAdyacencia();
          while (adyacencias != nullptr) {
            nodo *a = getNodoByID(adyacencias->Id());
            if (a->getEstatus() == enEspera) {
              pila.push(a);
              break; // Importante: salir del bucle para procesar el nuevo nodo
            }
            adyacencias = adyacencias->getNext();
          }
        } else {
          pila.pop();
        }
      }
    }
  }
  std::cout << std::endl;
}
