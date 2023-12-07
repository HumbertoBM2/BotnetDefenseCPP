/*
------------------------------------------------------------------------------------------------------
Archivo main: Se usan BST y listas doblemente enlazadas para almcacenar y
manipular registros de acceso fallidos

- Humberto Barrera Martínez

Fecha: 15 de octubre del 2023
------------------------------------------------------------------------------------------------------
*/

// Clases y librerias utilizadas
#include "BST.h"
#include "DLinkedList.h"
#include "accesoFallido.h"

#include <bits/stdc++.h>
using namespace std;

#define vt vector
#define pb push_back

// Estrucutras de datos que almacenan los registros de acceso fallido
BST<accesoFallido> arbol;
DLinkedList<accesoFallido> DLL;
DLinkedList<accesoFallido> DLLFiltrada;

// Funcion que lee el archivo de registros con accesos fallidos y los almacena
// en un BST Complejidad: O(n)
void leerArchivoBST(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << endl;
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    else {
        cout << endl;
        cout << "Archivo abierto correctamente" << endl;
        string lineaLeida;
        while (getline(archivo, lineaLeida)) {
            istringstream linea(lineaLeida);
            accesoFallido accesoIndividual;
            string mesLeido;
            int mesLeidoNumerico;
            int diaLeido;
            string horaLeida;
            string ipLeida;
            string razonLeida;
            linea >> mesLeido >> diaLeido >> horaLeida >>
                ipLeida;          // Se leen los datos del registro
            mesLeidoNumerico = 0; // Se inicializa el mes en 0
            // Convertir el mes leído a un número
            if (mesLeido == "Jan")
                mesLeidoNumerico = 1;
            else if (mesLeido == "Feb")
                mesLeidoNumerico = 2;
            else if (mesLeido == "Mar")
                mesLeidoNumerico = 3;
            else if (mesLeido == "Apr")
                mesLeidoNumerico = 4;
            else if (mesLeido == "May")
                mesLeidoNumerico = 5;
            else if (mesLeido == "Jun")
                mesLeidoNumerico = 6;
            else if (mesLeido == "Jul")
                mesLeidoNumerico = 7;
            else if (mesLeido == "Aug")
                mesLeidoNumerico = 8;
            else if (mesLeido == "Sep")
                mesLeidoNumerico = 9;
            else if (mesLeido == "Oct")
                mesLeidoNumerico = 10;
            else if (mesLeido == "Nov")
                mesLeidoNumerico = 11;
            else if (mesLeido == "Dec")
                mesLeidoNumerico = 12;
            getline(linea >> ws, razonLeida); // Se lee la razón del acceso fallido
            arbol.push(
                accesoFallido(mesLeidoNumerico, diaLeido, horaLeida, ipLeida,
                    razonLeida)); // Se inserta el registro en el árbol
        }
        archivo.close();
    }
}

// Funcion que lee el archivo de registros con accesos fallidos y los almacena
// en una lista doblemente ligada Complejidad: O(n)
void leerArchivoDLL(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << endl;
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    else {
        cout << endl;
        cout << "Archivo abierto correctamente" << endl;
        string lineaLeida;
        while (getline(archivo, lineaLeida)) {
            istringstream linea(lineaLeida);
            accesoFallido accesoIndividual;
            string mesLeido;
            int mesLeidoNumerico;
            int diaLeido;
            string horaLeida;
            string ipLeida;
            string razonLeida;
            linea >> mesLeido >> diaLeido >> horaLeida >>
                ipLeida;          // Se leen los datos del registro
            mesLeidoNumerico = 0; // Se inicializa el mes en 0
            // Convertir el mes leído a un número
            if (mesLeido == "Jan")
                mesLeidoNumerico = 1;
            else if (mesLeido == "Feb")
                mesLeidoNumerico = 2;
            else if (mesLeido == "Mar")
                mesLeidoNumerico = 3;
            else if (mesLeido == "Apr")
                mesLeidoNumerico = 4;
            else if (mesLeido == "May")
                mesLeidoNumerico = 5;
            else if (mesLeido == "Jun")
                mesLeidoNumerico = 6;
            else if (mesLeido == "Jul")
                mesLeidoNumerico = 7;
            else if (mesLeido == "Aug")
                mesLeidoNumerico = 8;
            else if (mesLeido == "Sep")
                mesLeidoNumerico = 9;
            else if (mesLeido == "Oct")
                mesLeidoNumerico = 10;
            else if (mesLeido == "Nov")
                mesLeidoNumerico = 11;
            else if (mesLeido == "Dec")
                mesLeidoNumerico = 12;
            getline(linea >> ws, razonLeida); // Se lee la razón del acceso fallido
            DLL.addLast(
                accesoFallido(mesLeidoNumerico, diaLeido, horaLeida, ipLeida,
                    razonLeida)); // Se inserta el registro en la lista
        }
        archivo.close();
    }
}

