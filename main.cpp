#include <iostream>
#include <vector>


using namespace std;
//ESTRUCTURA FECHA-------------------------------------------------
struct Fecha {
    int anio;
    int mes;
    int dia;
    string Fecha_De_Entrada;
};
//FUNCIONES-------------------------------------------------
bool Validar_de_Fecha(int anio, int mes, int dia) {
    if(mes < 1 || mes > 12 )
    {
        cout << "Month value is invalid: MONTH" << endl;
        return false;
    }
    if (dia < 1 || dia > 31) 
    {
        cout << "Day value is invalid:DAY"<< endl;
        return false;
    }
    if(mes == 2) 
    {
        if(dia > 29)
        {
            cout << "Day value is invalid:DAY" << endl;
            return false;
        }
    }
    else if(mes == 4 || mes == 6 || mes == 9 || mes == 11) 
    {
        if(dia > 30) {
            cout << "Day value is invalid:DAY" << endl;
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

//-------------------------------------------------
int main () {
    vector<Fecha> fechas;
    string input;

    while(true) 
    {
        cout<<"introduzca la fecha: "<<endl;
        cin >> input;


    if(input == "print") 
    {
        for(const auto& fecha : fechas) {
            cout << "Fecha: " << fecha.Fecha_De_Entrada << endl;
            cout << "Anio: " << fecha.anio << endl;
            cout << "Mes: " << fecha.mes << endl;
            cout << "Dia " << fecha.dia << endl;
            cout << "-----------------------------------" << endl;
        }
    } 
    
    else if(input == "salir") 
    {
        break;
    }


    else 
    {
        if(contarGuiones(input) == 2) {
            Fecha fecha;
            if(sscanf(input.c_str(), "%d-%d-%d", &fecha.anio,&fecha.mes,&fecha.dia) == 3)
            {
                fecha.Fecha_De_Entrada = input;
                if(Validar_de_Fecha(fecha.anio,fecha.mes,fecha.dia)) {
                    fechas.push_back(fecha);
                    cout << "Saved Fecha" << endl;
                }
            } else {
                cout << "formato incorrecto fechas";
            }
        }
            else {
                cout << "formato incorrecto -";
            }
    
    } 
    }
    return 0; 
}