#include <bits/stdc++.h> // incluye prácticamente toda la STL (útil en ejercicios; no recomendado en producción)
using namespace std;      // evita tener que escribir std:: cada vez

// ----------------------
// Algoritmos de búsqueda
// ----------------------

// Búsqueda lineal: recorre el vector hasta encontrar el valor
int busquedaLineal(const vector<int>& a, int x) { // recibe el vector por referencia const y el valor a buscar
    for (size_t i = 0; i < a.size(); ++i)        // iterador i desde 0 hasta a.size()-1
        if (a[i] == x) return (int)i;           // si el elemento en i es x devuelve el índice (cast a int)
    return -1;                                  // si no se encuentra devuelve -1
}

// Búsqueda binaria: requiere que el vector esté ORDENADO
int busquedaBinaria(const vector<int>& a, int x) {
    int l = 0, r = (int)a.size() - 1;           // l = límite izquierdo, r = límite derecho
    while (l <= r) {                            // mientras haya segmento válido
        int m = l + (r - l) / 2;                // m = punto medio (forma segura para evitar overflow)
        if (a[m] == x) return m;                // si el medio es x, devolvemos m
        else if (a[m] < x) l = m + 1;           // si el medio es menor, buscamos en la mitad derecha
        else r = m - 1;                         // si es mayor, buscamos en la mitad izquierda
    }
    return -1;                                  // no encontrado
}

