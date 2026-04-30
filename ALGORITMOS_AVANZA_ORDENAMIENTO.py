import time        # Permite medir tiempos de ejecución (benchmarking)
import random      # Generación de números aleatorios
import sys         # Acceso a funciones del sistema (como límite de recursión)

# Aumenta el límite de recursión de Python (por defecto ~1000)
# Necesario para evitar errores en QuickSort con listas grandes
sys.setrecursionlimit(2000000)


# 1. QUICK SORT

# Función de partición: reorganiza el arreglo en torno a un pivote
def partition(arr, low, high):
    # Selecciona el índice medio como pivote para evitar peor caso típico
    mid = low + (high - low) // 2
    
    # Intercambia el elemento medio con el final
    # Esto permite usar siempre arr[high] como pivote
    arr[mid], arr[high] = arr[high], arr[mid]
    
    pivot = arr[high]  # Define el pivote
    
    i = low - 1  # Índice del elemento menor
    
    # Recorre el arreglo desde low hasta high-1
    for j in range(low, high):
        # Si el elemento actual es menor que el pivote
        if arr[j] < pivot:
            i += 1  # Incrementa el índice
            # Intercambia el elemento actual con el menor encontrado
            arr[i], arr[j] = arr[j], arr[i]
    
    # Coloca el pivote en su posición correcta
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    
    return i + 1  # Retorna la posición del pivote


# Función recursiva de QuickSort
def quick_sort_helper(arr, low, high):
    # Condición base: subarreglo con más de un elemento
    if low < high:
        # Obtiene índice del pivote
        pi = partition(arr, low, high)
        
        # Ordena subarreglo izquierdo
        quick_sort_helper(arr, low, pi - 1)
        
        # Ordena subarreglo derecho
        quick_sort_helper(arr, pi + 1, high)


# Función principal QuickSort
def quick_sort(arr):
    # Verifica que la lista no esté vacía
    if arr:
        quick_sort_helper(arr, 0, len(arr) - 1)



# 2. MERGE SORT

# Función que fusiona dos sublistas ordenadas
def merge(arr, l, m, r):
    # Tamaños de los subarreglos
    n1 = m - l + 1
    n2 = r - m
    
    # Copias temporales de los subarreglos
    L = arr[l : l + n1]
    R = arr[m + 1 : m + 1 + n2]
    
    i = 0  # Índice para L
    j = 0  # Índice para R
    k = l  # Índice para arreglo original
    
    # Mezcla ambos subarreglos en orden
    while i < n1 and j < n2:
        if L[i] <= R[j]:
            arr[k] = L[i]
            i += 1
        else:
            arr[k] = R[j]
            j += 1
        k += 1
    
    # Copia elementos restantes de L (si hay)
    while i < n1:
        arr[k] = L[i]
        i += 1
        k += 1
    
    # Copia elementos restantes de R (si hay)
    while j < n2:
        arr[k] = R[j]
        j += 1
        k += 1


# Función recursiva de MergeSort
def merge_sort_helper(arr, l, r):
    # Caso base
    if l < r:
        # Calcula el punto medio
        m = l + (r - l) // 2
        
        # Ordena mitad izquierda
        merge_sort_helper(arr, l, m)
        
        # Ordena mitad derecha
        merge_sort_helper(arr, m + 1, r)
        
        # Fusiona ambas mitades
        merge(arr, l, m, r)


# Función principal
def merge_sort(arr):
    if arr:
        merge_sort_helper(arr, 0, len(arr) - 1)



# 3. TIM SORT (Híbrido)


RUN = 32  # Tamaño base de bloques pequeños

# Insertion Sort usado por TimSort en subarreglos pequeños
def insertion_sort_tim(arr, left, right):
    for i in range(left + 1, right + 1):
        temp = arr[i]  # Valor a insertar
        j = i - 1
        
        # Desplaza elementos mayores hacia la derecha
        while j >= left and arr[j] > temp:
            arr[j + 1] = arr[j]
            j -= 1
        
        # Inserta el elemento en su posición correcta
        arr[j + 1] = temp


# Implementación simplificada de TimSort
def tim_sort(arr):
    n = len(arr)
    
    # Ordena bloques pequeños con InsertionSort
    for i in range(0, n, RUN):
        insertion_sort_tim(arr, i, min(i + RUN - 1, n - 1))
    
    size = RUN
    
    # Fusiona bloques de tamaño creciente
    while size < n:
        for left in range(0, n, 2 * size):
            mid = left + size - 1
            right = min((left + 2 * size - 1), (n - 1))
            
            # Solo fusiona si hay dos bloques válidos
            if mid < right:
                merge(arr, left, mid, right)
        
        size *= 2  # Duplica tamaño del bloque



