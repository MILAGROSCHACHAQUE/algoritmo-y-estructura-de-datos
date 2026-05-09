#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Estructura para el nodo de la lista enlazada
struct Estudiante {
    int id;
    string nombre;
    string correo;
    string escuela;
    int anioIngreso;
    Estudiante* siguiente;
};

// Clase para gestionar la lista de estudiantes
class ListaEstudiantes {
private:
    Estudiante* cabeza;
    int siguienteId;

public:
    ListaEstudiantes() {
        cabeza = nullptr;
        siguienteId = 1;
    }

    ~ListaEstudiantes() {
        Estudiante* actual = cabeza;
        while (actual != nullptr) {
            Estudiante* aBorrar = actual;
            actual = actual->siguiente;
            delete aBorrar;
        }
    }

    void agregarEstudiante(string nombre, string correo, string escuela, int anioIngreso) {
        Estudiante* nuevo = new Estudiante;
        nuevo->id = siguienteId++;
        nuevo->nombre = nombre;
        nuevo->correo = correo;
        nuevo->escuela = escuela;
        nuevo->anioIngreso = anioIngreso;
        nuevo->siguiente = nullptr;

        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Estudiante* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
        cout << "Estudiante agregado con exito. ID asignado: " << nuevo->id << endl;
    }

    void mostrarEstudiantes() {
        if (cabeza == nullptr) {
            cout << "No hay estudiantes registrados." << endl;
            return;
        }
        Estudiante* actual = cabeza;
        cout << "--- Lista de Estudiantes ---" << endl;
        while (actual != nullptr) {
            cout << "ID: " << actual->id << endl;
            cout << "Nombre: " << actual->nombre << endl;
            cout << "Correo: " << actual->correo << endl;
            cout << "Escuela: " << actual->escuela << endl;
            cout << "Anio de Ingreso: " << actual->anioIngreso << endl;
            cout << "---------------------------" << endl;
            actual = actual->siguiente;
        }
    }

    void buscarEstudiante(int id) {
        Estudiante* actual = cabeza;
        while (actual != nullptr) {
            if (actual->id == id) {
                cout << "--- Estudiante Encontrado ---" << endl;
                cout << "ID: " << actual->id << endl;
                cout << "Nombre: " << actual->nombre << endl;
                cout << "Correo: " << actual->correo << endl;
                cout << "Escuela: " << actual->escuela << endl;
                cout << "Anio de Ingreso: " << actual->anioIngreso << endl;
                return;
            }
            actual = actual->siguiente;
        }
        cout << "Estudiante con ID " << id << " no encontrado." << endl;
    }

    void buscarEstudiante(string nombre) {
        Estudiante* actual = cabeza;
        bool encontrado = false;
        while (actual != nullptr) {
            // Busqueda simple por subcadena
            if (actual->nombre.find(nombre) != string::npos) {
                cout << "--- Estudiante Encontrado ---" << endl;
                cout << "ID: " << actual->id << endl;
                cout << "Nombre: " << actual->nombre << endl;
                cout << "Correo: " << actual->correo << endl;
                cout << "Escuela: " << actual->escuela << endl;
                cout << "Anio de Ingreso: " << actual->anioIngreso << endl;
                encontrado = true;
            }
            actual = actual->siguiente;
        }
        if (!encontrado) {
            cout << "Ningun estudiante encontrado con el nombre: " << nombre << endl;
        }
    }

    void modificarEstudiante(int id) {
        Estudiante* actual = cabeza;
        while (actual != nullptr) {
            if (actual->id == id) {
                cout << "--- Modificando Estudiante ID " << id << " ---" << endl;
                cout << "Dejar en blanco (o presionar Enter) para no modificar el campo." << endl;
                
                string entrada;
                cin.ignore(10000, '\n'); // Limpiar el buffer de entrada
                
                cout << "Nombre actual (" << actual->nombre << "): ";
                getline(cin, entrada);
                if (!entrada.empty()) actual->nombre = entrada;

                cout << "Correo actual (" << actual->correo << "): ";
                getline(cin, entrada);
                if (!entrada.empty()) actual->correo = entrada;

                cout << "Escuela actual (" << actual->escuela << "): ";
                getline(cin, entrada);
                if (!entrada.empty()) actual->escuela = entrada;

                cout << "Anio de Ingreso actual (" << actual->anioIngreso << "): ";
                getline(cin, entrada);
                if (!entrada.empty()) {
                    try {
                        actual->anioIngreso = stoi(entrada);
                    } catch (...) {
                        cout << "Entrada invalida. El anio no se modifico." << endl;
                    }
                }

                cout << "Datos actualizados exitosamente." << endl;
                return;
            }
            actual = actual->siguiente;
        }
        cout << "Estudiante con ID " << id << " no encontrado." << endl;
    }

