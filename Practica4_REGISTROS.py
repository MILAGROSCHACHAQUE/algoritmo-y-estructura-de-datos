# Importa el módulo csv, que permite leer y escribir archivos en formato CSV
import csv

# Importa el módulo os, que proporciona funciones para interactuar con el sistema operativo.
import os


# -----------------------------------------------------------------------------
# CLASE ESTUDIANTE
# -----------------------------------------------------------------------------
# Esta clase representa un nodo de una lista enlazada.
# Cada objeto Estudiante almacena los datos de un estudiante y una referencia
# al siguiente nodo de la lista.
class Estudiante:

    # Método constructor. Se ejecuta automáticamente al crear un objeto.
    def __init__(self, id, nombre, correo, escuela, anio_ingreso):

        # Identificador único del estudiante.
        self.id = id

        # Nombre completo del estudiante.
        self.nombre = nombre

        # Correo electrónico.
        self.correo = correo

        # Escuela profesional o carrera.
        self.escuela = escuela

        # Año de ingreso a la institución.
        self.anio_ingreso = anio_ingreso

        # Referencia al siguiente nodo de la lista enlazada.
        # Inicialmente no apunta a ningún nodo.
        self.siguiente = None


# -----------------------------------------------------------------------------
# CLASE LISTAESTUDIANTES
# -----------------------------------------------------------------------------
# Implementa una lista enlazada simple para almacenar objetos Estudiante.
# Incluye operaciones de agregar, mostrar, buscar, modificar, eliminar,
# guardar y cargar desde archivo.
class ListaEstudiantes:

    # Constructor de la clase.
    def __init__(self):

        # Referencia al primer nodo de la lista.
        # Si la lista está vacía, su valor es None.
        self.cabeza = None

        # Variable que almacena el próximo ID disponible.
        self.siguiente_id = 1


    # -------------------------------------------------------------------------
    # AGREGAR ESTUDIANTE
    # -------------------------------------------------------------------------
    # Crea un nuevo nodo y lo inserta al final de la lista.
    def agregar_estudiante(self, nombre, correo, escuela, anio_ingreso):

        # Crea un nuevo objeto Estudiante usando el ID actual.
        nuevo = Estudiante(self.siguiente_id, nombre, correo, escuela, anio_ingreso)

        # Incrementa el contador para que el próximo estudiante tenga un ID único.
        self.siguiente_id += 1

        # Si la lista está vacía.
        if self.cabeza is None:

            # El nuevo nodo se convierte en la cabeza.
            self.cabeza = nuevo

        else:

            # Comienza desde el primer nodo.
            actual = self.cabeza

            # Recorre la lista hasta llegar al último nodo.
            while actual.siguiente is not None:
                actual = actual.siguiente

            # Conecta el último nodo con el nuevo.
            actual.siguiente = nuevo

        # Muestra un mensaje de confirmación.
        print(f"Estudiante agregado con éxito. ID asignado: {nuevo.id}")


    # -------------------------------------------------------------------------
    # MOSTRAR TODOS LOS ESTUDIANTES
    # -------------------------------------------------------------------------
    # Recorre la lista e imprime la información de cada estudiante.
    def mostrar_estudiantes(self):

        # Si la lista está vacía.
        if self.cabeza is None:
            print("No hay estudiantes registrados.")
            return

        # Apunta al primer nodo.
        actual = self.cabeza

        # Encabezado.
        print("--- Lista de Estudiantes ---")

        # Recorre la lista hasta llegar al final.
        while actual is not None:

            # Muestra los datos del nodo actual.
            print(f"ID: {actual.id}")
            print(f"Nombre: {actual.nombre}")
            print(f"Correo: {actual.correo}")
            print(f"Escuela: {actual.escuela}")
            print(f"Año de Ingreso: {actual.anio_ingreso}")
            print("---------------------------")

            # Avanza al siguiente nodo.
            actual = actual.siguiente


    # -------------------------------------------------------------------------
    # BUSCAR POR ID
    # -------------------------------------------------------------------------
    # Busca un estudiante utilizando su identificador único.
    def buscar_por_id(self, id_buscar):

        # Inicia desde la cabeza.
        actual = self.cabeza

        # Recorre todos los nodos.
        while actual is not None:

            # Si el ID coincide.
            if actual.id == id_buscar:

                # Muestra la información del estudiante.
                print("--- Estudiante Encontrado ---")
                print(f"ID: {actual.id}")
                print(f"Nombre: {actual.nombre}")
                print(f"Correo: {actual.correo}")
                print(f"Escuela: {actual.escuela}")
                print(f"Año de Ingreso: {actual.anio_ingreso}")

                # Termina la función inmediatamente.
                return

            # Continúa con el siguiente nodo.
            actual = actual.siguiente

        # Si no se encontró ningún estudiante con ese ID.
        print(f"Estudiante con ID {id_buscar} no encontrado.")


    # -------------------------------------------------------------------------
    # BUSCAR POR NOMBRE
    # -------------------------------------------------------------------------
    # Busca estudiantes cuyo nombre contenga el texto ingresado.
    # La búsqueda no distingue mayúsculas y minúsculas.
    def buscar_por_nombre(self, nombre_buscar):

        # Inicia desde la cabeza.
        actual = self.cabeza

        # Bandera para saber si se encontró al menos una coincidencia.
        encontrado = False

        # Recorre la lista.
        while actual is not None:

            # Convierte ambos textos a minúsculas y verifica si uno está dentro del otro.
            if nombre_buscar.lower() in actual.nombre.lower():

                # Muestra los datos del estudiante encontrado.
                print("--- Estudiante Encontrado ---")
                print(f"ID: {actual.id}")
                print(f"Nombre: {actual.nombre}")
                print(f"Correo: {actual.correo}")
                print(f"Escuela: {actual.escuela}")
                print(f"Año de Ingreso: {actual.anio_ingreso}")

                # Marca que sí hubo coincidencias.
                encontrado = True

            # Avanza al siguiente nodo.
            actual = actual.siguiente

        # Si no se encontró ninguna coincidencia.
        if not encontrado:
            print(f"Ningún estudiante encontrado con el nombre: {nombre_buscar}")


    # -------------------------------------------------------------------------
    # MODIFICAR ESTUDIANTE
    # -------------------------------------------------------------------------
    # Permite actualizar uno o varios campos de un estudiante.
    def modificar_estudiante(self, id_modificar):

        # Comienza desde la cabeza.
        actual = self.cabeza

        # Recorre toda la lista.
        while actual is not None:

            # Si encuentra el ID solicitado.
            if actual.id == id_modificar:

                print(f"--- Modificando Estudiante ID {id_modificar} ---")
                print("Dejar en blanco (o presionar Enter) para no modificar el campo.")

                # Solicita nuevo nombre.
                nombre = input(f"Nombre actual ({actual.nombre}): ")

                # Si el usuario escribió algo distinto de espacios.
                if nombre.strip(): actual.nombre = nombre

                # Solicita nuevo correo.
                correo = input(f"Correo actual ({actual.correo}): ")

                # Actualiza si se ingresó un valor.
                if correo.strip(): actual.correo = correo

                # Solicita nueva escuela.
                escuela = input(f"Escuela actual ({actual.escuela}): ")

                # Actualiza si corresponde.
                if escuela.strip(): actual.escuela = escuela

                # Solicita nuevo año de ingreso.
                anio = input(f"Año de Ingreso actual ({actual.anio_ingreso}): ")

                # Si se ingresó algún valor.
                if anio.strip(): 
                    try:
                        # Convierte la cadena a entero.
                        actual.anio_ingreso = int(anio)
                    except ValueError:
                        # Si la conversión falla.
                        print("Entrada inválida. El año no se modificó.") 

                # Confirmación.
                print("Datos actualizados exitosamente.")
                return

            # Continúa con el siguiente nodo.
            actual = actual.siguiente

        # Si no se encontró el ID.
        print(f"Estudiante con ID {id_modificar} no encontrado.")


    # -------------------------------------------------------------------------
    # ELIMINAR ESTUDIANTE
    # -------------------------------------------------------------------------
    # Elimina un nodo de la lista según su ID.
    def eliminar_estudiante(self, id_eliminar):

        # Si la lista está vacía.
        if self.cabeza is None:
            print("La lista está vacía.")
            return

        # Caso especial: el nodo a eliminar es la cabeza.
        if self.cabeza.id == id_eliminar:

            # La cabeza pasa a ser el siguiente nodo.
            self.cabeza = self.cabeza.siguiente

            # Confirmación.
            print("Estudiante eliminado exitosamente.")
            return

        # Comienza desde la cabeza.
        actual = self.cabeza

        # Busca el nodo anterior al que se desea eliminar.
        while actual.siguiente is not None and actual.siguiente.id != id_eliminar:
            actual = actual.siguiente

        # Si se encontró el nodo.
        if actual.siguiente is not None:

            # Se salta el nodo eliminado.
            actual.siguiente = actual.siguiente.siguiente

            # Confirmación.
            print("Estudiante eliminado exitosamente.")

        else:

            # Si no se encontró el ID.
            print(f"Estudiante con ID {id_eliminar} no encontrado.") 


    # -------------------------------------------------------------------------
    # GUARDAR EN ARCHIVO CSV
    # -------------------------------------------------------------------------
    # Escribe todos los estudiantes en un archivo CSV.
    def guardar_en_archivo(self, filename):

        # Abre el archivo en modo escritura ('w').
        # newline='' evita líneas en blanco extra.
        # encoding='utf-8' permite caracteres especiales.
        with open(filename, mode='w', newline='', encoding='utf-8') as archivo:

            # Crea un escritor CSV.
            writer = csv.writer(archivo)

            # Escribe la fila de encabezado.
            writer.writerow(['ID', 'Nombre', 'Correo', 'Escuela', 'Año_Ingreso'])

            # Comienza desde la cabeza.
            actual = self.cabeza

            # Recorre toda la lista.
            while actual is not None:

                # Escribe una fila con los datos del estudiante.
                writer.writerow([
                    actual.id,
                    actual.nombre,
                    actual.correo,
                    actual.escuela,
                    actual.anio_ingreso
                ])

                # Avanza al siguiente nodo.
                actual = actual.siguiente

        # Al salir del bloque with, el archivo se cierra automáticamente.
        print(f"Datos guardados en {filename} exitosamente.") 


    # -------------------------------------------------------------------------
    # CARGAR DESDE ARCHIVO CSV
    # -------------------------------------------------------------------------
    # Lee los datos almacenados y reconstruye la lista enlazada.
    def cargar_desde_archivo(self, filename):

        # Verifica si el archivo existe.
        if not os.path.exists(filename): 
            return

        # Reinicia la lista.
        self.cabeza = None

        # Referencia al último nodo insertado.
        ultimo = None

        # Guarda el ID máximo encontrado.
        max_id = 0

        # Abre el archivo en modo lectura.
        with open(filename, mode='r', newline='', encoding='utf-8') as archivo:

            # Crea un lector CSV.
            reader = csv.reader(archivo)

            try:
                # Omite la primera fila (encabezado).
                next(reader) # Saltar el encabezado
            except StopIteration:
                # Si el archivo está vacío.
                return

            # Recorre cada fila del archivo.
            for row in reader:

                # Verifica que tenga exactamente 5 columnas.
                if len(row) == 5:

                    # Crea un nuevo objeto Estudiante con los datos del CSV.
                    nuevo = Estudiante(
                        int(row[0]),
                        row[1],
                        row[2],
                        row[3],
                        int(row[4])
                    )

                    # Actualiza el ID máximo encontrado.
                    if nuevo.id > max_id:
                        max_id = nuevo.id

                    # Inserta el nodo en la lista.
                    if self.cabeza is None:
                        self.cabeza = nuevo
                        ultimo = nuevo
                    else:
                        ultimo.siguiente = nuevo
                        ultimo = nuevo

        # Ajusta el siguiente ID disponible.
        self.siguiente_id = max_id + 1

        # Confirmación.
        print(f"Datos cargados desde {filename} exitosamente.") 


