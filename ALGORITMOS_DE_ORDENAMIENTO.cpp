#include <iostream>   // Permite usar entrada/salida estándar (cout, cin)
#include <vector>     // Permite usar la estructura dinámica vector
#include <chrono>     // Permite medir tiempo de ejecución

using namespace std;

// Alias para simplificar el uso del reloj de alta resolución
using Clock = chrono::high_resolution_clock;

// BUBBLE SORT  - ORDENAMINETO BURBUJA
void bubbleSort(vector<int>& arr) {
    int n = arr.size();      // Obtiene el tamaño del vector
    bool swapped;            // Variable para detectar si hubo intercambio

    // Recorre el arreglo n-1 veces
    for (int i = 0; i < n - 1; i++) {
        swapped = false;     // Reinicia el indicador en cada pasada

        // Compara elementos adyacentes
        for (int j = 0; j < n - i - 1; j++) {

            // Si el elemento actual es mayor que el siguiente, intercambia
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);  // Intercambio
                swapped = true;            // Marca que hubo cambio
            }
        }

        // Si no hubo intercambios, el arreglo ya está ordenado
        if (!swapped) break;
    }
}

//  SELECTION SORT - ORDENAMIENTO POR SELECCION
void selectionSort(vector<int>& arr) {
    int n = arr.size();  // Tamaño del vector

    // Recorre todo el arreglo
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;  // Asume que el mínimo está en la posición actual

        // Busca el mínimo en el resto del arreglo
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;  // Actualiza índice del mínimo
        }

        // Intercambia el mínimo encontrado con la posición actual
        swap(arr[i], arr[minIdx]);
    }
}

//  INSERTION SORT - ORDENAMIENTO POR INCERSION
void insertionSort(vector<int>& arr) {
    int n = arr.size();  // Tamaño del vector

    // Empieza desde el segundo elemento
    for (int i = 1; i < n; i++) {
        int key = arr[i];    // Elemento a insertar
        int j = i - 1;       // Índice del elemento anterior

        // Desplaza elementos mayores que key hacia la derecha
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];  // Mueve el elemento
            j--;                  // Retrocede índice
        }

        // Inserta key en la posición correcta
        arr[j + 1] = key;
    }
}

//  SHELL SORT - ORDENACION POR COMPARACION
void shellSort(vector<int>& arr) {
    int n = arr.size();  // Tamaño del vector

    // Gap inicial (intervalo), se va reduciendo a la mitad
    for (int gap = n / 2; gap > 0; gap /= 2) {

        // Aplica insertion sort con salto (gap)
        for (int i = gap; i < n; i++) {
            int temp = arr[i];  // Guarda el valor actual
            int j;

            // Reorganiza elementos separados por gap
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];  // Desplaza hacia adelante
            }

            // Inserta el elemento en su posición correcta
            arr[j] = temp;
        }
    }
}

//  FUNCIÓN DE TEST 
void test(vector<int> data, void(*func)(vector<int>&), const string& name) {

    auto arr = data;  // Copia los datos para no modificar el original

    auto t1 = Clock::now();  // Tiempo inicial

    func(arr);               // Ejecuta el algoritmo de ordenamiento

    auto t2 = Clock::now();  // Tiempo final

    // Imprime el tiempo en microsegundos
    cout << name << " took "
         << chrono::duration_cast<chrono::microseconds>(t2 - t1).count()
         << " μs\n";
}


int main() {

    // Diferentes tamaños de prueba
    vector<int> sizes = {10, 100, 1000};

    // Recorre cada tamaño
    for (int n : sizes) {

        vector<int> data(n);  // Crea vector de tamaño n

        // Llena el vector con números aleatorios
        for (int i = 0; i < n; i++)
            data[i] = rand();

        // Muestra el tamaño actual
        cout << "--- Size: " << n << " ---\n";

        // Ejecuta cada algoritmo con los mismos datos
        test(data, bubbleSort, "Bubble Sort");
        test(data, selectionSort, "Selection Sort");
        test(data, insertionSort, "Insertion Sort");
        test(data, shellSort, "Shell Sort");
    }

    return 0;  // Fin del programa
}
