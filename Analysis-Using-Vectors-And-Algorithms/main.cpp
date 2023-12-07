/*
------------------------------------------------------------------------------------------------------
Archivo main.cpp

- Humberto Barrera Martínez

Fecha: 2 de septiembre del 2023
------------------------------------------------------------------------------------------------------
*/

#include "accesoFallido.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define ar array
#define vt vector
#define pb push_back

// Algoritmos de ordenamiento

// Función para ordenar en forma ascendente los datos de un vector con el método
// de Merge Complejidad: O(n log n)
template <typename T> void ordenaMerge(vt<T>& arr, int izq, int der) {
    if (izq < der) {
        int mid = izq + (der - izq) / 2; // Se obtiene el punto medio
        ordenaMerge(arr, izq, mid);      // Se ordena la primera mitad
        ordenaMerge(arr, mid + 1, der);  // Se ordena la segunda mitad

        vt<T> tempArr(
            der - izq +
            1); // Se crea un vector temporal para almacenar los datos ordenados
        int i = izq, j = mid + 1, k = 0; // Se inicializan los indices de los
        // subvectores y del vector temporal

        while (i <= mid &&
            j <= der) {        // Se comparan los elementos de los subvectores
            if (arr[i] <= arr[j]) { // Si el elemento de la primera mitad es menor o
                // igual al de la segunda mitad
                tempArr[k++] = arr[i++]; // Se agrega el elemento de la primera mitad al
                // vector temporal
            }
            else { // Si el elemento de la segunda mitad es menor al de la primera
                // mitad
                tempArr[k++] = arr[j++]; // Se agrega el elemento de la segunda mitad al
                // vector temporal
            }
        }

        while (i <= mid) { // Se agregan los elementos restantes de la primera mitad
            // al vector temporal
            tempArr[k++] = arr[i++];
        }

        while (j <= der) { // Se agregan los elementos restantes de la segunda mitad
            // al vector temporal
            tempArr[k++] = arr[j++];
        }

        for (int p = 0; p < k; ++p) { // Se copian los elementos del vector temporal
            // al vector original
            arr[izq + p] = tempArr[p];
        }
    }
}

// Algoritmos de búsqueda

// Función para buscar un elemento en un vector con el método de Búsqueda
// Secuencial Complejidad: O(n)
template <typename T> int busqSecuencial(const vt<T>& arr, T numBuscado) {
    for (int i = 0; i < arr.size(); ++i) { // Se recorre el vector
        if (arr[i] == numBuscado) { // Si el elemento actual es el buscado se
            // retorna su indice
            return i;
        }
    }
    return -1;
}

// Función para buscar un elemento en un vector con el método de Búsqueda
// Secuencial Inversa Complejidad: O(n)
template <typename T>
int busqSecuencialInversa(const vt<T>& arr, T elementoBuscado) {
    for (int i = arr.size() - 1; i >= 0; --i) { // Se recorre el vector
        if (arr[i] == elementoBuscado) { // Si el elemento actual es el buscado se
            // retorna su indice
            return i;
        }
    }
    return -1;
}

// Función para buscar un elemento en un vector con el método de Búsqueda
// Binaria Complejidad: O(log n)
template <typename T> int busqBinaria(const vt<T>& arr, T elementoBuscado) {
    int izq = 0;
    int der = arr.size() - 1;

    while (izq <=
        der) { // Se realiza la búsqueda mientras el subvector tenga elementos
        int mid = izq + (der - izq) / 2; // Se obtiene el punto medio

        if (arr[mid] == elementoBuscado) { // Si el elemento del punto medio es el
            // buscado se retorna su indice
            return mid;
        }

        if (arr[mid] <
            elementoBuscado) { // Si el elemento del punto medio es menor al
            // buscado, se busca en la segunda mitad
            izq = mid + 1;       // Se actualiza el indice izquierdo
        }
        else { // Si el elemento del punto medio es mayor al buscado, se busca en
            // la primera mitad
            der = mid - 1; // Se actualiza el indice derecho
        }
    }

    return -1;
}

