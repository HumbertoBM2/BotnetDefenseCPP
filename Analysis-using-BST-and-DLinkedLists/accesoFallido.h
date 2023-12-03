/*
------------------------------------------------------------------------------------------------------
Clase accesoFallido que sirve para mainuplar los registros de accesos fallidos
de la bitácora. Se hace uso de sbrecarga de operadores para facilitar la
comparación de los registros.

- Humberto Barrera Martínez

Fecha: 15 de octubre del 2023
------------------------------------------------------------------------------------------------------
*/

#ifndef accesoFallido_h
#define accesoFallido_h

#include <bits/stdc++.h>
using namespace std;

class accesoFallido {

  // Atributos privados de la clase
private:
  int mes;
  int dia;
  string hora;
  string ip;
  string razon;

  // Atributos públicos de la clase
public:
  // Constructores
  accesoFallido();
  accesoFallido(int mes, int dia, string hora, string ip, string razon);
  // Setters
  void setMes(int mes);
  void setDia(int dia);
  void setHora(string hora);
  void setIp(string ip);
  void setRazon(string razon);
  // Getters
  int getMes();
  string getMesString();
  int getDia();
  string getHora();
  string getIp();
  string getRazon();
  int getCantidadAccesos();
  // Otros métodos
  void muestraDatos();
  bool operator<=(accesoFallido otro);
  bool operator>=(accesoFallido otro);
  bool operator<(accesoFallido otro);
  bool operator>(accesoFallido otro);
  bool operator==(accesoFallido otro);
  bool operator!=(accesoFallido otro);
};

// Constructores
accesoFallido::accesoFallido() {
  this->mes = 0;
  this->dia = 0;
  this->hora = "";
  this->ip = "";
  this->razon = "";
}

accesoFallido::accesoFallido(int mes, int dia, string hora, string ip,
                             string razon) {
  this->mes = mes;
  this->dia = dia;
  this->hora = hora;
  this->ip = ip;
  this->razon = razon;
}

// Setters
void accesoFallido::setMes(int mes) { this->mes = mes; }

void accesoFallido::setDia(int dia) { this->dia = dia; }

void accesoFallido::setHora(string hora) { this->hora = hora; }

void accesoFallido::setIp(string ip) { this->ip = ip; }

void accesoFallido::setRazon(string razon) { this->razon = razon; }

// Getters
int accesoFallido::getMes() { return this->mes; }

string accesoFallido::getMesString() {
  if (mes == 1) {
    return "Jan";
  } else if (mes == 2) {
    return "Feb";
  } else if (mes == 3) {
    return "Mar";
  } else if (mes == 4) {
    return "Apr";
  } else if (mes == 5) {
    return "May";
  } else if (mes == 6) {
    return "Jun";
  } else if (mes == 7) {
    return "Jul";
  } else if (mes == 8) {
    return "Aug";
  } else if (mes == 9) {
    return "Sep";
  } else if (mes == 10) {
    return "Oct";
  } else if (mes == 11) {
    return "Nov";
  } else if (mes == 12) {
    return "Dec";
  } else {
    return "Mes no válido";
  }
}

int accesoFallido::getDia() { return this->dia; }

string accesoFallido::getHora() { return this->hora; }

string accesoFallido::getIp() { return this->ip; }

string accesoFallido::getRazon() { return this->razon; }

int accesoFallido::getCantidadAccesos() { return 1; }

// Otros métodos

// Método para mostrar los datos de un registro de acceso fallido
void accesoFallido::muestraDatos() {
  if (mes == 1) {
    cout << "Jan"
         << " " << dia << " " << hora << " " << ip << " " << razon << endl;
  } else if (mes == 2) {
    cout << "Feb"
         << " " << dia << " " << hora << " " << ip << " " << razon << endl;
  } else if (mes == 3) {
    cout << "Mar"
         << " " << dia << " " << hora << " " << ip << " " << razon << endl;
  } else if (mes == 4) {
    cout << "Apr"
         << " " << dia << " " << hora << " " << ip << " " << razon << endl;
  } else if (mes == 5) {
    cout << "May"
         << " " << dia << " " << hora << " " << ip << " " << razon << endl;
  } else if (mes == 6) {
    cout << "Jun"
         << " " << dia << " " << hora << " " << ip << " " << razon << endl;
  } else if (mes == 7) {
    cout << "Jul"
         << " " << dia << " " << hora << " " << ip << " " << razon << endl;
  } else if (mes == 8) {
    cout << "Aug"
         << " " << dia << " " << hora << " " << ip << " " << razon << endl;
  } else if (mes == 9) {
    cout << "Sep"
         << " " << dia << " " << hora << " " << ip << " " << razon << endl;
  } else if (mes == 10) {
    cout << "Oct"
         << " " << dia << " " << hora << " " << ip << " " << razon << endl;
  } else if (mes == 11) {
    cout << "Nov"
         << " " << dia << " " << hora << " " << ip << " " << razon << endl;
  } else if (mes == 12) {
    cout << "Dec"
         << " " << dia << " " << hora << " " << ip << " " << razon << endl;
  } else {
    cout << "Mes no válido" << endl;
  }
}

// Sobrecargar el operador <= para poder comparar los registros de acceso
// fallido segun el IP
bool accesoFallido::operator<=(accesoFallido otro) {
  if (this->ip <= otro.getIp()) {
    return true;
  } else {
    return false;
  }
}

// Sobrecargar el operador >= para poder comparar los registros de acceso
// fallido segun el IP
bool accesoFallido::operator>=(accesoFallido otro) {
  if (this->ip >= otro.getIp()) {
    return true;
  } else {
    return false;
  }
}

// Sobrecargar el operador < para poder comparar los registros de acceso fallido
// segun el IP
bool accesoFallido::operator<(accesoFallido otro) {
  if (this->ip < otro.getIp()) {
    return true;
  } else {
    return false;
  }
}

// Sobrecargar el operador > para poder comparar los registros de acceso fallido
// segun el IP
bool accesoFallido::operator>(accesoFallido otro) {
  if (this->ip > otro.getIp()) {
    return true;
  } else {
    return false;
  }
}

// Sobrecargar el operador == para poder comparar los registros de acceso
// fallido segun el IP
bool accesoFallido::operator==(accesoFallido otro) {
  if (this->ip == otro.getIp()) {
    return true;
  } else {
    return false;
  }
}

// Sobrecargar el operador != para poder comparar los registros de acceso
// fallido segun el IP
bool accesoFallido::operator!=(accesoFallido otro) {
  if (this->ip != otro.getIp()) {
    return true;
  } else {
    return false;
  }
}

#endif