// Funciones que recibe como parametro una lista doblemente ligada y la ordena
// usando mergesort Complejidad: O(n log n)
template <typename T>
void mergeLists(DLinkedList<T>& list, DLinkedList<T>& left,
    DLinkedList<T>& right) {
    Node<T>* leftPtr = left.getHead();
    Node<T>* rightPtr = right.getHead();
    while (leftPtr != nullptr &&
        rightPtr != nullptr) { // Se comparan los elementos de las listas y se
        // insertan en la lista original
        if (leftPtr->getData() <= rightPtr->getData()) {
            list.addLast(leftPtr->getData());
            leftPtr = leftPtr->getNext();
        }
        else {
            list.addLast(rightPtr->getData());
            rightPtr = rightPtr->getNext();
        }
    }
    while (leftPtr !=
        nullptr) { // Se insertan los elementos restantes de la lista izquierda
        list.addLast(leftPtr->getData());
        leftPtr = leftPtr->getNext();
    }
    while (rightPtr !=
        nullptr) { // Se insertan los elementos restantes de la lista derecha
        list.addLast(rightPtr->getData());
        rightPtr = rightPtr->getNext();
    }
}

template <typename T> void mergeSort(DLinkedList<T>& list) {
    int listSize = list.getSize();
    if (listSize <= 1)
        return;
    int mid = listSize / 2;
    DLinkedList<T> left, right;
    Node<T>* current = list.getHead();
    for (int i = 0; i < mid; ++i) { // Se divide la lista en dos sublistas
        left.addLast(current->getData());
        current = current->getNext();
    }
    while (current !=
        nullptr) { // Se insertan los elementos restantes en la lista derecha
        right.addLast(current->getData());
        current = current->getNext();
    }
    mergeSort(left);
    mergeSort(right);
    list.clear();
    mergeLists(list, left, right);
}

// Funcion que recibe como parametro una lista doblemente ligada y la filtra
// segun un rango de IPs Complejidad: O(n)
template <typename T>
void filtrarDLLPorRango(DLinkedList<T>& list, DLinkedList<T>& listafiltradaDLL,
    T ipInicio, T ipFin) {
    mergeSort(list);
    Node<T>* current = list.getHead();
    while (current != nullptr) {
        if (typeid(current->getData()) == typeid(accesoFallido)) {
            if (current->getData().getIp() >= ipInicio.getIp() &&
                current->getData().getIp() <=
                ipFin.getIp()) { // Se filtra la lista segun el rango de IPs y se
                // almacena en una lista auxiliar
                listafiltradaDLL.addLast(current->getData());
            }
        }
        current = current->getNext();
    }
}

// Variables globales auxiliares
int opcionMenuPrincipal, opcionSubMenuBST, opcionSubMenuDLL = 0;
string ipInicialBST, ipFinalBST, ipInicialDLL, ipFinalDLL;
accesoFallido ipInicioBST, ipInicioDLL;
accesoFallido ipFinBST, ipFinDLL;

