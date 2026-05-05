#include <iostream>
using namespace std;

int main() {

    float distancia;
    int tipoUsuario;
    float tarifaBase = 0.50;
    float total;

    cout << "Ingrese la distancia recorrida: ";
    cin >> distancia;

    cout << "Tipo de usuario:" << endl;
    cout << "1. General" << endl;
    cout << "2. Estudiante" << endl;
    cout << "3. Adulto mayor" << endl;
    cin >> tipoUsuario;

    total = distancia * tarifaBase;

    switch(tipoUsuario){

        case 1:
            break;

        case 2:
            total = total * 0.5;
            break;

        case 3:
            total = total * 0.3;
            break;

        default:
            cout << "Tipo de usuario invalido";
            return 0;
    }

    cout << "Total a pagar: $" << total;

    return 0;
}
