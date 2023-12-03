
/* ----------------------------------------------------------------------------------------------------
Clase AVL que sirve que sirve para manejar arboles de busqueda binaria de tipo
AVL

- Humberto Barrera Martinez

Fecha: 9 de noviembre del 2023
-----------------------------------------------------------------------------------------------------*/

#ifndef AVL_h
#define AVL_h

#include "BST.h"
#include "IPCount.h"
#include "nodeT.h"
#include <iostream>

template <class T> class AVL : public BST<T> {

  // Atributos privados de la clase
private:
  static int count;

  // Atributos publicos de la clase
public:
  bool isBalanced(T);
  bool isBalanced(nodeT<T> *);
  int height(nodeT<T> *);
  void push(T);
  void pop(T);
  nodeT<T> *getPivot(T);
  void swap(nodeT<T> *, nodeT<T> *);
  void simpleLeftRotation(nodeT<T> *);
  void simpleRightRotation(nodeT<T> *);
  void doubleLeftRotation(nodeT<T> *);
  void doubleRightRotation(nodeT<T> *);
  void printPreOrder();
  void preOrder(nodeT<T> *);
  void printInOrder();
  void inOrder(nodeT<T> *);
  void printPostOrder();
  void postOrder(nodeT<T> *);
  void printLevelByLevel();
  void levelByLevel(nodeT<T> *);
  void reverseInOrder(nodeT<T> *);
  void printReverseInOrder();
  void reverseInOrderTop5(nodeT<T> *);
  void printReverseInOrderTop5();
};

// Inicializacion del contador
template <class T> int AVL<T>::count = 0;

// Metodo para verificar si un nodo esta balanceado
// Complejidad: O(1)
template <class T> bool AVL<T>::isBalanced(T data) {
  nodeT<T> *curr = this->root;
  while (curr != NULL) {
    if (curr->getData() == data) {
      return this->isBalanced(curr);
    } else if (curr->getData() > data) {
      curr = curr->getLeft();
    } else {
      curr = curr->getRight();
    }
  }
  return false;
}

// Metodo para verificar si un nodo esta balanceado
// Complejidad: O(1)
template <class T> bool AVL<T>::isBalanced(nodeT<T> *r) {
  if (r == NULL) {
    return true;
  } else {
    int leftHeight = this->height(r->getLeft());
    int rightHeight = this->height(r->getRight());
    if (abs(leftHeight - rightHeight) <= 1) {
      return true;
    } else {
      return false;
    }
  }
}

// Metodo para obtener la altura de un nodo
// Complejidad: O(n)
template <class T> int AVL<T>::height(nodeT<T> *r) {
  if (r == NULL) {
    return 0;
  } else {
    int leftHeight = this->height(r->getLeft());
    int rightHeight = this->height(r->getRight());
    if (leftHeight > rightHeight) {
      return leftHeight + 1;
    } else {
      return rightHeight + 1;
    }
  }
}

// Metodo para insertar un elemento en el arbol
// Complejidad: O(log(n))
template <class T> void AVL<T>::push(T data) {
  this->BST<T>::push(data);
  nodeT<T> *pivot = this->getPivot(data);
  if (pivot != NULL) {
    if (!this->isBalanced(pivot)) {
      if (pivot->getLeft() != NULL && pivot->getLeft()->getData() == data) {
        if (pivot->getLeft()->getLeft() != NULL &&
            pivot->getLeft()->getLeft()->getData() == data) {
          this->simpleRightRotation(pivot);
        } else {
          this->doubleRightRotation(pivot);
        }
      } else {
        if (pivot->getRight()->getRight() != NULL &&
            pivot->getRight()->getRight()->getData() == data) {
          this->simpleLeftRotation(pivot);
        } else {
          this->doubleLeftRotation(pivot);
        }
      }
    }
  }
}

