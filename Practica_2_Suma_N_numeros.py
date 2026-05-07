import time
import matplotlib.pyplot as plt

def suma_bucle(n):
    suma = 0
    for i in range(1, n + 1):
        suma += i
    return suma

def suma_formula(n):
    return n * (n + 1) // 2

ns = [1000, 10000, 100000, 1000000]

tiempos_bucle = []
tiempos_formula = []

for n in ns:
    # Bucle
    inicio = time.perf_counter()
    _ = suma_bucle(n)
    fin = time.perf_counter()
    tiempos_bucle.append((fin - inicio) * 1e6)

    # Fórmula
    inicio = time.perf_counter()
    _ = suma_formula(n)
    fin = time.perf_counter()
    tiempos_formula.append((fin - inicio) * 1e6)

# Tabla en la consola
print(f"{'n':>10} {'Bucle (μs)':>12} {'Fórmula (μs)':>14}")
print("-" * 38)
for n, t1, t2 in zip(ns, tiempos_bucle, tiempos_formula):
    print(f"{n:>10} {t1:12.2f} {t2:14.2f}")
    
plt.figure(figsize=(8, 5))
plt.plot(ns, tiempos_bucle, label="Bucle (O(n))", marker="o")
plt.plot(ns, tiempos_formula, label="Fórmula (O(1))", marker="s")
plt.xlabel("n (números naturales)")
plt.ylabel("Tiempo de ejecución (μs)")
plt.title("Comparación: Suma de los primeros n números naturales")
plt.legend()
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.savefig("tiempos_suma.png", dpi=150)
plt.show()
