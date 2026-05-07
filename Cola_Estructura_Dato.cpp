#include <iostream> // Biblioteca para entrada y salida (cin, cout)
#include <conio.h>  // Biblioteca para usar getch()
using namespace std; // Permite usar cout y cin sin escribir std::

// Definición de la estructura Nodo
struct Nodo{
    int dato; // Variable que almacena el valor del nodo
    Nodo *siguiente; // Puntero que almacena la dirección del siguiente nodo
};

// Declaración de funciones
void insertarCola(Nodo *&, Nodo *&, int); // Inserta elementos en la cola
bool colaVacia(Nodo *); // Verifica si la cola está vacía
void eliminarCola(Nodo *&, Nodo *&, int &); // Elimina elementos de la cola

int main(){
    
    Nodo *frente = NULL; // Puntero que apunta al primer elemento de la cola
    Nodo *fin = NULL;    // Puntero que apunta al último elemento de la cola
    
    int dato; // Variable para guardar los números ingresados
    char rpt; // Variable para repetir el proceso
    
    do{
        cout<<"Digite un numero: "; // Solicita un número al usuario
        cin>>dato; // Lee el número
        
        insertarCola(frente,fin,dato); // Inserta el número en la cola
        
        cout<<"\nDesea ingresar otro elemento (s/n): ";
        cin>>rpt; // Lee la respuesta
        
    }while((rpt=='s') || (rpt=='S')); // Repite mientras la respuesta sea s o S
    
    
    cout<<"\nSacando elementos de la cola:\n";
    
    while(frente != NULL){ // Mientras la cola no esté vacía
        
        eliminarCola(frente,fin,dato); // Elimina el elemento del frente
        
        if(frente != NULL){
            cout<<dato<<" , "; // Muestra el elemento con coma
        }else{
            cout<<dato<<"."; // Último elemento con punto
        }
    }

    getch(); // Pausa el programa
    return 0; // Finaliza correctamente
}


// Función que inserta elementos en la cola
void insertarCola(Nodo *&frente, Nodo *&fin, int n){
    
    Nodo *nuevo_nodo = new Nodo(); // Se crea un nuevo nodo en memoria
    
    nuevo_nodo->dato = n; // Se asigna el valor al nodo
    nuevo_nodo->siguiente = NULL; // El nuevo nodo siempre apunta a NULL porque será el último
    
    if(colaVacia(frente)){ // Si la cola está vacía
        frente = nuevo_nodo; // El frente apunta al nuevo nodo
    }else{
        fin->siguiente = nuevo_nodo; // El último nodo apunta al nuevo nodo
    }
    
    fin = nuevo_nodo; // El nuevo nodo se convierte en el final de la cola
    
    cout<<"\tElemento "<<n<<" insertado correctamente en COLA\n";
}


// Función que verifica si la cola está vacía
bool colaVacia(Nodo *frente){
    return (frente == NULL); // Devuelve true si la cola está vacía
}


// Función que elimina elementos de la cola
void eliminarCola(Nodo *&frente, Nodo *&fin, int &n){
    
    n = frente->dato; // Guarda el valor del nodo que se eliminará
    Nodo *aux = frente; // Puntero auxiliar al nodo que se eliminará
    
    if(frente == fin){ // Si solo hay un nodo
        frente = NULL; // La cola queda vacía
        fin = NULL;
    }else{
        frente = frente->siguiente; // El frente pasa al siguiente nodo
    }
    
    delete aux; // Se libera la memoria del nodo eliminado
}