// Funciones para el programa

// Función para generar un reporte con los registros de accesos fallidos según
// la solicitud del usuario Complejidad: O(n)
void generarReporte(vt<accesoFallido>& registrosAGuardar,
    const string& nombreReporte) {
    ofstream archivoReporteOpcion1(
        nombreReporte); // Se crea un archivo de texto para almacenar el reporte
    // de la opción 1
    if (!archivoReporteOpcion1) {
        cout << endl;
        cout << "Error al crear el archivo ReporteOpcion1.txt." << endl;
        return;
    }

    for (int i = 0; i < registrosAGuardar.size();
        i++) { // Se recorre el vector de registros
        archivoReporteOpcion1
            << registrosAGuardar[i].getMesString() << " "
            << registrosAGuardar[i].getDia() << " "
            << registrosAGuardar[i].getHora() << " " << registrosAGuardar[i].getIp()
            << " " << registrosAGuardar[i].getRazon()
            << endl; // Se escribe el registro en el archivo de texto
    }
    archivoReporteOpcion1.close(); // Se cierra el archivo de texto
    cout << "Se ha generado el reporte bajo el nombre: " << nombreReporte
        << endl; // Se muestra el nombre del archivo de texto generado
}

// Función que recibe el vector de registros ordenados y genera un vector con
// los registros filtrados por un rango de fechas elegido por el usuario
// Complejidad: O(n)
void filtrarPorRangoUsuario(vt<accesoFallido>& registrosFiltradosRango,
    int mesInicio, int mesFin, int diaInicio,
    int diaFin) {

    // Se filtran los registros por rango de fechas
    for (int i = 0; i < registrosFiltradosRango.size(); ++i) {
        if (registrosFiltradosRango[i].getMes() < mesInicio ||
            registrosFiltradosRango[i].getMes() >
            mesFin) { // Si el mes del registro no está en el rango de meses
            // elegido por el usuario
            registrosFiltradosRango.erase(
                registrosFiltradosRango.begin() +
                i); // Se elimina el registro del vector de registros filtrados por
            // rango de fechas
            --i;    // Se decrementa el indice para no saltarse el siguiente registro
        }
        else if (registrosFiltradosRango[i].getMes() == mesInicio &&
            registrosFiltradosRango[i].getDia() <
            diaInicio) { // Si el mes del registro es igual al mes de
            // inicio del rango de fechas y el dia del
            // registro es menor al dia de inicio del rango
            // de fechas
            registrosFiltradosRango.erase(
                registrosFiltradosRango.begin() +
                i); // Se elimina el registro del vector de registros filtrados por
            // rango de fechas
            --i;    // Se decrementa el indice para no saltarse el siguiente registro
        }
        else if (registrosFiltradosRango[i].getMes() == mesFin &&
            registrosFiltradosRango[i].getDia() >
            diaFin) { // Si el mes del registro es igual al mes de fin
            // del rango de fechas y el dia del registro es
            // mayor al dia de fin del rango de fechas
            registrosFiltradosRango.erase(
                registrosFiltradosRango.begin() +
                i); // Se elimina el registro del vector de registros filtrados por
            // rango de fechas
            --i;    // Se decrementa el indice para no saltarse el siguiente registro
        }
    }
}