// Funcion principal
int main() {
    system("clear") || system("cls");
    cout << endl;
    cout << "Bienvenido al sistema de consultas de registros fallidos" << endl;
    cout << "Es posible hacer consultas usando BST o Listas doblemente ligadas"
        << endl;
    while (opcionMenuPrincipal != 4) {
        cout << endl;
        cout << "Elija una opcion del menu principal" << endl;
        cout << endl;
        cout << "1. BST" << endl;
        cout << "2. Listas doblemente ligadas" << endl;
        cout << "3. Limpiar pantalla" << endl;
        cout << "4. Salir" << endl;
        cout << endl;
        cout << "Opcion: ";
        cin >> opcionMenuPrincipal;
        switch (opcionMenuPrincipal) {
            // Menu de trabajo para BST
        case 1:
            cout << endl;
            leerArchivoBST("bitacora.txt"); // Se leen los registros del archivo y se
            // almacenan en un BST
            cout << endl;
            cout << "Ha elegido BST" << endl;
            while (opcionSubMenuBST != 4) {
                cout << endl;
                cout << "Elija una opcion para trabajar con los datos usando BST"
                    << endl;
                cout << endl;
                cout << "1. Imprimir los datos ordenados por IP y cantidad de accesos "
                    "(se creara un reporte .txt)"
                    << endl;
                cout << "2. Buscar registros dentro de un rango de IPs" << endl;
                cout << "3. Limpiar terminal" << endl;
                cout << "4. Regresar al menu principal" << endl;
                cout << endl;
                cout << "Opcion: ";
                cin >> opcionSubMenuBST;
                switch (opcionSubMenuBST) {
                    // Mostrar los registros ordenados por IP y por cantidad de accesos
                    // usando BST
                case 1:
                    cout << "Mostrando los registros ordenados por IP y por cantidad de "
                        "accesos"
                        << endl;
                    cout << endl;
                    arbol.printInorder(); // Se imprimen los registros ordenados por IP y
                    // por cantidad de accesos
                    arbol.printToFileInOrder(
                        "DatosOrdenadosBST.txt"); // Se crea un archivo .txt con los
                    // registros ordenados por IP y por
                    // cantidad de accesos
                    break;
                    // Mostrar los registros dentro de un rango de IPs usando BST
                case 2:
                    cout << "Ingrese el rango de IPs que desea buscar" << endl;
                    cout << "Especifique IP y puerto (ej. 997.95.633.17:6045)" << endl;
                    cout << endl;
                    cout << "IP inicial: ";
                    cin >> ipInicialBST;
                    ipInicioBST.setIp(ipInicialBST);
                    cout << "IP final: ";
                    cin >> ipFinalBST;
                    ipFinBST.setIp(ipFinalBST);
                    cout << endl;
                    cout << "Mostrando los registros dentro del rango de IPs" << endl;
                    cout << endl;
                    arbol.printInOrderAndInRange(
                        ipInicioBST,
                        ipFinBST); // Se imprimen los registros dentro del rango de IPs
                    break;
                    // Limpiar la terminal
                case 3:
                    system("clear") || system("cls");
                    break;
                    // Regresar al menu principal
                case 4:
                    break;
                    // Opcion invalida
                default:
                    cout << "Opcion invalida" << endl;
                    break;
                }
            }
            break;
            // Menu de trabajo para listas doblemente ligadas
        case 2:
            cout << endl;
            leerArchivoDLL(
                "bitacora.txt"); // Se leen los registros del archivo y se almacenan
            // en una lista doblemente ligada
            cout << endl;
            cout << "Ha elegido Listas doblemente ligadas" << endl;
            while (opcionSubMenuDLL != 4) {
                cout << endl;
                cout << "Elija una opcion para trabajar con los datos usando Listas "
                    "doblemente ligadas"
                    << endl;
                cout << endl;
                cout << "1. Imprimir los datos ordenados por IP y cantidad de accesos "
                    "(se creara un reporte .txt)"
                    << endl;
                cout << "2. Buscar registros dentro de un rango de IPs" << endl;
                cout << "3. Limpiar terminal" << endl;
                cout << "4. Regresar al menu principal" << endl;
                cout << endl;
                cout << "Opcion: ";
                cin >> opcionSubMenuDLL;
                switch (opcionSubMenuDLL) {
                    // Mostrar los registros ordenados por IP y por cantidad de accesos
                    // usando listas doblemente ligadas
                case 1:
                    cout << "Mostrando los registros ordenados por IP y por cantidad de "
                        "accesos"
                        << endl;
                    cout << endl;
                    mergeSort(DLL);
                    DLL.print();
                    DLL.printToFile(
                        "DatosOrdenadosDLL.txt"); // Se crea un archivo .txt con los
                    // registros ordenados por IP y por
                    // cantidad de accesos
                    break;
                    // Mostrar los registros dentro de un rango de IPs usando listas
                    // doblemente ligadas
                case 2:
                    cout << "Ingrese el rango de IPs que desea buscar" << endl;
                    cout << "Especifique IP y puerto (ej. 997.95.633.17:6045)" << endl;
                    cout << endl;
                    cout << "IP inicial: ";
                    cin >> ipInicialDLL;
                    ipInicioDLL.setIp(ipInicialDLL);
                    cout << "IP final: ";
                    cin >> ipFinalDLL;
                    ipFinDLL.setIp(ipFinalDLL);
                    cout << endl;
                    cout << "Mostrando los registros dentro del rango de IPs" << endl;
                    cout << endl;
                    filtrarDLLPorRango(
                        DLL, DLLFiltrada, ipInicioDLL,
                        ipFinDLL); // Se imprimen los registros dentro del rango de IPs
                    DLLFiltrada.print();
                    break;
                    // Limpiar la terminal
                case 3:
                    system("clear") || system("cls");
                    break;
                    // Regresar al menu principal
                case 4:
                    break;
                default:
                    cout << "Opcion invalida" << endl;
                    break;
                }
            }
            break;
            // Limpiar la terminal
        case 3:
            system("clear") || system("cls");
            break;
            // Salir del programa
        case 4:
            cout << endl;
            cout << "Saliendo ..." << endl;
            cout << endl;
            break;
        default:
            cout << "Opcion invalida" << endl;
            break;
        }
    }
    return 0;
}