// Búsqueda exponencial: expande el rango y luego aplica binaria
int busquedaExponencial(const vector<int>& a, int x) {
    if (a.empty()) return -1;                   // manejo del caso de vector vacío
    if (a[0] == x) return 0;                    // chequear el primer elemento (optimización rápida)

    int i = 1;                                  // i será la posición que duplicaremos: 1,2,4,8,...
    while (i < (int)a.size() && a[i] < x) i <<= 1; // duplicar i mientras a[i] < x y no salgamos del vector

    int l = i / 2, r = min(i, (int)a.size() - 1); // rango candidato donde puede estar x: [i/2, min(i,n-1)]

    // ahora hacemos búsqueda binaria dentro de [l, r]
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (a[m] == x) return m;
        else if (a[m] < x) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

// Búsqueda por interpolación: estima la posición del valor
int busquedaInterpolacion(const vector<int>& a, int x) {
    int low = 0, high = (int)a.size() - 1;      // límites iniciales

    // el bucle solo tiene sentido si x está entre a[low] y a[high]
    while (low <= high && x >= a[low] && x <= a[high]) {
        if (a[low] == a[high])                  // si todos los valores en el intervalo son iguales
            return (a[low] == x ? low : -1);    // si son iguales y coinciden devolvemos low, si no -1

        // fórmula de interpolación: aproxima la posición usando proporción
        long long pos = low + (long long)((double)(high - low) *
                                          ((double)(x - a[low]) /
                                           (double)(a[high] - a[low])));

        if (pos < low || pos > high) break;    // si la estimación sale del rango, salimos (fallo de estimación)

        if (a[pos] == x) return (int)pos;      // si la estimación acierta, devolvemos índice
        if (a[pos] < x) low = (int)pos + 1;    // si el valor en pos es menor, mover low
        else high = (int)pos - 1;              // si es mayor, mover high
    }
    return -1;                                  // no encontrado o estimación inválida
}

// ----------------------
// (medir tiempo promedio de búsquedas)
// ----------------------

// plantilla que recibe cualquier "buscador" que tenga firma int(const vector<int>&, int)
template <class F>
double medir(const vector<int>& a, const vector<int>& queries, F buscador) {
    using clk = chrono::high_resolution_clock;  // alias para tipo de reloj
    auto t0 = clk::now();                       // instante inicial

    volatile long long checksum = 0;            // variable volátil para evitar que el compilador optimice las llamadas
    for (int x : queries) checksum += buscador(a, x); // ejecutar buscador para cada query y acumular resultado

    auto t1 = clk::now();                       // instante final
    chrono::duration<double, milli> ms = t1 - t0; // duración en milisegundos

    // devolver el tiempo promedio por búsqueda (ms)
    return ms.count() / (double)queries.size();
}

// ----------------------
// Programa principal
// ----------------------
int main() {
    ios::sync_with_stdio(false);                // optimiza IO vinculando cin/cout a C I/O (desvincula)
    cin.tie(nullptr);                           // evita flushing automático de cout al leer con cin

    // Tamaños de prueba (n)
    vector<int> ns = {104, 105, 5105};   // tres escalas para ver comportamiento asintótico
    mt19937 rng(123);                           // motor Mersenne Twister con semilla fija para reproducibilidad

    for (int n : ns) {                          // iterar para cada tamaño n
        // a) Dataset uniforme ordenado (0..n-1)
        vector<int> uni(n);                     // reservar vector de tamaño n
        iota(uni.begin(), uni.end(), 0);        // llenar con 0,1,2,...,n-1

        // b) Dataset sesgado ordenado
        // objetivo: 80% valores concentrados en rango pequeño, 20% dispersos
        vector<int> ses(n);
        for (int i = 0; i < n; i++) {
            double u = uniform_real_distribution<double>(0, 1)(rng); // número en [0,1)
            if (u < 0.8)
                ses[i] = uniform_int_distribution<int>(0, (int)(0.1 * n))(rng); // 80% en [0,0.1n)

            else
                ses[i] = uniform_int_distribution<int>((int)(0.1 * n), 5 * n)(rng); // 20% en [0.1n,5n)
        }
        sort(ses.begin(), ses.end());           // ordenamos para que sea dataset ordenado (requisito de ciertos algoritmos)

        // c) Dataset desordenado (shuffle del uniforme)
        vector<int> des = uni;                   // copia del uniforme
        shuffle(des.begin(), des.end(), rng);    // barajar aleatoriamente para desordenarlo

        // Generar queries (1000 en total: 70% hits, 30% misses)
        auto mkqueries = [&](const vector<int>& base) { // lambda que toma un dataset base y devuelve vector de queries
            vector<int> q; q.reserve(1000);     // reservar espacio para 1000 queries
            uniform_int_distribution<int> idx(0, (int)base.size() - 1); // distribución para seleccionar índices válidos

            // 70% hits: seleccionamos valores que sí están en el dataset
            for (int i = 0; i < 700; i++) q.push_back(base[idx(rng)]);
            // 30% misses: generamos valores fuera del rango (garantizamos ausencia)
            for (int i = 0; i < 300; i++) q.push_back(10 * (int)base.size() + i);

            shuffle(q.begin(), q.end(), rng);   // mezclar para no agrupar hits/misses
            return q;                           // devolver las queries
        };

        auto q_uni = mkqueries(uni);            // queries para dataset uniforme
        auto q_ses = mkqueries(ses);            // queries para dataset sesgado
        auto q_des = mkqueries(des);            // queries para dataset desordenado

        // Función para mostrar resultados en consola para un dataset
        auto report = [&](const string& nombre, const vector<int>& arr, const vector<int>& q) {
            cout << "n=" << n << ", dataset=" << nombre << "\n"; // encabezado

            // medir y mostrar tiempo de búsqueda lineal (siempre aplicable)
            cout << "  lineal        : " << medir(arr, q, busquedaLineal) << " ms/busq\n";

// comprobar si el arreglo está ordenado: si lo está, medimos los algoritmos que requieren orden
            if (is_sorted(arr.begin(), arr.end())) {
                cout << "  binaria       : " << medir(arr, q, busquedaBinaria) << " ms/busq\n";
                cout << "  exponencial   : " << medir(arr, q, busquedaExponencial) << " ms/busq\n";
                cout << "  interpolacion : " << medir(arr, q, busquedaInterpolacion) << " ms/busq\n";
            } else {
                // si no está ordenado, informamos que sólo es razonable usar lineal (sin ordenar primero)
                cout << "  (datos no ordenados: usar solo búsqueda lineal)\n";
            }
        };

        // Reportar resultados para los tres datasets generados
        report("uniforme_ordenado", uni, q_uni);
        report("sesgado_ordenado", ses, q_ses);
        report("desordenado", des, q_des);

        cout << "*******************************\n"; // separador visual entre bloques de n
    }

    return 0; // fin del programa
}
