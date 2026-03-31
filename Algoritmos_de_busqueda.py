
# Comparación de algoritmos de búsqueda en Python


# Importación de librerías necesarias
import random        # Para generar números aleatorios
import time          # Para medir tiempos de ejecución
from bisect import bisect_left  # (opcional, búsqueda binaria estándar de Python)


# Búsqueda lineal
# Recorre el arreglo de izquierda a derecha comparando
# cada elemento con el valor buscado.
def busqueda_lineal(a, x):
    for i, val in enumerate(a):   # recorre cada índice y valor
        if val == x:              # si encuentra el valor buscado
            return i              # devuelve la posición
    return -1                     # si no lo encuentra devuelve -1


# Requiere que el arreglo esté ORDENADO.
# Divide el rango a la mitad en cada paso.
# Complejidad: O(log n)

def busqueda_binaria(a, x):
    l, r = 0, len(a) - 1          # l = inicio, r = final
    while l <= r:                 # mientras el rango sea válido
        m = l + (r - l) // 2      # punto medio
        if a[m] == x:             # encontrado
            return m
        elif a[m] < x:            # si el valor del medio es menor
            l = m + 1             # busca en la mitad derecha
        else:                     # si el valor del medio es mayor
            r = m - 1             # busca en la mitad izquierda
    return -1                     # no encontrado



# Búsqueda exponencial
# Primero expande un rango de búsqueda exponencialmente
# (1, 2, 4, 8, ...) hasta pasarse del valor o del tamaño.
# Luego aplica búsqueda binaria en ese rango.
# Complejidad: O(log pos), donde pos es la posición del elemento.
def busqueda_exponencial(a, x):
    if not a:          # si el arreglo está vacío
        return -1
    if a[0] == x:      # caso especial: primer elemento
        return 0

    i = 1
# duplicar rango mientras no se pase y el valor sea menor que x
    while i < len(a) and a[i] < x:
        i *= 2

    # definir límites del rango
    l, r = i // 2, min(i, len(a) - 1)

    # búsqueda binaria dentro del rango [l, r]
    while l <= r:
        m = l + (r - l) // 2
        if a[m] == x:
            return m
        elif a[m] < x:
            l = m + 1
        else:
            r = m - 1
    return -1


# Búsqueda por interpolación
# Estima la posición del valor basándose en su relación
# proporcional dentro del rango.
# Muy eficiente si los datos están uniformemente distribuidos.
# Complejidad promedio: O(log log n). Peor caso: O(n).
def busqueda_interpolacion(a, x):
    low, high = 0, len(a) - 1

    # mientras el rango sea válido y x esté dentro de los extremos
    while low <= high and x >= a[low] and x <= a[high]:
        if a[low] == a[high]:              # todos los valores iguales
            return low if a[low] == x else -1

        # estimación de la posición según proporción
        pos = low + int((high - low) * ((x - a[low]) / (a[high] - a[low])))

        if pos < low or pos > high:        # fuera de rango
            break

        if a[pos] == x:                    # encontrado
            return pos
        elif a[pos] < x:                   # mover límite inferior
            low = pos + 1
        else:                              # mover límite superior
            high = pos - 1
    return -1                              # no encontrado



# Función medir
# Ejecuta un buscador sobre un conjunto de queries
# y mide el tiempo promedio de ejecución por búsqueda.
def medir(a, queries, buscador):
    t0 = time.perf_counter()         # tiempo inicial de alta precisión
    checksum = 0                     # acumulador (para evitar optimización)

    for x in queries:                # ejecutar todas las queries
        checksum += buscador(a, x)   # aplicar el buscador

    t1 = time.perf_counter()         # tiempo final
    # devuelve el tiempo promedio en milisegundos
    return (t1 - t0) * 1000 / len(queries)


# Programa principal

def main():
    # Definir tamaños de prueba
    ns = [10000, 100000, 500000]   # tamaños de dataset
    rng = random.Random(123)       # generador aleatorio con semilla fija

    # Repetir para cada tamaño
    for n in ns:
        # a) Dataset uniforme ordenado (0..n-1)
        uni = list(range(n))       # lista [0, 1, 2, ..., n-1]

        # b) Dataset sesgado ordenado
        ses = []
        for _ in range(n):
            u = rng.random()                               # número entre 0 y 1
            if u < 0.8:                                    # 80% de los casos
                ses.append(rng.randint(0, int(0.1 * n)))   # valores pequeños
            else:                                          # 20% de los casos
                ses.append(rng.randint(int(0.1 * n), 5 * n)) # valores grandes
        ses.sort()                                         # ordenar el dataset

        # c) Dataset desordenado
        des = uni[:]                # copia del uniforme
        rng.shuffle(des)            # barajar aleatoriamente

   
        # Generación de queries
        def mkqueries(base):
            q = []
            # 70% aciertos (valores que sí están en el dataset)
            for _ in range(700):
                q.append(rng.choice(base))
            # 30% fallos (valores fuera del rango del dataset)
            for i in range(300):
                q.append(10 * len(base) + i)
            rng.shuffle(q)          # mezclar consultas
            return q

        q_uni = mkqueries(uni)      # queries para dataset uniforme
        q_ses = mkqueries(ses)      # queries para dataset sesgado
        q_des = mkqueries(des)      # queries para dataset desordenado

        # Reporte de resultados
        def report(nombre, arr, q):
            print(f"n={n}, dataset={nombre}")
            # búsqueda lineal siempre se puede aplicar
            print(f"  lineal        : {medir(arr, q, busqueda_lineal):.6f} ms/busq")

            # si el arreglo está ordenado, se pueden usar otros algoritmos
            if arr == sorted(arr):
                print(f"  binaria       : {medir(arr, q, busqueda_binaria):.6f} ms/busq")
                print(f"  exponencial   : {medir(arr, q, busqueda_exponencial):.6f} ms/busq")
                print(f"  interpolacion : {medir(arr, q, busqueda_interpolacion):.6f} ms/busq")
            else:
                print("  (datos no ordenados: usar solo búsqueda lineal)")

        # Llamadas al reporte para cada dataset
        report("uniforme_ordenado", uni, q_uni)
        report("sesgado_ordenado", ses, q_ses)
        report("desordenado", des, q_des)
        print("*" * 35)  # separador visual


# Ejecutar el programa principal

if __name__ == "__main__":
    main()