// Función que recibe el vector de registros filtrados por rango de fechas y los
// ordena de forma descendente según la cantidad de accesos Complejidad: O(n)
void ordenarPorCantidadDeAccesos(vt<accesoFallido>& registrosFiltradosRango) {
    // Se crea un vector para almacenar la cantidad de accesos por IP
    vt<int> cantidadAccesosPorIp;
    cantidadAccesosPorIp.pb(1); // Se inicializa la cantidad de accesos en 1

    // Se crea un vector para almacenar las IPs
    vt<string> ips;
    ips.pb(registrosFiltradosRango[0]
        .getIp()); // Se agrega la primera IP al vector de IPs

    // Se recorre el vector de registros filtrados por rango de fechas
    for (int i = 1; i < registrosFiltradosRango.size(); ++i) {
        int indiceIp =
            busqSecuencial(ips, registrosFiltradosRango[i]
                .getIp()); // Se busca la IP en el vector de IPs
        if (indiceIp == -1) { // Si la IP no está en el vector de IPs
            ips.pb(registrosFiltradosRango[i]
                .getIp());       // Se agrega la IP al vector de IPs
            cantidadAccesosPorIp.pb(1); // Se inicializa la cantidad de accesos en 1
        }
        else {                      // Si la IP está en el vector de IPs
            ++cantidadAccesosPorIp[indiceIp]; // Se incrementa la cantidad de accesos
            // de la IP
        }
    }

    // Se crea un nuevo vector para almacenar los registros ordenados
    vt<accesoFallido> registrosOrdenados = registrosFiltradosRango;

    // Se ordenan los registros filtrados por rango de fechas de forma descendente
    // según la cantidad de accesos usando merge sort
    ordenaMerge(cantidadAccesosPorIp, 0, cantidadAccesosPorIp.size() - 1);

    registrosFiltradosRango =
        registrosOrdenados; // Se actualiza el vector original con los registros
    // ordenados
}

