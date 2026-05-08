# Implementación simple de una Cola en Python

# Función para recorrer y mostrar la cola
def recorrer_cola(cola):
    if not cola:
        print("La cola está vacía.")
    else:
        print("Contenido de la cola (Frente -> Final):", cola)


def main():
    cola = []

    print("--- Implementación de Cola en Python ---")

    # Insertar elementos (enqueue)
    elementos = [3, 6, 9, 12]
    for num in elementos:
        cola.append(num)  # append funciona como enqueue

    print("\nCola después de insertar elementos:")
    recorrer_cola(cola)

    # Mostrar el frente
    if cola:
        print("\nFrente de la cola:", cola[0])

    # Eliminar un elemento (dequeue)
    if cola:
        eliminado = cola.pop(0)  # elimina el primer elemento
        print("\nElemento eliminado (dequeue):", eliminado)

    # Mostrar cola final
    print("\n--- COLA FINAL ---")
    recorrer_cola(cola)


if __name__ == "__main__":
    main()
