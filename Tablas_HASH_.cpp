// ================================================================
// PRÁCTICA: TABLAS HASH EN C++ (SOLO COLISIONES)
// Curso: Estructuras de Datos | Semanas 5-6
// Compilar: g++ -O2 -std=c++17 -o hash_tabla hash_tabla.cpp
// ================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <algorithm>
#include <unordered_map>

using namespace std;

// ───────────────────────────────────────────────────────────────
// ESTRUCTURA: Registro de datos del CSV
// ───────────────────────────────────────────────────────────────
struct Registro {
    string clave;
    string valor;
};

// Estructura simplificada sin tiempos
struct Metricas {
    size_t m;
    size_t n;
    double lambda;
    long long col_enc;
    long long col_sl;
};

// ───────────────────────────────────────────────────────────────
// FUNCIÓN HASH PERSONALIZADA (Polinomial)
// ───────────────────────────────────────────────────────────────
size_t funcionHash(const string& clave, size_t tamanio) {
    size_t hash = 0;
    for (char c : clave)
        hash = (hash * 31 + (size_t)c) % tamanio;
    return hash;
}

// ───────────────────────────────────────────────────────────────
// CLASE: Tabla Hash con Encadenamiento Separado
// ───────────────────────────────────────────────────────────────
class TablaHashEncadenamiento {
public:
    size_t tamanio;
    vector<list<Registro>> tabla;
    long long colisiones = 0;
    long long elementos  = 0;

    TablaHashEncadenamiento(size_t m) : tamanio(m), tabla(m) {}

    void insertar(const Registro& reg) {
        size_t idx = funcionHash(reg.clave, tamanio);
        if (!tabla[idx].empty())
            colisiones++;
        tabla[idx].push_back(reg);
        elementos++;
    }

    double factorDeCarga() const {
        return (double)elementos / tamanio;
    }
};

// ───────────────────────────────────────────────────────────────
// CLASE: Tabla Hash con Sondeo Lineal
// ───────────────────────────────────────────────────────────────
class TablaHashSondeoLineal {
    enum Estado { VACIO, OCUPADO, ELIMINADO };
public:
    size_t tamanio;
    vector<Registro> tabla;
    vector<Estado>   estados;
    long long colisiones = 0;
    long long elementos  = 0;

    TablaHashSondeoLineal(size_t m)
        : tamanio(m), tabla(m), estados(m, VACIO) {}

    bool insertar(const Registro& reg) {
        if ((double)elementos / tamanio >= 0.75)
            return false;

        size_t idx = funcionHash(reg.clave, tamanio);
        size_t pasos = 0;

        while (estados[idx] == OCUPADO) {
            colisiones++;
            idx = (idx + 1) % tamanio;
            if (++pasos >= tamanio) return false;
        }

        tabla[idx] = reg;
        estados[idx] = OCUPADO;
        elementos++;
        return true;
    }
};

// ───────────────────────────────────────────────────────────────
// LECTURA DE CSV INTELIGENTE
// ───────────────────────────────────────────────────────────────
vector<Registro> leerCSV(const string& ruta, const string& nombre_clave, const string& nombre_valor) {
    vector<Registro> registros;
    ifstream archivo(ruta);

    if (!archivo.is_open()) return registros;

    string linea;
    if (!getline(archivo, linea)) return registros;

    stringstream ss_head(linea);
    string col_name;
    int idx_clave = -1, idx_valor = -1, i = 0;

    while (getline(ss_head, col_name, ',')) {
        if (!col_name.empty() && col_name.back() == '\r') col_name.pop_back();
        if (col_name == nombre_clave) idx_clave = i;
        if (col_name == nombre_valor) idx_valor = i;
        i++;
    }

    if (idx_clave == -1 || idx_valor == -1) return registros;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        vector<string> campos;

        while (getline(ss, campo, ',')) {
            if (!campo.empty() && campo.back() == '\r') campo.pop_back();
            campos.push_back(campo);
        }

        if ((int)campos.size() > max(idx_clave, idx_valor)) {
            Registro r;
            r.clave = campos[idx_clave];
            r.valor = campos[idx_valor];
            if (!r.clave.empty()) registros.push_back(r);
        }
    }
    archivo.close();
    return registros;
}

// ───────────────────────────────────────────────────────────────
// FUNCIÓN PARA MOSTRAR LA TABLA (Simplificada)
// ───────────────────────────────────────────────────────────────
void mostrarTabla(const vector<Metricas>& resultados) {
    cout << "\n" << string(60, '=') << endl;
    cout << right
         << setw(6)  << "m"
         << setw(8)  << "n"
         << setw(10) << "lambda"
         << setw(15) << "Col_Enc"
         << setw(15) << "Col_SL" << endl;
    cout << string(60, '=') << endl;

    for (const auto& r : resultados) {
        cout << right
             << setw(6)  << r.m
             << setw(8)  << r.n
             << fixed << setprecision(3) << setw(10) << r.lambda
             << setw(15) << r.col_enc
             << setw(15) << r.col_sl << endl;
    }
}

// ───────────────────────────────────────────────────────────────
// BENCHMARK COMPLETO (Sin medición de tiempo)
// ───────────────────────────────────────────────────────────────
vector<Metricas> benchmark(const vector<Registro>& datos, vector<size_t> tamanios) {
    vector<Metricas> resultados;

    for (size_t m : tamanios) {
        size_t n = min(datos.size(), (size_t)(m * 0.65));
        vector<Registro> subdatos(datos.begin(), datos.begin() + n);

        Metricas met;
        met.m = m;
        met.n = n;

        // --- Encadenamiento ---
        TablaHashEncadenamiento th_enc(m);
        for (const auto& reg : subdatos) th_enc.insertar(reg);
        met.col_enc = th_enc.colisiones;
        met.lambda = th_enc.factorDeCarga();

        // --- Sondeo Lineal ---
        TablaHashSondeoLineal th_sl(m);
        for (const auto& reg : subdatos) th_sl.insertar(reg);
        met.col_sl = th_sl.colisiones;

        // Imprimir progreso en consola
        cout << "m=" << m << ": lambda=" << fixed << setprecision(3) << met.lambda
             << " | col_enc=" << met.col_enc
             << " | col_sl=" << met.col_sl << endl;

        resultados.push_back(met);
    }
    return resultados;
}

// ───────────────────────────────────────────────────────────────
// FUNCIÓN PRINCIPAL
// ───────────────────────────────────────────────────────────────
int main() {
    string archivo = "AI_Impact_Student_Life_2026.csv";

    // Cargar dataset
    vector<Registro> datos_brutos = leerCSV(archivo, "Student_ID", "Main_Usage_Case");
    if (datos_brutos.empty()) {
        cout << "Error: Verifica el archivo " << archivo << endl;
        return 1;
    }

    // Filtrar IDs únicos
    unordered_map<string, string> unicos;
    for (const auto& r : datos_brutos) unicos[r.clave] = r.valor;

    vector<Registro> datos;
    for (const auto& par : unicos) datos.push_back({par.first, par.second});

    cout << "Procesando " << datos.size() << " registros unicos...\n";

    vector<size_t> tamanios = {1009, 2003, 4001, 8009};
    vector<Metricas> res = benchmark(datos, tamanios);
    mostrarTabla(res);

    return 0;
}
