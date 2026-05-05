#include <iostream>
using namespace std;

int main() {
    char cadena[100];
    int i = 0, j = 0;
    bool palindromo = true;

    cout << "Ingrese una cadena: ";
    cin >> cadena;

    // Calcular longitud
    while (cadena[j] != '\0') {
        j++;
    }

    j--; // último carácter

    // Comparar extremos
    while (i < j) {
        if (cadena[i] != cadena[j]) {
            palindromo = false;
        }
        i++;
        j--;
    }

    if (palindromo)
        cout << "Es palindromo";
    else
        cout << "No es palindromo";

    return 0;
}
