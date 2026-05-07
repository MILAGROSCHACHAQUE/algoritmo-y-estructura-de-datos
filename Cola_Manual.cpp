#include <iostream>
#include <conio.h>
using namespace std;

struct Nodo {
    int dato;
    Nodo *siguiente;
};

// Prototipos con validación
void insertarCola(Nodo *&, Nodo *&, int);
bool colaVacia(Nodo *);
void eliminarCola(Nodo *&, Nodo *&, int &);

int main() {
    Nodo *frente = NULL;
    Nodo *fin = NULL;
    int dato;
    char rpt;

    // 1. Inserción de valores
    do {
        cout << "Digite un numero: ";
        if (!(cin >> dato)) { // Validación de entrada no numérica
            cout << "Entrada invalida.";
            break;
        }
        
        insertarCola(frente, fin, dato);
        
        cout << "Desea ingresar otro (s/n): ";
        cin >> rpt;
    } while (rpt == 's' || rpt == 'S');

    // 2. Eliminación con control de vaciado
    cout << "\n--- Desencolando elementos ---\n";
    while (frente != NULL) {
        eliminarCola(frente, fin, dato);
        if (frente != NULL) cout << dato << " -> ";
        else cout << dato << ". (Cola vacia)";
    }

    getch();
    return 0;
}

void insertarCola(Nodo *&frente, Nodo *&fin, int n) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = n;
    nuevo_nodo->siguiente = NULL;

    if (colaVacia(frente)) {
        frente = nuevo_nodo;
    } else {
        fin->siguiente = nuevo_nodo;
    }
    fin = nuevo_nodo;
    cout << "Elemento [" << n << "] insertado.\n";
}

bool colaVacia(Nodo *frente) {
    return (frente == NULL);
}

void eliminarCola(Nodo *&frente, Nodo *&fin, int &n) {
    // Control de errores: Verificar si está vacía antes de borrar
    if (frente == NULL) return; 

    n = frente->dato;
    Nodo *aux = frente;

    if (frente == fin) {
        frente = NULL;
        fin = NULL;
    } else {
        frente = frente->siguiente;
    }
    delete aux;
}
