# Definición del nodo
class Nodo:
    def __init__(self, dato):
        self.dato = dato
        self.siguiente = None


# Lista enlazada simple
class ListaEnlazada:
    def __init__(self):
        self.cabeza = None

    # Insertar al inicio
    def insertar_inicio(self, dato):
        nuevo = Nodo(dato)
        nuevo.siguiente = self.cabeza
        self.cabeza = nuevo

    # Insertar al final
    def insertar_final(self, dato):
        nuevo = Nodo(dato)

        if self.cabeza is None:
            self.cabeza = nuevo
        else:
            actual = self.cabeza
            while actual.siguiente:
                actual = actual.siguiente
            actual.siguiente = nuevo

    # Eliminar el primer nodo
    def eliminar_inicio(self):
        if self.cabeza:
            eliminado = self.cabeza.dato
            self.cabeza = self.cabeza.siguiente
            return eliminado

    # Recorrer y mostrar lista
    def mostrar(self):
        actual = self.cabeza
        print("Lista:", end=" ")
        while actual:
            print(actual.dato, end=" -> ")
            actual = actual.siguiente
        print("None")


def main():
    lista = ListaEnlazada()

    # Insertar al inicio: 8 y 4
    lista.insertar_inicio(8)
    lista.insertar_inicio(4)

    print("Insertado al inicio: 4 y 8")
    lista.mostrar()

    # Insertar al final: 11
    lista.insertar_final(11)

    print("\nInsertado al final: 11")
    lista.mostrar()

    # Eliminar primer nodo
    eliminado = lista.eliminar_inicio()

    print(f"\nPrimer nodo eliminado: {eliminado}")
    lista.mostrar()

    # Mostrar el recorrido completo
    print("\nRecorrido completo de la lista:")
    lista.mostrar()


if __name__ == "__main__":
    main()