// Metodo para eliminar un elemento en el arbol
// Complejidad: O(log(n))
template <class T> void AVL<T>::pop(T data) {
  nodeT<T> *pivot = this->getPivot(data);
  this->BST<T>::pop(data);
  if (pivot != NULL) {
    if (!this->isBalanced(pivot)) {
      if (pivot->getLeft() != NULL && pivot->getLeft()->getData() == data) {
        if (pivot->getLeft()->getLeft() != NULL &&
            pivot->getLeft()->getLeft()->getData() == data) {
          this->simpleRightRotation(pivot);
        } else {
          this->doubleRightRotation(pivot);
        }
      } else {
        if (pivot->getRight()->getRight() != NULL &&
            pivot->getRight()->getRight()->getData() == data) {
          this->simpleLeftRotation(pivot);
        } else {
          this->doubleLeftRotation(pivot);
        }
      }
    }
  }
}

// Metodo para obtener el nodo pivot de un nodo
// Complejidad: O(log(n))
template <class T> nodeT<T> *AVL<T>::getPivot(T data) {
  nodeT<T> *curr = this->root;
  nodeT<T> *father = NULL;
  while (curr != NULL) {
    if (curr->getData() == data) {
      return father;
    }
    father = curr;
    curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
  }
  return NULL;
}

// Metodo para intercambiar dos nodos
// Complejidad: O(1)
template <class T> void AVL<T>::swap(nodeT<T> *a, nodeT<T> *b) {
  T aux = a->getData();
  a->setData(b->getData());
  b->setData(aux);
}

// Metodo para realizar una rotacion simple a la izquierda
// Complejidad: O(1)
template <class T> void AVL<T>::simpleLeftRotation(nodeT<T> *pivot) {
  nodeT<T> *aux = pivot->getRight();
  pivot->setRight(aux->getLeft());
  aux->setLeft(pivot);
  if (pivot == this->root) {
    this->root = aux;
  } else {
    nodeT<T> *father = this->getPivot(pivot->getData());
    if (father->getData() > pivot->getData()) {
      father->setLeft(aux);
    } else {
      father->setRight(aux);
    }
  }
}

// Metodo para realizar una rotacion simple a la derecha
// Complejidad: O(1)
template <class T> void AVL<T>::simpleRightRotation(nodeT<T> *pivot) {
  nodeT<T> *aux = pivot->getLeft();
  pivot->setLeft(aux->getRight());
  aux->setRight(pivot);
  if (pivot == this->root) {
    this->root = aux;
  } else {
    nodeT<T> *father = this->getPivot(pivot->getData());
    if (father->getData() > pivot->getData()) {
      father->setLeft(aux);
    } else {
      father->setRight(aux);
    }
  }
}

// Metodo para realizar una rotacion doble a la izquierda
// Complejidad: O(1)
template <class T> void AVL<T>::doubleLeftRotation(nodeT<T> *pivot) {
  nodeT<T> *aux = pivot->getRight()->getLeft();
  pivot->getRight()->setLeft(aux->getRight());
  aux->setRight(pivot->getRight());
  pivot->setRight(aux->getLeft());
  aux->setLeft(pivot);
  if (pivot == this->root) {
    this->root = aux;
  } else {
    nodeT<T> *father = this->getPivot(pivot->getData());
    if (father->getData() > pivot->getData()) {
      father->setLeft(aux);
    } else {
      father->setRight(aux);
    }
  }
}

// Metodo para realizar una rotacion doble a la derecha
// Complejidad: O(1)
template <class T> void AVL<T>::doubleRightRotation(nodeT<T> *pivot) {
  nodeT<T> *aux = pivot->getLeft()->getRight();
  pivot->getLeft()->setRight(aux->getLeft());
  aux->setLeft(pivot->getLeft());
  pivot->setLeft(aux->getRight());
  aux->setRight(pivot);
  if (pivot == this->root) {
    this->root = aux;
  } else {
    nodeT<T> *father = this->getPivot(pivot->getData());
    if (father->getData() > pivot->getData()) {
      father->setLeft(aux);
    } else {
      father->setRight(aux);
    }
  }
}

