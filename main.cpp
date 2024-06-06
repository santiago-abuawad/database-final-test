#include <iostream>
#include <vector>
#include <map>

using namespace std;

// ESTRUCTURA FECHA-------------------------------------------------
struct Fecha {
    int anio;
    int mes;
    int dia;
};

// FUNCIONES-------------------------------------------------
bool validarFecha(int anio, int mes, int dia) {
    if(anio == 0) {
        cout << "Year value is invalid: " << anio << endl;
        return false;
    }
    if(mes < 1 || mes > 12 )
    {
        cout << "Month value is invalid: "<< mes << endl;
        return false;
    }
    if (dia < 1 || dia > 31) 
    {
        cout << "Day value is invalid: "<<dia<<endl;
        return false;
    }
    if(mes == 2) 
    {
        if(dia > 29)
        {
            cout << "Day value is invalid: "<< dia << endl;
            return false;
        }
    }
    else if(mes == 4 || mes == 6 || mes == 9 || mes == 11) 
    {
        if(dia > 30) {
            cout << "Day value is invalid: "<< dia << endl;
            return false;
        }
    }
    return true;
}

int contarGuiones(const string& str) {
    int count = 0;
    for (char c : str) {
        if (c == '-') {
            count++;
        }
    }
    return count;
}

string formatearFecha(int anio, int mes, int dia) {
    return to_string(anio) + "-" + (mes < 10 ? "0" : "") + to_string(mes) + "-" + (dia < 10 ? "0" : "") + to_string(dia);
}

void insertarEventoEnOrden(vector<string>& eventos, const string& evento) {
    auto it = eventos.begin();
    while (it != eventos.end() && *it < evento) {
        ++it;
    }
    eventos.insert(it, evento);
}

void imprimirFechas(const map<string, vector<string>>& fechas) {
    for (const auto& par : fechas) {
        cout << "Fecha: " << par.first << endl;
        for (const auto& evento : par.second) {
            cout << "  - " << evento << endl;
        }
        cout << "-----------------------------------" << endl;
    }
}

bool eliminarEvento(vector<string>& eventos, const string& evento) {
    for (auto it = eventos.begin(); it != eventos.end(); ++it) {
        if (*it == evento) {
            eventos.erase(it);
            return true;
        }
    }
    return false;
}

//-------------------------------------------------
int main() {
    map<string, vector<string>> fechas;
    string input;

    while (true) {
        string errorformato = "[ERROR] Incorrect format: ";
        string errorcomando = "[ERROR] Unknown command: ";
        cout << ">> ";
        getline(cin, input);

        if (input.substr(0, 5) == "print") {
            imprimirFechas(fechas);
        } else if (input.substr(0, 5) == "salir") {
            break;
        } else if (input.substr(0, 3) == "add") {
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
        } else if (input.substr(0, 4) == "find") {
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
                        cout << "Date not found" << endl;
                    }
                } else {
                    cout << errorformato << endl;
                }
            } else {
                cout << errorformato << endl;
            }
        } else if (input.substr(0, 3) == "del") {
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
                                cout << "Date not found" << endl;
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
        } else if (input.substr(0, 6) == "delall") {
            string fechaStr = input.substr(7);
            if (contarGuiones(fechaStr) == 2) {
                int anio, mes, dia;
                if (sscanf(fechaStr.c_str(), "%d-%d-%d", &anio, &mes, &dia) == 3) {
                    string fechaFormateada = formatearFecha(anio, mes, dia);
                    auto it = fechas.find(fechaFormateada);
                    if (it != fechas.end()) {
                        int cantidadEliminada = it->second.size();
                        fechas.erase(it);
                        cout << "Deleted" << cantidadEliminada << "Events"<< endl;
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
            cout << errorcomando << endl;
        }
    }
    return 0;
}
