#include <iostream> // Permite usar cout (mostrar en pantalla) y cin (leer desde teclado).
#include <fstream> // Permite usar ifstream (lectura) y ofstream (escritura).
#include <string> // Facilita el manejo de cadenas de texto.
#include <sstream> // Permite dividir y procesar cadenas como si fueran flujos de datos.

using namespace std; // Evita escribir std:: antes de cout, cin, string, etc.

//ESTRUCTURA ESTUDIANTE
// Define un nodo de la lista enlazada. // Cada nodo almacena los datos de un estudiante y un puntero al siguiente nodo
struct Estudiante {
    int id;  // Identificador único del estudiante.
    string nombre;          
    string correo;          
    string escuela;   // Escuela profesional.
    int anioIngreso;        
    
    Estudiante* siguiente; // Puntero al siguiente nodo de la lista. // Si es el último nodo, este puntero será nullptr.
};

// POO - Utilizamos el Paradigma de Programación Orientada a Objetos 
// CLASE ListaEstudiantes  // Administra la lista enlazada de estudiantes y todas las operaciones.
class ListaEstudiantes {
private:
    Estudiante* cabeza; // Puntero al primer nodo de la lista. // Si la lista está vacía, vale nullptr.
    int siguienteId; // Variable que guarda el próximo ID a asignar automáticamente.

public:
    // CONSTRUCTOR
    ListaEstudiantes() { // Inicializa una lista vacía.
        cabeza = nullptr;   // No hay nodos al inicio.
        siguienteId = 1;    // El primer estudiante tendrá ID 1.
    }

    // DESTRUCTOR
    ~ListaEstudiantes() {
        Estudiante* actual = cabeza;  // Comenzamos desde la cabeza.
        while (actual != nullptr) { // Recorremos toda la lista.
            Estudiante* aBorrar = actual;  // Guardamos el nodo actual para eliminarlo.
            actual = actual->siguiente;  // Avanzamos al siguiente nodo.
            delete aBorrar;  // Liberamos la memoria del nodo.
        }
    }

    // AGREGAR ESTUDIANTE
    void agregarEstudiante(string nombre, string correo,
                           string escuela, int anioIngreso) {

        Estudiante* nuevo = new Estudiante;  // Reservamos memoria para un nuevo nodo.
        nuevo->id = siguienteId++;  // Asignamos un ID único y luego incrementamos el contador.

        // Copiamos los datos recibidos.
        nuevo->nombre = nombre;
        nuevo->correo = correo;
        nuevo->escuela = escuela;
        nuevo->anioIngreso = anioIngreso;

        // Como será el último nodo, apunta a nullptr.
        nuevo->siguiente = nullptr;

        // Si la lista está vacía.
        if (cabeza == nullptr) {
            // El nuevo nodo se convierte en la cabeza.
            cabeza = nuevo;
        }
        else {
            // Recorremos hasta el último nodo.
            Estudiante* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }

            // Enlazamos el último nodo con el nuevo.
            actual->siguiente = nuevo;
        }