int main() {

    ifstream archivoRegistros(
        "bitacora.txt"); // Se abre el archivo de texto con los registros de
    // accesos fallidos
// Se valida que se haya abierto correctamente el archivo
    if (!archivoRegistros) {

        cout << endl;
        cout << "Error al abrir el archivo bitacora.txt." << endl;

    }
    else {

        cout << endl;
        cout << "Archivo bitacora.txt abierto correctamente." << endl;
    }

    vt<accesoFallido> vectorRegistros; // Se crea un vector para almacenar los
    // registros de accesos fallidos
    string lineaLeida; // Se crea una variable para almacenar la linea leida del
    // archivo de texto

    while (getline(archivoRegistros, lineaLeida)) {

        istringstream linea(lineaLeida);  // Se crea un objeto de tipo istringstream
        // para leer la línea leída
        accesoFallido registroIndividual; // Se crea un objeto de tipo accesoFallido
        // para almacenar los datos de un registro
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
        vectorRegistros.pb(accesoFallido(
            mesLeidoNumerico, diaLeido, horaLeida, ipLeida,
            razonLeida)); // Se agrega el registro al vector de registros
    }

    archivoRegistros.close(); // Se cierra el archivo de texto
    ordenaMerge(vectorRegistros, 0,
        vectorRegistros.size() -
        1); // Se ordena el vector de registros por fecha

    // Menú de opciones
    int opcionMenu = 0;
    cout << endl;
    cout << "Bienvenido al sistema de consulta de accesos fallidos." << endl;
    cout << endl;
    cout << "Los datos han sido ordenados por fecha." << endl;

    while (opcionMenu != 5) {

        cout << endl;
        cout << "Por favor, seleccione una opcion del menu:" << endl;
        cout << "1. Mostrar todos los accesos fallidos registrados (ordenados por "
            "mes)"
            << endl;
        cout << "2. Mostrar accesos fallidos en un rango de fechas (ordenados de "
            "forma descendente por cantidad de accesos segun la IP)"
            << endl;
        cout << "3. Mostrar conteo de accesos fallidos por mes" << endl;
        cout << "4. Limpiar terminal" << endl;
        cout << "5. Salir" << endl;
        cout << "Nota: Cada vez que se filtren los datos, se creara un archivo de "
            "texto con los resultados."
            << endl;
        cout << endl;
        cout << "Opcion: ";
        cin >> opcionMenu;

        if (opcionMenu == 1) {

            // Se despliegan todos los accesos fallidos registrados (ordenados por
            // mes)
            cout << endl;
            cout << "Desplegando todos los accesos fallidos registrados ..." << endl;
            for (int i = 0; i < vectorRegistros.size(); ++i) {
                vectorRegistros[i].muestraDatos();
            }
            generarReporte(
                vectorRegistros,
                "ReporteOpcion1.txt"); // Se genera el reporte de la opción 1

        }
        else if (opcionMenu == 2) {

            int mesInicio = 0;
            int mesFin = 0;
            int diaInicio = 0;
            int diaFin = 0;
            cout << endl;
            cout << "Por favor, ingrese el numero de mes de inicio del rango de "
                "fechas (1 al 12): ";
            cin >> mesInicio;
            cout << "Por favor, ingrese el dia de inicio del rango de fechas (1 al "
                "31): ";
            cin >> diaInicio;
            cout << "Por favor, ingrese el numero mes de fin del rango de fechas (1 "
                "al 12): ";
            cin >> mesFin;
            cout
                << "Por favor, ingrese el dia de fin del rango de fechas (1 al 31): ";
            cin >> diaFin;
            vt<accesoFallido>
                registrosFiltradosRango; // Se crea un vector para almacenar los
            // registros filtrados por rango de fechas
            int cantidadAccesos = 0;     // Se inicializa la cantidad de accesos en 0
            registrosFiltradosRango =
                vectorRegistros; // Se copia el vector de registros al vector de
            // registros filtrados por rango de fechas
            filtrarPorRangoUsuario(
                registrosFiltradosRango, mesInicio, mesFin, diaInicio,
                diaFin); // Se filtran los registros por rango de fechas
            ordenarPorCantidadDeAccesos(
                registrosFiltradosRango); // Se ordenan los registros filtrados por
            // rango de fechas por cantidad de accesos

            cout << endl;
            cout << "Desplegando los accesos fallidos de " << mesInicio << "/"
                << diaInicio << " a " << mesFin << "/" << diaFin << " ..." << endl;
            cout << endl;
            for (int i = 0; i < registrosFiltradosRango.size(); ++i) {
                registrosFiltradosRango[i].muestraDatos();
            }
            cout << endl;
            generarReporte(
                registrosFiltradosRango,
                "ReporteOpcion2.txt"); // Se genera el reporte de la opción 2

        }
        else if (opcionMenu == 3) {

            // Se despliega el conteo de accesos fallidos por mes
            ofstream archivoReporteOpcion3(
                "ReporteOpcion3.txt"); // Se crea un archivo de texto para almacenar
            // el reporte de la opción 3
            cout << endl;
            cout << "Desplegando el conteo de accesos fallidos por mes ..." << endl;
            int cantidadAccesos = 0; // Se inicializa la cantidad de accesos en 0
            for (int i = 1; i <= 12; ++i) { // Se recorren los meses
                for (int j = 0; j < vectorRegistros.size();
                    ++j) { // Se recorren los registros
                    if (vectorRegistros[j].getMes() ==
                        i) {             // Si el mes del registro es igual al mes actual
                        ++cantidadAccesos; // Se incrementa la cantidad de accesos
                    }
                }
                cout << "Mes: " << i << " Cantidad de accesos: " << cantidadAccesos
                    << endl; // Se muestra el mes y la cantidad de accesos
                // Se guarda el conteo en el .txt
                archivoReporteOpcion3
                    << "Mes: " << i
                    << " Cantidad de accesos fallidos: " << cantidadAccesos << endl;
                cantidadAccesos = 0; // Se reinicia la cantidad de accesos
            }

            archivoReporteOpcion3.close(); // Se cierra el archivo de texto
            cout << endl;
            cout << "Se genero un reporte bajo el nombre ReporteOpcion3.txt." << endl;

        }
        else if (opcionMenu == 4) {

            // Se limpia la terminal
            system("cls") || system("clear");

        }
        else if (opcionMenu == 5) {

            cout << endl;
            cout << "Saliendo ..." << endl;

        }
        else {

            cout << endl;
            cout << "Opcion invalida. Por favor, seleccione una opcion valida."
                << endl;
        }
    }

    return 0;
}