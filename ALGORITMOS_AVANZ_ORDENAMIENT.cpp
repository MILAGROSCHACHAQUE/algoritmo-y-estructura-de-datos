#include <iostream>   // Entrada y salida estándar (cout, cin)
#include <vector>     // Estructura de datos vector
#include <chrono>     // Medición de tiempo de ejecución
#include <algorithm>  // Funciones como sort, max_element, min_element
#include <random>     // Generación de números aleatorios
#include <iomanip>    // Formato de salida (setw, alineación)

using namespace std;  // Evita escribir std:: constantemente
using Clock = chrono::high_resolution_clock; // Alias para reloj de alta precisión

// 1. QUICK SORT
// Función de partición: reorganiza el arreglo respecto a un pivote
int partition(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2; // Calcula el índice medio
    swap(arr[mid], arr[high]);        // Mueve el pivote al final
    int pivot = arr[high];            // Selecciona el pivote

    int i = (low - 1); // Índice del menor elemento
    for (int j = low; j <= high - 1; j++) { // Recorre el arreglo
        if (arr[j] < pivot) { // Si elemento actual es menor que pivote
            i++;              // Incrementa índice
            swap(arr[i], arr[j]); // Intercambia elementos
        }
    }
    swap(arr[i + 1], arr[high]); // Coloca pivote en su posición correcta
    return (i + 1); // Retorna índice del pivote
}

// Función recursiva de QuickSort
void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low < high) { // Caso base
        int pi = partition(arr, low, high); // Obtiene pivote
        quickSortHelper(arr, low, pi - 1);  // Ordena izquierda
        quickSortHelper(arr, pi + 1, high); // Ordena derecha
    }
}

// Función principal QuickSort
void quickSort(vector<int>& arr) {
    if(!arr.empty()) // Verifica que no esté vacío
        quickSortHelper(arr, 0, arr.size() - 1);
}


// 2. MERGE SORT
// Función para fusionar dos subarreglos ordenados
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1; // Tamaño subarreglo izquierdo
    int n2 = r - m;     // Tamaño subarreglo derecho
    vector<int> L(n1), R(n2); // Vectores temporales

    // Copia datos al subarreglo izquierdo
    for(int i = 0; i < n1; i++) L[i] = arr[l + i];
    // Copia datos al subarreglo derecho
    for(int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l; // Índices

    // Mezcla los subarreglos
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) arr[k++] = L[i++]; // Inserta menor
        else arr[k++] = R[j++];
    }

    // Copia elementos restantes
    while(i < n1) arr[k++] = L[i++];
    while(j < n2) arr[k++] = R[j++];
}

// Función recursiva MergeSort
void mergeSortHelper(vector<int>& arr, int l, int r) {
    if(l >= r) return; // Caso base
    int m = l + (r - l) / 2; // Punto medio
    mergeSortHelper(arr, l, m);     // Ordena izquierda
    mergeSortHelper(arr, m + 1, r); // Ordena derecha
    merge(arr, l, m, r);            // Fusiona
}

// Función principal MergeSort
void mergeSort(vector<int>& arr) {
    if(!arr.empty())
        mergeSortHelper(arr, 0, arr.size() - 1);
}


// 3. TIM SORT (Híbrido)

const int RUN = 32; // Tamaño de subarreglo inicial

// Insertion Sort usado por TimSort
void insertionSortTim(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i]; // Elemento actual
        int j = i - 1;

        // Desplaza elementos mayores
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp; // Inserta en posición correcta
    }
}

// Implementación de TimSort
void timSort(vector<int>& arr) {
    int n = arr.size();

    // Ordena pequeños bloques con InsertionSort
    for (int i = 0; i < n; i += RUN)
        insertionSortTim(arr, i, min(i + RUN - 1, n - 1));

    // Fusiona bloques progresivamente
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));

            if(mid < right)
                merge(arr, left, mid, right);
        }
    }
}


