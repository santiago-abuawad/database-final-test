#include "funct-call.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;
//=============================================================================================
bool validarFecha(int anio, int mes, int dia) {
    if(anio == 0){
        cout << "Year value is invalid: " << anio << endl;
        return false;
    }
    if(mes > 12) {
        cout << "Month value is invalid: " << mes << endl;
        return false;
    }
    if(dia == 0 && dia > 30) {
        cout << "Day value is invalid: " << dia << endl;
        return false;
    }
    return true;
}
//=============================================================================================
string formatearFecha(int anio, int mes, int dia) {
    return (anio < 10 ? "000" : (anio < 100 ? "00" : (anio < 1000 ? "0" : ""))) + to_string(anio) + "-" + (mes < 10 ? "0" : "") + to_string(mes) + "-" + (dia < 10 ? "0" : "") + to_string(dia);
}
//=============================================================================================
int contarGuiones(const string& str) {
    int count = 0;
    for (char c : str) {
        if (c == '-') {
            count++;
        }
    }
    return count;
}
//=============================================================================================
void insertarEventoEnOrden(vector<string>& eventos, const string& evento) {
    auto it = eventos.begin();
  while (it != eventos.end() && *it < evento) {
        ++it;
    }
  if(it == eventos.end() || *it != evento) {
        eventos.insert(it,evento);
    }
}
//=============================================================================================
bool eliminarEvento(vector<string>& eventos, const string& evento) {
    for (auto it = eventos.begin(); it != eventos.end(); ++it) {
        if (*it == evento) {
            eventos.erase(it);
            return true;
        }
    }  
    return false;
}
//=============================================================================================
void imprimirFechas(const map<string, vector<string>>& fechas) {
    for (const auto& par : fechas) {
        cout << "Fecha: " << par.first << endl;
        for (const auto& evento : par.second) {
            cout << "  - " << evento << endl;
        }
        cout << "-----------------------------------" << endl;
    }
}