#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "funct-call.h"
#include "struct.h"
using namespace std;

int main() {
    map<string, vector<string>> fechas;
  cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
  cout << "Welcome to BD" << endl;
  cout << "Command list" << endl;
  cout << "- add | adds a date with its event format year-month-day event" << endl;
  cout << "- find | search for a specific date and print all its events" << endl;
  cout << "- print | print the entire bd" << endl;
  cout << "- del | remove a specific event from a date" << endl;
  cout << "- delall | removes all events from a date" << endl;
  cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << "\n"
       << endl;
  while (true) {
    string input;
    string errorformato = "[ERROR] Wrong date format: ";
    string errorcomando = "[ERROR] Unknown command: ";
    cout << ">> ";
    getline(cin, input);
    //=============================================================================================
    if (input.substr(0, 5) == "print") {
      imprimirFechas(fechas);
    }
    //=============================================================================================
    else if (input.substr(0, 5) == "salir") {
      break;
    }
    //=============================================================================================
    else if (input.substr(0, 3) == "add") {
      size_t firstSpace = input.find(' ', 4);
      if (firstSpace != string::npos) {
        string fechaStr = input.substr(4, firstSpace - 4);
        string evento = input.substr(firstSpace + 1);
        if (contarGuiones(fechaStr) == 2) {
          int anio, mes, dia;
          if (sscanf(fechaStr.c_str(), "%d-%d-%d", &anio, &mes, &dia) == 3) {
            if (validarFecha(anio, mes, dia)) {
              string fechaFormateada = formatearFecha(anio, mes, dia);
              insertarEventoEnOrden(fechas[fechaFormateada], evento);
              cout << "Date saved successfully" << endl;
            } else {
            }
          } else {
            cout << errorformato << fechaStr << endl;
          }
        } else {
          cout << errorformato << fechaStr << endl;
        }
      } else {
        cout << errorcomando << input << endl;
      }
    }
    //=============================================================================================
    else if (input.substr(0, 4) == "find") {
      string fechaStr = input.substr(5);
      if (contarGuiones(fechaStr) == 2) {
        int anio, mes, dia;
        if (sscanf(fechaStr.c_str(), "%d-%d-%d", &anio, &mes, &dia) == 3) {
          string fechaFormateada = formatearFecha(anio, mes, dia);
          auto it = fechas.find(fechaFormateada);
          if (it != fechas.end()) {
            cout << "Fecha: " << it->first << endl;
            for (const auto& evento : it->second) {
              cout << "  - " << evento << endl;
            }
          } else {
            cout << "[ERROR] Date not found" << endl;
          }
        } else {
          cout << errorformato << fechaStr << endl;
        }
      } else {
        cout << errorformato << fechaStr << endl;
      }
    }
    //=============================================================================================
    else if (input.substr(0, 6) == "delall") {
      string fechaStr = input.substr(7);
      if (contarGuiones(fechaStr) == 2) {
        int anio, mes, dia;
        if (sscanf(fechaStr.c_str(), "%d-%d-%d", &anio, &mes, &dia) == 3) {
          string fechaFormateada = formatearFecha(anio, mes, dia);
          auto it = fechas.find(fechaFormateada);
          if (it != fechas.end()) {
            int cantidadEliminada = it->second.size();
            fechas.erase(it);
            cout << "Deleted " << cantidadEliminada << " events" << endl;
          } else {
            cout << "[ERROR] Date not found" << fechaStr << endl;
          }
        } else {
          cout << errorformato << fechaStr << endl;
        }
      } else {
        cout << errorformato << fechaStr << endl;
      }
    }
    //=============================================================================================
    else if (input.substr(0, 3) == "del") {
      size_t firstSpace = input.find(' ', 4);
      if (firstSpace != string::npos) {
        string fechaStr = input.substr(4, firstSpace - 4);
        string evento = input.substr(firstSpace + 1);
        if (contarGuiones(fechaStr) == 2) {
          int anio, mes, dia;
          if (sscanf(fechaStr.c_str(), "%d-%d-%d", &anio, &mes, &dia) == 3) {
            if (validarFecha(anio, mes, dia)) {
              string fechaFormateada = formatearFecha(anio, mes, dia);
              auto it = fechas.find(fechaFormateada);
              if (it != fechas.end()) {
                if (eliminarEvento(it->second, evento)) {
                  cout << "Deleted successfully" << endl;
                } else {
                  cout << "[ERROR] Event not found" << endl;
                }
              } else {
                cout << "[ERROR] Date not found" << endl;
              }
            } else {
              cout << errorformato << endl;
            }
          } else {
            cout << errorformato << endl;
          }
        } else {
          cout << errorformato << endl;
        }
      } else {
        cout << errorcomando << endl;
      }
    }
    else if(input.substr(0,5) == "empty") {
      fechas.clear();
      cout << "The BD is empty" << endl;
    }
    else {
      cout << errorcomando << input << endl;
    }
  }
  return 0;
}