// 4. COUNTING SORT

void countingSort(vector<int>& arr) {
    if(arr.empty()) return;

    int max_val = *max_element(arr.begin(), arr.end()); // Máximo
    int min_val = *min_element(arr.begin(), arr.end()); // Mínimo
    int range = max_val - min_val + 1; // Rango

    vector<int> count(range, 0), output(arr.size());

    // Conteo de frecuencias
    for (int i = 0; i < arr.size(); i++) 
        count[arr[i] - min_val]++;

    // Acumulación
    for (int i = 1; i < count.size(); i++) 
        count[i] += count[i - 1];

    // Construcción del arreglo ordenado
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - min_val] - 1] = arr[i];
        count[arr[i] - min_val]--;
    }

    // Copia al original
    for (int i = 0; i < arr.size(); i++) 
        arr[i] = output[i];
}


// 5. RADIX SORT

// Counting Sort auxiliar por dígitos
void countSortForRadix(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    // Conteo por dígito
    for (int i = 0; i < n; i++) 
        count[(arr[i] / exp) % 10]++;

    // Acumulación
    for (int i = 1; i < 10; i++) 
        count[i] += count[i - 1];

    // Construcción
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copia
    for (int i = 0; i < n; i++) 
        arr[i] = output[i];
}

// Radix principal
void radixSort(vector<int>& arr) {
    if(arr.empty()) return;

    int m = *max_element(arr.begin(), arr.end());

    // Procesa cada dígito
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSortForRadix(arr, exp);
}


// 6. BUCKET SORT

void bucketSort(vector<int>& arr) {
    if(arr.empty()) return;

    int max_val = *max_element(arr.begin(), arr.end());
    int min_val = *min_element(arr.begin(), arr.end());

    int bucket_count = arr.size();
    vector<vector<int>> buckets(bucket_count);

    double range = (double)(max_val - min_val + 1) / bucket_count;

    // Distribuye elementos en buckets
    for(int i = 0; i < arr.size(); i++) {
        int b_idx = (arr[i] - min_val) / range;
        if(b_idx >= bucket_count) b_idx = bucket_count - 1;
        buckets[b_idx].push_back(arr[i]);
    }

    int idx = 0;

    // Ordena cada bucket y concatena
    for(int i = 0; i < bucket_count; i++) {
        sort(buckets[i].begin(), buckets[i].end());
        for(int j = 0; j < buckets[i].size(); j++) {
            arr[idx++] = buckets[i][j];
        }
    }
}


// Función para medir tiempo de ejecución
void test(const vector<int>& data, void(*func)(vector<int>&), const string& name) {
    vector<int> arr = data; // Copia datos

    auto t1 = Clock::now(); // Inicio
    func(arr);              // Ejecuta algoritmo
    auto t2 = Clock::now(); // Fin

    // Muestra tiempo
    cout << left << setw(18) << name << " tomó " 
         << right << setw(10) 
         << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() 
         << " μs\n";
}


int main() {
    vector<int> sizes = {10000, 100000, 1000000}; // Tamaños

    random_device rd;
    mt19937 gen(42); // Semilla fija
    uniform_int_distribution<> dis(1, 10000000); // Rango

    for (int n : sizes) {
        vector<int> data(n);

        // Genera datos aleatorios
        for (int i = 0; i < n; i++) 
            data[i] = dis(gen);

        cout << "\n============================================\n";
        cout << "****** Probando con N = " << n << " ******\n";
        cout << "============================================\n";

        // Ejecuta pruebas
        test(data, quickSort,     "Quick Sort");
        test(data, mergeSort,     "Merge Sort");
        test(data, timSort,       "Tim Sort");
        test(data, radixSort,     "Radix Sort");
        test(data, bucketSort,    "Bucket Sort");
        test(data, countingSort,  "Counting Sort");
    }

    return 0; // Fin del programa
}