# 4. COUNTING SORT

def counting_sort(arr):
    if not arr:
        return
    
    max_val = max(arr)  # Valor máximo
    min_val = min(arr)  # Valor mínimo
    
    rango = max_val - min_val + 1  # Tamaño del rango
    
    # Inicializa arreglo de conteo y salida
    count = [0] * rango
    output = [0] * len(arr)
    
    # Cuenta frecuencia de cada valor
    for i in range(len(arr)):
        count[arr[i] - min_val] += 1
    
    # Convierte conteo en acumulado
    for i in range(1, len(count)):
        count[i] += count[i - 1]
    
    # Construye el arreglo ordenado (estable)
    for i in range(len(arr) - 1, -1, -1):
        output[count[arr[i] - min_val] - 1] = arr[i]
        count[arr[i] - min_val] -= 1
    
    # Copia resultado al arreglo original
    for i in range(len(arr)):
        arr[i] = output[i]



# 5. RADIX SORT

# Counting Sort por dígito específico
def count_sort_for_radix(arr, exp):
    n = len(arr)
    
    output = [0] * n
    count = [0] * 10  # Base decimal (0-9)
    
    # Cuenta ocurrencias de dígitos
    for i in range(n):
        index = arr[i] // exp
        count[index % 10] += 1
    
    # Acumulación
    for i in range(1, 10):
        count[i] += count[i - 1]
    
    # Construcción estable
    i = n - 1
    while i >= 0:
        index = arr[i] // exp
        output[count[index % 10] - 1] = arr[i]
        count[index % 10] -= 1
        i -= 1
    
    # Copia resultado
    for i in range(n):
        arr[i] = output[i]


# Función principal RadixSort
def radix_sort(arr):
    if not arr:
        return
    
    max_val = max(arr)  # Determina número de dígitos
    exp = 1
    
    # Procesa cada dígito (unidades, decenas, centenas...)
    while max_val // exp > 0:
        count_sort_for_radix(arr, exp)
        exp *= 10



# 6. BUCKET SORT


def bucket_sort(arr):
    if not arr:
        return
    
    max_val = max(arr)
    min_val = min(arr)
    
    bucket_count = len(arr)
    
    # Crea lista de buckets vacíos
    buckets = [[] for _ in range(bucket_count)]
    
    # Caso trivial: todos iguales
    if max_val == min_val:
        return
    
    # Tamaño del rango por bucket
    rango = (max_val - min_val + 1) / bucket_count
    
    # Distribuye elementos en buckets
    for i in range(len(arr)):
        b_idx = int((arr[i] - min_val) / rango)
        
        # Ajuste por posibles errores de precisión
        if b_idx >= bucket_count:
            b_idx = bucket_count - 1
        
        buckets[b_idx].append(arr[i])
    
    idx = 0
    
    # Ordena cada bucket y concatena
    for i in range(bucket_count):
        buckets[i].sort()  # Usa Timsort interno de Python
        for j in range(len(buckets[i])):
            arr[idx] = buckets[i][j]
            idx += 1


#Analisis temporal de los algoritmos

def test(data, func, name):
    # Copia los datos para evitar modificar el original
    arr = data.copy()
    
    t1 = time.perf_counter()  # Tiempo inicial
    func(arr)                 # Ejecuta algoritmo
    t2 = time.perf_counter()  # Tiempo final
    
    # Convierte a microsegundos
    duracion_us = int((t2 - t1) * 1_000_000)
    
    # Muestra resultado formateado
    print(f"{name:<18} tomó {duracion_us:>10} μs")


#funcion principal
def main():
    sizes = [10000, 100000, 1000000]  # Tamaños de prueba
    
    # Fija semilla para reproducibilidad
    random.seed(42)
    
    for n in sizes:
        # Genera lista de números aleatorios
        data = [random.randint(1, 10000000) for _ in range(n)]
        
        print("\n============================================")
        print(f"****** Probando con N = {n} elementos ******")
        print("============================================")
        
        # Ejecuta benchmarks
        test(data, quick_sort,     "Quick Sort")
        test(data, merge_sort,     "Merge Sort")
        test(data, tim_sort,       "Tim Sort")
        test(data, radix_sort,     "Radix Sort")
        test(data, bucket_sort,    "Bucket Sort")
        test(data, counting_sort,  "Counting Sort")


# Punto de entrada del programa
if __name__ == "__main__":
    main() #llama a la funcion principal
