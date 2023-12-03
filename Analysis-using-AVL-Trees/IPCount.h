
/* ----------------------------------------------------------------------------------------------------
Clase IPCount que sirve para manejar IPs y cantidad de apariciones en un reporte
de accesos fallidos

- Humberto Barrera Martinez

Fecha: 9 de noviembre del 2023
-----------------------------------------------------------------------------------------------------*/

#ifndef IPCount_h
#define IPCount_h

#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

class IPCount {

  // Atributos privados
private:
  std::string ip;
  int count;

  // Atributos publicos
public:
  // Constructores
  IPCount();
  IPCount(const std::string &ip);
  IPCount(const std::string &ip, int count);

  // Destructor
  ~IPCount();

  // Getters
  const std::string &getIP() const;
  int getCount() const;

  // Setters
  void setIP(const std::string &ip);
  void setCount(int count);

  // Metodo
  unsigned int ipToInteger(const std::string &ip) const;

  // Sobrecargamos el operador <
  bool operator<(const IPCount &other) const;
  bool operator>(const IPCount &other) const;
  bool operator==(const IPCount &other) const;
  bool operator!=(const IPCount &other) const;

  // Imprimir
  void print();

  // Incrementar el conteo
  void incrementCount();
};

// Constructores
IPCount::IPCount() {
  ip = "";
  count = 0;
}

IPCount::IPCount(const std::string &ip) {
  this->ip = ip;
  count = 1;
}

IPCount::IPCount(const std::string &ip, int count) {
  this->ip = ip;
  this->count = count;
}

// Destructor
IPCount::~IPCount() {
  ip = "";
  count = 0;
}

// Getters
const std::string &IPCount::getIP() const { return ip; }

int IPCount::getCount() const { return count; }

// Setters
void IPCount::setIP(const std::string &ip) { this->ip = ip; }

void IPCount::setCount(int count) { this->count = count; }

// Metodos

// Metodo para convertir una IP a un entero
unsigned int IPCount::ipToInteger(const std::string &ip) const {
  std::vector<int> parts;
  std::stringstream ss(ip);
  std::string part;
  while (getline(ss, part, '.')) {
    parts.push_back(std::stoi(part));
  }
  if (parts.size() != 4) {
    throw std::invalid_argument("IP invalida");
  }
  unsigned int result = 0;
  for (int i = 0; i < 4; ++i) {
    result = (result << 8) | parts[i];
  }
  return result;
}

// Sobrecarga de operadores

bool IPCount::operator<(const IPCount &other) const {
  if (count == other.count) {
    return ipToInteger(ip) < ipToInteger(other.getIP());
  } else {
    return count < other.count;
  }
}

bool IPCount::operator>(const IPCount &other) const {
  if (count == other.count) {
    return ipToInteger(ip) > ipToInteger(other.getIP());
  } else {
    return count > other.count;
  }
}

bool IPCount::operator==(const IPCount &other) const {
  return count == other.count;
}

bool IPCount::operator!=(const IPCount &other) const {
  return count != other.count;
}

// Imprimir
void IPCount::print() { std::cout << ip << " " << count << std::endl; }

// Incrementar el conteo
void IPCount::incrementCount() { count++; }

#endif