        // Confirmación al usuario.
        cout << "Estudiante agregado con exito. ID asignado: "
             << nuevo->id << endl;
    }

    // MOSTRAR TODOS LOS ESTUDIANTES
    void mostrarEstudiantes() {

        // Si la lista está vacía.
        if (cabeza == nullptr) {
            cout << "No hay estudiantes registrados." << endl;
            return;
        }

        // Empezamos desde el primer nodo.
        Estudiante* actual = cabeza;

        cout << "--- Lista de Estudiantes ---" << endl;

        // Recorremos toda la lista.
        while (actual != nullptr) {
            cout << "ID: " << actual->id << endl;
            cout << "Nombre: " << actual->nombre << endl;
            cout << "Correo: " << actual->correo << endl;
            cout << "Escuela: " << actual->escuela << endl;
            cout << "Anio de Ingreso: "
                 << actual->anioIngreso << endl;
            cout << "---------------------------" << endl;

            // Avanzamos al siguiente nodo.
            actual = actual->siguiente;
        }
    }

    // BUSCAR ESTUDIANTE POR ID
    void buscarEstudiante(int id) {

        // Iniciamos desde la cabeza.
        Estudiante* actual = cabeza;

        // Recorremos la lista.
        while (actual != nullptr) {

            // Si encontramos el ID.
            if (actual->id == id) {
                cout << "--- Estudiante Encontrado ---" << endl;
                cout << "ID: " << actual->id << endl;
                cout << "Nombre: " << actual->nombre << endl;
                cout << "Correo: " << actual->correo << endl;
                cout << "Escuela: " << actual->escuela << endl;
                cout << "Anio de Ingreso: "
                     << actual->anioIngreso << endl;

                // Terminamos la función.
                return;
            }

            // Avanzamos al siguiente nodo.
            actual = actual->siguiente;
        }

        // Si no se encontró ningún nodo con ese ID.
        cout << "Estudiante con ID " << id
             << " no encontrado." << endl;
    }

    // BUSCAR ESTUDIANTE POR NOMBRE
    void buscarEstudiante(string nombre) {

        // Comenzamos desde la cabeza.
        Estudiante* actual = cabeza;

        // Bandera para saber si hubo coincidencias.
        bool encontrado = false;

        // Recorremos toda la lista.
        while (actual != nullptr) {

            // find() busca una subcadena.
            // Si no la encuentra devuelve string::npos.
            if (actual->nombre.find(nombre) != string::npos) {

                cout << "--- Estudiante Encontrado ---" << endl;
                cout << "ID: " << actual->id << endl;
                cout << "Nombre: " << actual->nombre << endl;
                cout << "Correo: " << actual->correo << endl;
                cout << "Escuela: " << actual->escuela << endl;
                cout << "Anio de Ingreso: "
                     << actual->anioIngreso << endl;

                // Marcamos que sí se encontró al menos uno.
                encontrado = true;
            }

            // Avanzamos al siguiente nodo.
            actual = actual->siguiente;
        }

        // Si no hubo coincidencias.
        if (!encontrado) {
            cout << "Ningun estudiante encontrado con el nombre: "
                 << nombre << endl;
        }
    }

    // MODIFICAR ESTUDIANTE
    void modificarEstudiante(int id) {

        // Empezamos desde la cabeza.
        Estudiante* actual = cabeza;

        // Buscamos el ID.
        while (actual != nullptr) {

            if (actual->id == id) {
                cout << "--- Modificando Estudiante ID "
                     << id << " ---" << endl;

                cout << "Dejar en blanco (o presionar Enter) "
                     << "para no modificar el campo." << endl;

                // Variable temporal para leer cada campo.
                string entrada;

                // Limpiamos el buffer para que getline funcione correctamente.
                cin.ignore(10000, '\n');

                // ----------------- Nombre -----------------
                cout << "Nombre actual ("
                     << actual->nombre << "): ";
                getline(cin, entrada);

                // Si el usuario escribió algo, actualizamos.
                if (!entrada.empty())
                    actual->nombre = entrada;

                // ----------------- Correo -----------------
                cout << "Correo actual ("
                     << actual->correo << "): ";
                getline(cin, entrada);

                if (!entrada.empty())
                    actual->correo = entrada;

                // ----------------- Escuela -----------------
                cout << "Escuela actual ("
                     << actual->escuela << "): ";
                getline(cin, entrada);

                if (!entrada.empty())
                    actual->escuela = entrada;

                // ----------------- Año de ingreso -----------------
                cout << "Anio de Ingreso actual ("
                     << actual->anioIngreso << "): ";
                getline(cin, entrada);

                // Si se ingresó un valor.
                if (!entrada.empty()) {
                    try {
                        // Convertimos la cadena a entero.
                        actual->anioIngreso = stoi(entrada);
                    }
                    catch (...) {
                        // Si la conversión falla.
                        cout << "Entrada invalida. "
                             << "El anio no se modifico." << endl;
                    }
                }

                cout << "Datos actualizados exitosamente." << endl;
                return;
            }

            // Avanzamos al siguiente nodo.
            actual = actual->siguiente;
        }

        // Si no se encontró el ID.
        cout << "Estudiante con ID " << id
             << " no encontrado." << endl;
    }

    // ELIMINAR ESTUDIANTE
    void eliminarEstudiante(int id) {

        // Si la lista está vacía.
        if (cabeza == nullptr) {
            cout << "La lista esta vacia." << endl;
            return;
        }

        // Caso especial: el nodo a eliminar es la cabeza.
        if (cabeza->id == id) {
            Estudiante* aBorrar = cabeza;

            // La cabeza pasa a ser el segundo nodo.
            cabeza = cabeza->siguiente;

            // Liberamos memoria.
            delete aBorrar;

            cout << "Estudiante eliminado exitosamente." << endl;
            return;
        }

        // Recorremos hasta encontrar el nodo anterior al que se eliminará.
        Estudiante* actual = cabeza;

        while (actual->siguiente != nullptr &&
               actual->siguiente->id != id) {
            actual = actual->siguiente;
        }

        // Si encontramos el nodo.
        if (actual->siguiente != nullptr) {

            // Nodo a eliminar.
            Estudiante* aBorrar = actual->siguiente;

            // Saltamos el nodo eliminado.
            actual->siguiente = aBorrar->siguiente;

            // Liberamos memoria.
            delete aBorrar;

            cout << "Estudiante eliminado exitosamente." << endl;
        }
        else {
            // No se encontró el ID.
            cout << "Estudiante con ID " << id
                 << " no encontrado." << endl;
        }
    }

    // GUARDAR EN ARCHIVO
    void guardarEnArchivo(string filename) {
        ofstream archivo(filename); // Abrimos el archivo en modo escritura por eso el ofstream. // Si existe, su contenido se reemplaza.

        // Verificamos si se abrió correctamente.
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo para guardar." << endl;
            return;
        }

        // Recorremos toda la lista.
        Estudiante* actual = cabeza;

        while (actual != nullptr) {

            // Guardamos los datos separados por '|'.
            // Ejemplo:
            // Forma en que se va a guardar >>>   1|Juan Perez|juan@correo.com|Ingenieria|2023
            archivo << actual->id << "|"
                    << actual->nombre << "|"
                    << actual->correo << "|"
                    << actual->escuela << "|"
                    << actual->anioIngreso << "\n";

            // Avanzamos al siguiente nodo.
            actual = actual->siguiente;
        }

        // Cerramos el archivo.
        archivo.close();

        cout << "Datos guardados en "
             << filename
             << " exitosamente." << endl;
    }

    // CARGAR DESDE ARCHIVO
    void cargarDesdeArchivo(string filename) {

        // Abrimos el archivo para lectura.
        ifstream archivo(filename);

        // Si no existe, simplemente salimos.
        if (!archivo.is_open()) {
            return;
        }

        // Variable para almacenar cada línea del archivo.
        string linea;

        // Guardará el ID máximo encontrado.
        int maxId = 0;

        // Limpiar la lista actual antes de cargar.
        while (cabeza != nullptr) {
            Estudiante* aBorrar = cabeza;
            cabeza = cabeza->siguiente;
            delete aBorrar;
        }

        // Puntero al último nodo para insertar eficientemente.
        Estudiante* ultimo = nullptr;

        // Leemos el archivo línea por línea.
        while (getline(archivo, linea)) {

            // Ignoramos líneas vacías.
            if (linea.empty())
                continue;

            // Convertimos la línea en un flujo.
            stringstream ss(linea);

            // Variable auxiliar para campos numéricos.
            string item;

            // Creamos un nuevo nodo.
            Estudiante* nuevo = new Estudiante;
            nuevo->siguiente = nullptr;

            // Extraemos cada campo separado por '|'.
            getline(ss, item, '|');
            nuevo->id = stoi(item);

            getline(ss, nuevo->nombre, '|');
            getline(ss, nuevo->correo, '|');
            getline(ss, nuevo->escuela, '|');

            getline(ss, item, '|');
            nuevo->anioIngreso = stoi(item);

            // Actualizamos el ID máximo.
            if (nuevo->id > maxId) {
                maxId = nuevo->id;
            }

            // Insertamos el nodo al final.
            if (cabeza == nullptr) {
                cabeza = nuevo;
                ultimo = nuevo;
            }
            else {
                ultimo->siguiente = nuevo;
                ultimo = nuevo;
            }
        }

        // Cerramos el archivo.
        archivo.close();

        // El próximo ID será uno mayor que el máximo encontrado.
        siguienteId = maxId + 1;

        cout << "Datos cargados desde "
             << filename
             << " exitosamente." << endl;
    }
};