// Metodo para imprimir el arbol en pre-orden
// Complejidad: O(n)
template <class T> void AVL<T>::printPreOrder() {
  this->preOrder(this->root);
  std::cout << std::endl;
}

// Metodo auxiliar para imprimir el arbol en pre-orden
// Complejidad: O(n)
template <class T> void AVL<T>::preOrder(nodeT<T> *r) {
  if (r != NULL) {
    std::cout << r->getData() << " ";
    this->preOrder(r->getLeft());
    this->preOrder(r->getRight());
  }
}

// Metodo para imprimir el arbol en orden
// Complejidad: O(n)
template <class T> void AVL<T>::printInOrder() {
  this->inOrder(this->root);
  std::cout << std::endl;
}

// Metodo auxiliar para imprimir el arbol en orden
// Complejidad: O(n)
template <class T> void AVL<T>::inOrder(nodeT<T> *r) {
  if (r != NULL) {
    this->inOrder(r->getLeft());
    if (typeid(r->getData()) == typeid(IPCount)) {
      std::cout << r->getData().getIP() << " " << r->getData().getCount()
                << std::endl;
    }
    this->inOrder(r->getRight());
  }
}

// Metodo para imprimir el arbol en post-orden
// Complejidad: O(n)
template <class T> void AVL<T>::printPostOrder() {
  this->postOrder(this->root);
  std::cout << std::endl;
}

// Metodo auxiliar para imprimir el arbol en post-orden
// Complejidad: O(n)
template <class T> void AVL<T>::postOrder(nodeT<T> *r) {
  if (r != NULL) {
    this->postOrder(r->getLeft());
    this->postOrder(r->getRight());
    std::cout << r->getData() << " ";
  }
}

// Metodo para imprimir el arbol por niveles
// Complejidad: O(n)
template <class T> void AVL<T>::printLevelByLevel() {
  this->levelByLevel(this->root);
  std::cout << std::endl;
}

// Metodo auxiliar para imprimir el arbol por niveles
// Complejidad: O(n)
template <class T> void AVL<T>::levelByLevel(nodeT<T> *r) {
  queue<nodeT<T> *> q;
  nodeT<T> *curr = r;
  q.push(curr);
  while (!q.isEmpty()) {
    curr = q.getFront();
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

// Metodo para imprimir el arbol en orden inverso
// Complejidad: O(n)
template <class T> void AVL<T>::printReverseInOrder() {
  this->reverseInOrder(this->root);
  std::cout << std::endl;
}

// Metodo auxiliar para imprimir el arbol en orden inverso
// Complejidad: O(n)
template <class T> void AVL<T>::reverseInOrder(nodeT<T> *r) {
  if (r != NULL) {
    this->reverseInOrder(r->getRight());
    if (typeid(r->getData()) == typeid(IPCount)) {
      std::cout << r->getData().getIP() << " " << r->getData().getCount()
                << std::endl;
    }
    this->reverseInOrder(r->getLeft());
  }
}

// Meotodo auxiliar para imprimir los ultimos 5 nodos del arbol en orden inverso
// Complejidad: O(n)
template <class T> void AVL<T>::reverseInOrderTop5(nodeT<T> *r) {
  if (r != NULL && count < 5) {
    this->reverseInOrderTop5(r->getRight());

    if (typeid(r->getData()) == typeid(IPCount)) {
      if (count < 5) {
        std::cout << "IP: " << r->getData().getIP()
                  << " \tApariciones: " << r->getData().getCount() << std::endl;
        count++;
      }
    }

    this->reverseInOrderTop5(r->getLeft());
  }
}

// Metodo para imprimir los ultimos 5 nodos del arbol en orden inverso
// Complejidad: O(n)
template <class T> void AVL<T>::printReverseInOrderTop5() {
  this->reverseInOrderTop5(this->root);
  std::cout << std::endl;
  count = 0; // Reinicia el contador
}

#endif