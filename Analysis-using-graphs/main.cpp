/* ----------------------------------------------------------------------------------------------------
Archivo main.cpp en donde se utilizan grafos para encontrar el boot master de un
ataque de botnets.

- Humberto Barrera Martinez

Fecha: 21 de noviembre del 2023
-----------------------------------------------------------------------------------------------------*/

#include "grafo.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Función para construir la matriz de adyacencia de las IPs con respecto al
// octeto de red Complejidad: O(n)
void construirMatrizAdyacencia(const vector<string> &logs,
                               unordered_map<int, vector<string>> &matriz) {
  for (const string &log : logs) {
    istringstream iss(log);
    string mes, dia, hora, ip, ipYPuerto;
    // Leer cada log
    iss >> mes >> dia >> hora >> ipYPuerto;
    // Obtener la IP sin el puerto
    ip = ipYPuerto.substr(0, ipYPuerto.find(':'));
    // Obtener el primer octeto de la IP
    size_t pos = ip.find('.');
    if (pos != string::npos) {
      string primerOcteto = ip.substr(0, pos);
      // Agregar la IP completa a la lista de adyacencias del primer octeto
      matriz[stoi(primerOcteto)].push_back(ip);
    }
  }
}

// Función para guardar la matriz de adyacencia en un archivo .txt
// Complejidad: O(n)
void guardarMatrizArchivo(const unordered_map<int, vector<string>> &matriz,
                          const string &nombreArchivo) {
  ofstream archivo(nombreArchivo);
  if (archivo.is_open()) {
    // Guardar la matriz de adyacencia en un archivo
    for (const auto &par : matriz) {
      archivo << par.first << " ";
      for (const string &ip : par.second) {
        archivo << ip << " ";
      }
      archivo << endl;
    }
    archivo.close();
    cout << endl;
    cout << "Matriz de adyacencia guardada en " << nombreArchivo << endl;
  } else {
    cout << endl;
    cerr << "No se pudo abrir el archivo de salida." << endl;
  }
}

// Funcion main
int main() {
  // Variables de la aplicacion
  grafo grafoIPs;
  nodo *nodoIP;
  vector<string> logs;
  string linea, linea2, id, idAdyacencia;
  unordered_map<int, vector<string>> matrizAdyacencia;
  unordered_map<int, int> numAdyacenciasPorRed;
  int bootMaster = -1, maxAdyacencias = -1;
  string continuar;
  // Limpiar la consola
  system("cls") || system("clear");
  // Imprimir instrucciones
  cout << endl;
  cout << "Bienvenido al programa para encontrar el boot master de un ataque "
          "de botnets."
       << endl;
  cout << endl;
  cout << "Metodologia:" << endl;
  cout << "- Se lee un archivo de logs y se crea un grafo con las IPs que "
          "hicieron solicitudes fallidas."
       << endl;
  cout << "- Se encuentra el octeto de red con mas solicitudes fallidas y se "
          "marca como el boot master."
       << endl;
  cout << "- Se muestran las IPs conectadas a la red del boot master que "
          "hicieron solicitudes fallidas."
       << endl;
  cout << "- Se recomienda bloquear todas las solicitudes provenientes de la "
          "red del boot master."
       << endl;
  cout << endl;
  cout << "Presiona ENTER para continuar (Se limpiara la pantalla)...";
  getline(cin, continuar);
  system("cls") || system("clear");
  cout << endl;
  cout << "A continuacion, se leera el archivo de logs bitacora.txt y se "
          "creara una matriz de adyacencia."
       << endl;
  cout << endl;
  cout << "Presiona ENTER para continuar (Se limpiara la pantalla)...";
  getline(cin, continuar);
  system("cls") || system("clear");
  // Abrir y leer el archivo de logs
  ifstream archivo(
      "bitacora.txt"); // Reemplaza con el nombre de tu archivo de logs
  if (!archivo) {
    cout << endl;
    cerr << "No se pudo abrir el archivo de logs." << endl;
    return 1;
  }
  // Leer cada linea del archivo y guardarla en un vector
  while (getline(archivo, linea)) {
    logs.push_back(linea);
  }
  archivo.close();
  // Crear matriz de adyacencia de las IPs con respecto al octeto de red
  construirMatrizAdyacencia(logs, matrizAdyacencia);
  // Guardar la matriz de adyacencia en un archivo
  guardarMatrizArchivo(matrizAdyacencia, "matrizAdyacenciaIPs.txt");
  // Leer la matriz de adyacencia y crear el grafo
  cout << endl;
  cout << "A continuacion, se leera el archivo de la matriz de adyacencia y se "
          "creara el grafo."
       << endl;
  cout << "Se mostrara el numero de dispositivos de cada red que hicieron "
          "solicitudes fallidas."
       << endl;
  cout << endl;
  cout << "Presiona ENTER para continuar (Se limpiara la pantalla)...";
  getline(cin, continuar);
  system("cls") || system("clear");
  ifstream archivoMatriz("matrizAdyacenciaIPs.txt");
  if (!archivoMatriz) {
    cout << endl;
    cerr << "No se pudo abrir el archivo de la matriz de adyacencia." << endl;
    return 1;
  }
  // Crear cada nodo del grafo con su lista de adyacencias
  while (archivoMatriz >> id) {
    getline(archivoMatriz, linea2);
    istringstream iss(linea2);
    nodoIP = grafoIPs.addNodo(id);
    getline(iss, idAdyacencia, ' ');
    while (getline(iss, idAdyacencia, ' ')) {
      grafoIPs.addAdyacencia(nodoIP, idAdyacencia);
    }
    // Guardar el numero de adyacencias de cada nodo
    int numAdyacencias = nodoIP->getNumAdyacencias();
    cout << "Octeto de red: " << nodoIP->Id()
         << "\tNumero de dispositivos de esa red que hicieron solicitudes "
            "fallidas: "
         << nodoIP->getNumAdyacencias() << endl;
    numAdyacenciasPorRed[stoi(id)] += numAdyacencias;
  }
  archivoMatriz.close();
  cout << endl;
  cout << "Se ha creado el grafo." << endl;
  cout << endl;
  cout << "Se hara un conteo de las adyacencias de cada octeto de red para "
          "encontrar el boot master."
       << endl;
  cout << "Se mostrara el boot master y sus dispositivos." << endl;
  cout << endl;
  cout << "Presiona ENTER para continuar (Se limpiara la pantalla)...";
  getline(cin, continuar);
  system("cls") || system("clear");
  // Encontrar el boot master (octeto de red con mas adyacencias)
  for (const auto &par : numAdyacenciasPorRed) {
    if (par.second > maxAdyacencias) {
      maxAdyacencias = par.second;
      bootMaster = par.first;
    }
  }
  // Imprimir el boot master y sus dispositivos
  cout << endl
       << "El boot master presuntamente es el octeto de red: " << bootMaster
       << endl;
  cout << endl << "IPs de los dispositivos de la red del boot master:" << endl;
  for (const string &ip : matrizAdyacencia[bootMaster]) {
    cout << ip << endl;
  }
  cout << endl;
  cout << "Recomendacion: Bloquear todas las solicitudes provenientes de la "
          "red del boot master."
       << endl;
  cout << endl;
  cout << "Presiona ENTER para salir del programa ...";
  getline(cin, continuar);
  cout << endl;
  return 0;
}