#include <vector>
#include <string>
#include <map>
using namespace std;
bool validarFecha(int anio, int mes, int dia);
std::string formatearFecha(int anio, int mes, int dia);
int contarGuiones(const string& str);
void insertarEventoEnOrden(vector<string>& eventos, const string& evento);
bool eliminarEvento(vector<string>& eventos, const string& evento);
void imprimirFechas(const map<string, vector<string>>& fechas);