    void eliminarEstudiante(int id) {
        if (cabeza == nullptr) {
            cout << "La lista esta vacia." << endl;
            return;
        }

        if (cabeza->id == id) {
            Estudiante* aBorrar = cabeza;
            cabeza = cabeza->siguiente;
            delete aBorrar;
            cout << "Estudiante eliminado exitosamente." << endl;
            return;
        }

        Estudiante* actual = cabeza;
        while (actual->siguiente != nullptr && actual->siguiente->id != id) {
            actual = actual->siguiente;
        }

        if (actual->siguiente != nullptr) {
            Estudiante* aBorrar = actual->siguiente;
            actual->siguiente = aBorrar->siguiente;
            delete aBorrar;
            cout << "Estudiante eliminado exitosamente." << endl;
        } else {
            cout << "Estudiante con ID " << id << " no encontrado." << endl;
        }
    }

    void guardarEnArchivo(string filename) {
        ofstream archivo(filename);
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo para guardar." << endl;
            return;
        }

        Estudiante* actual = cabeza;
        while (actual != nullptr) {
            // Guardar usando delimitador |
            archivo << actual->id << "|"
                    << actual->nombre << "|"
                    << actual->correo << "|"
                    << actual->escuela << "|"
                    << actual->anioIngreso << "\n";
            actual = actual->siguiente;
        }
        archivo.close();
        cout << "Datos guardados en " << filename << " exitosamente." << endl;
    }

    void cargarDesdeArchivo(string filename) {
        ifstream archivo(filename);
        if (!archivo.is_open()) {
            // Archivo no existe aun, no hay problema
            return;
        }

        string linea;
        int maxId = 0;
        
        // Limpiar la lista actual
        while(cabeza != nullptr) {
            Estudiante* aBorrar = cabeza;
            cabeza = cabeza->siguiente;
            delete aBorrar;
        }
        
        Estudiante* ultimo = nullptr;

        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            stringstream ss(linea);
            string item;
            
            Estudiante* nuevo = new Estudiante;
            nuevo->siguiente = nullptr;

            getline(ss, item, '|'); nuevo->id = stoi(item);
            getline(ss, nuevo->nombre, '|');
            getline(ss, nuevo->correo, '|');
            getline(ss, nuevo->escuela, '|');
            getline(ss, item, '|'); nuevo->anioIngreso = stoi(item);

            if (nuevo->id > maxId) {
                maxId = nuevo->id;
            }

            if (cabeza == nullptr) {
                cabeza = nuevo;
                ultimo = nuevo;
            } else {
                ultimo->siguiente = nuevo;
                ultimo = nuevo;
            }
        }
        archivo.close();
        siguienteId = maxId + 1;
        cout << "Datos cargados desde " << filename << " exitosamente." << endl;
    }
};

void mostrarMenu() {
    cout << "\n=== SISTEMA DE REGISTRO DE ESTUDIANTES ===" << endl;
    cout << "1. Agregar nuevo estudiante" << endl;
    cout << "2. Mostrar todos los estudiantes" << endl;
    cout << "3. Buscar estudiante por ID o nombre" << endl;
    cout << "4. Modificar datos de un estudiante" << endl;
    cout << "5. Eliminar un estudiante" << endl;
    cout << "6. Guardar los datos en archivo .txt" << endl;
    cout << "7. Cargar los datos desde archivo" << endl;
    cout << "8. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    ListaEstudiantes lista;
    int opcion;
    string filename = "registros.txt";

    // Cargar datos al iniciar el programa
    lista.cargarDesdeArchivo(filename);

    do {
        mostrarMenu();
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Ingrese un numero." << endl;
            continue;
        }

        switch (opcion) {
            case 1: {
                string nombre, correo, escuela;
                int anio;
                cin.ignore(10000, '\n'); // Limpiar el buffer
                cout << "Ingrese nombre completo: ";
                getline(cin, nombre);
                cout << "Ingrese correo electronico: ";
                getline(cin, correo);
                cout << "Ingrese escuela profesional: ";
                getline(cin, escuela);
                cout << "Ingrese anio de ingreso: ";
                cin >> anio;
                lista.agregarEstudiante(nombre, correo, escuela, anio);
                break;
            }
            case 2:
                lista.mostrarEstudiantes();
                break;
            case 3: {
                int subopcion;
                cout << "1. Buscar por ID\n2. Buscar por Nombre\nSeleccione: ";
                if (!(cin >> subopcion)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Entrada invalida." << endl;
                    break;
                }
                
                if (subopcion == 1) {
                    int id;
                    cout << "Ingrese ID a buscar: ";
                    cin >> id;
                    lista.buscarEstudiante(id);
                } else if (subopcion == 2) {
                    string nombre;
                    cin.ignore(10000, '\n');
                    cout << "Ingrese nombre a buscar: ";
                    getline(cin, nombre);
                    lista.buscarEstudiante(nombre);
                } else {
                    cout << "Opcion invalida." << endl;
                }
                break;
            }
            case 4: {
                int id;
                cout << "Ingrese el ID del estudiante a modificar: ";
                cin >> id;
                lista.modificarEstudiante(id);
                break;
            }
            case 5: {
                int id;
                cout << "Ingrese el ID del estudiante a eliminar: ";
                cin >> id;
                lista.eliminarEstudiante(id);
                break;
            }
            case 6:
                lista.guardarEnArchivo(filename);
                break;
            case 7:
                lista.cargarDesdeArchivo(filename);
                break;
            case 8:
                cout << "Guardando datos antes de salir..." << endl;
                lista.guardarEnArchivo(filename);
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
        }
    } while (opcion != 8);

    return 0;
}
