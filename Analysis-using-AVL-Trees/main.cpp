
/* ----------------------------------------------------------------------------------------------------
main.cpp En este archivo se utilizan arboles AVL para analizar una serie de
Logs y determinar las IP's que han hecho más peticiones fallidas a un
servidor.

- Humberto Barrera Martinez

Fecha: 9 de noviembre del 2023
-----------------------------------------------------------------------------------------------------*/

#include "AVL.h"
#include "IPCount.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Se crea un arbol AVL para almacenar las IP's
AVL<IPCount> AVLTree;
// Se crea un mapa para almacenar las IP's y las veces que aparecen
std::map<std::string, int> IPMap;

// Funcion para leer el archivo de texto y almacenar las IP's en el mapa
bool readFile(std::string fileName, std::map<std::string, int> &IPMap) {
  // Leer el archivo de texto
  std::ifstream file(fileName);
  if (!file) {
    std::cerr << "Error al abrir el archivo." << std::endl;
    std::cout << std::endl;
    return false;
  }
  // Extraer las IP's del cada registro fallido (renglon)
  std::string registro;
  while (std::getline(file, registro)) {
    size_t colonPos = registro.rfind(":"); // Encuentra los dos puntos
    if (colonPos != std::string::npos) {
      size_t spacePos = registro.rfind(
          " ",
          colonPos - 1); // Encuentra el último espacio antes de los dos puntos
      if (spacePos != std::string::npos) {
        std::string ip = registro.substr(spacePos + 1, colonPos - spacePos - 1);
        // Se valida si la IP ya existe en el mapa y se aumenta el conteo, si no
        // existe se agrega y se le asigna un valor de 1
        auto it = IPMap.find(ip);
        if (it != IPMap.end()) {
          it->second++;
        } else {
          IPMap[ip] = 1;
        }
      }
    }
  }
  file.close();
  return true;
}

// Nota: los archivos .txt que se adjuntan con la entrga poseen la siguiente
// informacion:
// - bitacora.txt: Hay al menos 6 IP's con mas de una peticion fallida
// - bitacora2.txt: No hay ninguna IP con mas de una peticion fallida

// Funcion principal
int main() {
  // Se limpia la terminal
  system("clear") || system("cls");
  // Se inicializan las variables
  bool flagMenu = true;
  bool flagArchivo = false;
  int opcionLectura = 0, opcionMenu = 0;
  // Se crea un ciclo para mostrar el menu de lectura de archivos
  while (flagMenu) {
    opcionMenu = 0;
    flagArchivo = false;
    std::cout << std::endl;
    std::cout << "Bienvenido al programa de analisis de registros fallidos."
              << std::endl;
    std::cout
        << "Se utilizan arboles AVL para el analisis de los registros logs."
        << std::endl;
    std::cout << std::endl;
    std::cout << "Seleccione el archivo que desea analizar: " << std::endl;
    std::cout << "1. bitacora.txt" << std::endl;
    std::cout << "2. bitacora2.txt" << std::endl;
    std::cout << std::endl;
    std::cout << "Opcion: ";
    std::cin >> opcionLectura;
    std::cout << std::endl;
    switch (opcionLectura) {
    case 1:
      readFile("bitacora.txt", IPMap);
      flagArchivo = true;
      break;
    case 2:
      readFile("bitacora2.txt", IPMap);
      flagArchivo = true;
      break;
    default:
      std::cout << "Opcion invalida." << std::endl;
      std::cout << std::endl;
      break;
    }
    // Se crea un ciclo para mostrar el menu de opciones
    while (opcionMenu != 4) {
      std::cout
          << "Seleccione una opcion para analizar los logs de acceso fallido: "
          << std::endl;
      std::cout << "1. Mostrar las 5 IP's con mas peticiones fallidas."
                << std::endl;
      std::cout << "2. Leer otro archivo de texto." << std::endl;
      std::cout << "3. Limpiar terminal." << std::endl;
      std::cout << "4. Salir de la aplicacion." << std::endl;
      std::cout << std::endl;
      std::cout << "Opcion: ";
      std::cin >> opcionMenu;
      std::cout << std::endl;
      switch (opcionMenu) {
      // Se muestra el top 5 de las IP's con mas peticiones fallidas
      case 1:
        if (flagArchivo) {
          for (const auto &pair : IPMap) {
            // Agregar las IP's con mas de una peticion fallida al arbol AVL
            if (pair.second > 1) {
              AVLTree.push(IPCount(pair.first, pair.second));
            }
          }
          // Buscar si en el mapa hay una IP con mas de una peticion fallida
          if (AVLTree.empty()) {
            std::cout << "Ninguna IP ha hecho mas de una peticion fallida."
                      << std::endl;
          } else {
            std::cout << "Las 5 IP's con mas peticiones fallidas son: "
                      << std::endl;
            std::cout << std::endl;
            AVLTree.printReverseInOrderTop5();
          }
          // Se limpian las estructuras de datos
          std::cout << std::endl;
          AVLTree.clear();
          IPMap.clear();
        } else {
          // Si no se ha seleccionado un archivo se muestra un mensaje de error
          std::cout << "No se ha seleccionado un archivo." << std::endl;
          std::cout << std::endl;
        }
        flagArchivo = false;
        break;
      // Se muestra el menu de lectura de archivos
      case 2:
        std::cout << "Seleccione el archivo que desea analizar: " << std::endl;
        std::cout << "1. bitacora.txt" << std::endl;
        std::cout << "2. bitacora2.txt" << std::endl;
        std::cout << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opcionLectura;
        std::cout << std::endl;
        switch (opcionLectura) {
        case 1:
          flagArchivo = readFile("bitacora.txt", IPMap);
          break;
        case 2:
          flagArchivo = readFile("bitacora2.txt", IPMap);
          break;
        default:
          std::cout << "Opcion invalida." << std::endl;
          break;
        }
        break;
      // Se limpia la terminal
      case 3:
        system("clear") || system("cls");
        break;
      // Se sale de la aplicacion
      case 4:
        std::cout << "Saliendo de la aplicacion ..." << std::endl;
        std::cout << std::endl;
        flagMenu = false;
        break;
      // Se muestra un mensaje de error si la opcion no es valida
      default:
        std::cout << "Opcion invalida." << std::endl;
        std::cout << std::endl;
        break;
      }
    }
  }
  return 0;
}