// MOSTRAR MENÚ PRINCIPAL
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

// FUNCIÓN PRINCIPAL
int main() {

    // Creamos el objeto que administrará la lista.
    ListaEstudiantes lista;

    // Variable para almacenar la opción del menú.
    int opcion;

    // Nombre del archivo donde se guardarán los datos.
    string filename = "registros.txt";

    // Cargamos automáticamente los datos al iniciar el programa.
    lista.cargarDesdeArchivo(filename);

    // Bucle principal del programa.
    do {
        // Mostramos el menú.
        mostrarMenu();

        // Validamos que el usuario ingrese un número.
        if (!(cin >> opcion)) {

            // Limpiamos el estado de error.
            cin.clear();

            // Eliminamos el contenido inválido del buffer.
            cin.ignore(10000, '\n');

            cout << "Entrada invalida. Ingrese un numero." << endl;

            // Reinicia el ciclo.
            continue;
        }

        // Evaluamos la opción elegida.
        switch (opcion) {

            // -----------------------------------------------------------------
            // OPCIÓN 1: AGREGAR ESTUDIANTE
            // -----------------------------------------------------------------
            case 1: {
                string nombre, correo, escuela;
                int anio;

                // Limpiamos buffer antes de getline.
                cin.ignore(10000, '\n');

                cout << "Ingrese nombre completo: ";
                getline(cin, nombre);

                cout << "Ingrese correo electronico: ";
                getline(cin, correo);

                cout << "Ingrese escuela profesional: ";
                getline(cin, escuela);

                cout << "Ingrese anio de ingreso: ";
                cin >> anio;

                // Insertamos el estudiante en la lista.
                lista.agregarEstudiante(nombre, correo,
                                        escuela, anio);
                break;
            }

            // -----------------------------------------------------------------
            // OPCIÓN 2: MOSTRAR ESTUDIANTES
            // -----------------------------------------------------------------
            case 2:
                lista.mostrarEstudiantes();
                break;

            // -----------------------------------------------------------------
            // OPCIÓN 3: BUSCAR
            // -----------------------------------------------------------------
            case 3: {
                int subopcion;

                cout << "1. Buscar por ID\n"
                     << "2. Buscar por Nombre\n"
                     << "Seleccione: ";

                if (!(cin >> subopcion)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Entrada invalida." << endl;
                    break;
                }

                // Buscar por ID.
                if (subopcion == 1) {
                    int id;
                    cout << "Ingrese ID a buscar: ";
                    cin >> id;
                    lista.buscarEstudiante(id);
                }
                // Buscar por nombre.
                else if (subopcion == 2) {
                    string nombre;
                    cin.ignore(10000, '\n');
                    cout << "Ingrese nombre a buscar: ";
                    getline(cin, nombre);
                    lista.buscarEstudiante(nombre);
                }
                else {
                    cout << "Opcion invalida." << endl;
                }

                break;
            }

            // -----------------------------------------------------------------
            // OPCIÓN 4: MODIFICAR
            // -----------------------------------------------------------------
            case 4: {
                int id;
                cout << "Ingrese el ID del estudiante a modificar: ";
                cin >> id;
                lista.modificarEstudiante(id);
                break;
            }

            // -----------------------------------------------------------------
            // OPCIÓN 5: ELIMINAR
            // -----------------------------------------------------------------
            case 5: {
                int id;
                cout << "Ingrese el ID del estudiante a eliminar: ";
                cin >> id;
                lista.eliminarEstudiante(id);
                break;
            }

            // -----------------------------------------------------------------
            // OPCIÓN 6: GUARDAR
            // -----------------------------------------------------------------
            case 6:
                lista.guardarEnArchivo(filename);
                break;

            // -----------------------------------------------------------------
            // OPCIÓN 7: CARGAR
            // -----------------------------------------------------------------
            case 7:
                lista.cargarDesdeArchivo(filename);
                break;

            // -----------------------------------------------------------------
            // OPCIÓN 8: SALIR
            // -----------------------------------------------------------------
            case 8:
                cout << "Guardando datos antes de salir..." << endl;
                lista.guardarEnArchivo(filename);
                cout << "Saliendo del programa..." << endl;
                break;

            // -----------------------------------------------------------------
            // OPCIÓN INVÁLIDA
            // -----------------------------------------------------------------
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
        }

    // El ciclo continúa mientras la opción sea distinta de 8.
    } while (opcion != 8);

    // Fin exitoso del programa.
    return 0;
}