# -----------------------------------------------------------------------------
# FUNCIÓN MOSTRAR MENÚ
# -----------------------------------------------------------------------------
# Imprime el menú principal y retorna la opción elegida por el usuario.
def mostrar_menu(): 

    print("\n=== SISTEMA DE REGISTRO DE ESTUDIANTES ===")
    print("1. Agregar nuevo estudiante")
    print("2. Mostrar todos los estudiantes")
    print("3. Buscar estudiante por ID o nombre")
    print("4. Modificar datos de un estudiante")
    print("5. Eliminar un estudiante")
    print("6. Guardar los datos en archivo .csv")
    print("7. Cargar los datos desde archivo")
    print("8. Salir")

    # Solicita la opción al usuario.
    opcion = input("Seleccione una opción: ")

    # Retorna la opción como cadena.
    return opcion


# -----------------------------------------------------------------------------
# FUNCIÓN PRINCIPAL
# -----------------------------------------------------------------------------
# Controla el flujo general del programa.
def main(): 

    # Crea el objeto que administrará la lista enlazada.
    lista = ListaEstudiantes()

    # Nombre del archivo de almacenamiento.
    filename = "registros.csv"

    # Carga automáticamente los datos al iniciar.
    lista.cargar_desde_archivo(filename)

    # Bucle infinito del menú.
    while True:

        # Muestra el menú y obtiene la opción.
        opcion = mostrar_menu()

        # ---------------------------------------------------------------------
        # OPCIÓN 1: AGREGAR ESTUDIANTE
        # ---------------------------------------------------------------------
        if opcion == '1':
            nombre = input("Ingrese nombre completo: ")
            correo = input("Ingrese correo electrónico: ")
            escuela = input("Ingrese escuela profesional: ")

            try:
                anio = int(input("Ingrese año de ingreso: "))
                lista.agregar_estudiante(nombre, correo, escuela, anio)
            except ValueError:
                print("El año de ingreso debe ser un número entero.") 

        # ---------------------------------------------------------------------
        # OPCIÓN 2: MOSTRAR
        # ---------------------------------------------------------------------
        elif opcion == '2':
            lista.mostrar_estudiantes()

        # ---------------------------------------------------------------------
        # OPCIÓN 3: BUSCAR
        # ---------------------------------------------------------------------
        elif opcion == '3':
            subopcion = input("1. Buscar por ID\n2. Buscar por Nombre\nSeleccione: ") 

            if subopcion == '1':
                try:
                    id_buscar = int(input("Ingrese ID a buscar: "))
                    lista.buscar_por_id(id_buscar)
                except ValueError:
                    print("Entrada inválida.") 

            elif subopcion == '2':
                nombre_buscar = input("Ingrese nombre a buscar: ")
                lista.buscar_por_nombre(nombre_buscar)

            else:
                print("Opción inválida.") 

        # ---------------------------------------------------------------------
        # OPCIÓN 4: MODIFICAR
        # ---------------------------------------------------------------------
        elif opcion == '4':
            try:
                id_modificar = int(input("Ingrese el ID del estudiante a modificar: "))
                lista.modificar_estudiante(id_modificar)
            except ValueError:
                print("Entrada inválida.") 

        # ---------------------------------------------------------------------
        # OPCIÓN 5: ELIMINAR
        # ---------------------------------------------------------------------
        elif opcion == '5':
            try:
                id_eliminar = int(input("Ingrese el ID del estudiante a eliminar: "))
                lista.eliminar_estudiante(id_eliminar)
            except ValueError:
                print("Entrada inválida.") 

        # ---------------------------------------------------------------------
        # OPCIÓN 6: GUARDAR
        # ---------------------------------------------------------------------
        elif opcion == '6':
            lista.guardar_en_archivo(filename)

        # ---------------------------------------------------------------------
        # OPCIÓN 7: CARGAR
        # ---------------------------------------------------------------------
        elif opcion == '7':
            lista.cargar_desde_archivo(filename)

        # ---------------------------------------------------------------------
        # OPCIÓN 8: SALIR
        # ---------------------------------------------------------------------
        elif opcion == '8':
            print("Guardando datos antes de salir...")
            lista.guardar_en_archivo(filename)
            print("Saliendo del programa...") 
            break

        # ---------------------------------------------------------------------
        # OPCIÓN INVÁLIDA
        # ---------------------------------------------------------------------
        else:
            print("Opción inválida. Intente nuevamente.") 


# -----------------------------------------------------------------------------
# PUNTO DE ENTRADA DEL PROGRAMA
# -----------------------------------------------------------------------------
# Esta condición garantiza que main() se ejecute solo si este archivo
# se ejecuta directamente, y no cuando se importa como módulo.
if __name__ == "__main__": 
    main()
