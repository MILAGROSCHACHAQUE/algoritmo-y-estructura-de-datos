import streamlit as st
import pandas as pd
from collections import deque
import copy

# ============================================================================
# CONFIGURACIÓN DE LA PÁGINA
# ============================================================================
st.set_page_config(
    page_title="Excel Académico Pro",
    page_icon="🟢",
    layout="wide",
    initial_sidebar_state="expanded"
)

# Estilos CSS para simular el entorno de Excel (Verde corporativo, tarjetas limpias)
st.markdown("""
    <style>
    .main { background-color: #f3f4f6; }
    .stButton>button { width: 100%; border-radius: 4px; background-color: #107c41; color: white; border: none;}
    .stButton>button:hover { background-color: #0b592e; color: white; }
    .excel-header {
        background-color: #107c41;
        color: white;
        padding: 15px;
        border-radius: 5px;
        margin-bottom: 20px;
    }
    .metric-card {
        background-color: white;
        padding: 15px;
        border-radius: 6px;
        border-left: 5px solid #107c41;
        box-shadow: 0 2px 4px rgba(0,0,0,0.05);
    }
    </style>
    """, unsafe_allow_html=True)

# ============================================================================
# INICIALIZACIÓN DEL ESTADO GLOBAL
# ============================================================================
# Datos iniciales para que el Excel no aparezca completamente vacío y se vea el formato
if 'hoja' not in st.session_state:
    st.session_state.hoja = [
        {"codigo": "EST01", "nombre": "Alvarado Pérez, Luis", "nota1": 15.0, "nota2": 14.0, "nota3": 16.0, "promedio": 15.0},
        {"codigo": "EST02", "nombre": "Castro Solis, Maria", "nota1": 11.0, "nota2": 13.0, "nota3": 12.0, "promedio": 12.0},
        {"codigo": "EST03", "nombre": "Bermudez Luna, Carlos", "nota1": 18.0, "nota2": 17.0, "nota3": 19.0, "promedio": 18.0}
    ]
if 'indiceHash' not in st.session_state:
    st.session_state.indiceHash = {}
if 'historial' not in st.session_state:
    st.session_state.historial = []
if 'colaAtencion' not in st.session_state:
    st.session_state.colaAtencion = deque()

# ============================================================================
# CORE LOGIC & ALGORITMOS
# ============================================================================

def actualizar_hash_y_promedios():
    """Recalcula promedios estilo fórmulas de Excel y reconstruye el Hash O(1)"""
    for est in st.session_state.hoja:
        # Reemplazar valores nulos/vacíos por 0 para evitar errores numéricos
        n1 = float(est.get('nota1', 0) or 0)
        n2 = float(est.get('nota2', 0) or 0)
        n3 = float(est.get('nota3', 0) or 0)
        est['promedio'] = round((n1 + n2 + n3) / 3.0, 2)
    
    st.session_state.indiceHash = {
        est['codigo']: idx for idx, est in enumerate(st.session_state.hoja) if est.get('codigo')
    }

def guardar_historial():
    st.session_state.historial.append(copy.deepcopy(st.session_state.hoja))

# --- RECURSIVIDAD PURA (Estadísticas) ---
def suma_promedios_recursiva(hoja_calculo, i):
    if i == len(hoja_calculo):
        return 0.0
    return float(hoja_calculo[i].get('promedio', 0) or 0) + suma_promedios_recursiva(hoja_calculo, i + 1)

# --- ALGORITMOS DE ORDENAMIENTO (Idénticos a C++) ---
def particion_quicksort(arr, bajo, alto):
    pivote = arr[alto]['promedio']
    i = bajo - 1
    for j in range(bajo, alto):
        if arr[j]['promedio'] >= pivote: # Descendente
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[alto] = arr[alto], arr[i + 1]
    return i + 1

def quicksort(arr, bajo, alto):
    if bajo < alto:
        pi = particion_quicksort(arr, bajo, alto)
        quicksort(arr, bajo, pi - 1)
        quicksort(arr, pi + 1, alto)

def merge(arr, izq, medio, der):
    L = arr[izq:medio + 1]
    R = arr[medio + 1:der + 1]
    i = j = 0
    k = izq
    while i < len(L) and j < len(R):
        if str(L[i]['codigo']) <= str(R[j]['codigo']): # Ascendente alfanumérico
            arr[k] = L[i]; i += 1
        else:
            arr[k] = R[j]; j += 1
        k += 1
    while i < len(L): arr[k] = L[i]; i += 1; k += 1
    while j < len(R): arr[k] = R[j]; j += 1; k += 1

def mergesort(arr, izq, der):
    if izq < der:
        medio = izq + (der - izq) // 2
        mergesort(arr, izq, medio)
        mergesort(arr, medio + 1, der)
        merge(arr, izq, medio, der)

# Asegurar sincronización inicial
actualizar_hash_y_promedios()

# ============================================================================
# INTERFAZ DE USUARIO (ESTILO EXCEL)
# ============================================================================

st.markdown("""
    <div class='excel-header'>
        <h1>🟢 Libro1 - Excel Académico</h1>
        <p>Edita directamente las celdas como en Excel. Las fórmulas de promedio se calculan automáticamente.</p>
    </div>
    """, unsafe_allow_html=True)

# --- BARRA DE FÓRMULAS / INDICADORES (MÉTRICAS) ---
if st.session_state.hoja:
    total_filas = len(st.session_state.hoja)
    suma_total = suma_promedios_recursiva(st.session_state.hoja, 0)
    promedio_general = round(suma_total / total_filas, 2)
else:
    total_filas, promedio_general = 0, 0.0

col_m1, col_m2, col_m3 = st.columns(3)
with col_m1:
    st.markdown(f"<div class='metric-card'><b>CONTAR(Filas):</b> <span style='font-size:20px; color:#107c41;'>{total_filas}</span></div>", unsafe_allow_html=True)
with col_m2:
    st.markdown(f"<div class='metric-card'><b>PROMEDIO(General):</b> <span style='font-size:20px; color:#107c41;'>{promedio_general}</span></div>", unsafe_allow_html=True)
with col_m3:
    st.markdown(f"<div class='metric-card'><b>COLA SECRETARÍA:</b> <span style='font-size:20px; color:#107c41;'>{len(st.session_state.colaAtencion)} en espera</span></div>", unsafe_allow_html=True)

st.write("")

# --- CUERPO PRINCIPAL (HOJA DE CÁLCULO ACTIVA) ---
col_hoja, col_acciones = st.columns([3, 1])

with col_hoja:
    st.subheader("📊 Hoja1")
    
    # Transformamos el estado a DataFrame para pasárselo al editor tipo Excel
    df_actual = pd.DataFrame(st.session_state.hoja)
    
    # Asegurar el orden de las columnas visibles
    column_order = ["codigo", "nombre", "nota1", "nota2", "nota3", "promedio"]
    for col in column_order:
        if col not in df_actual.columns:
            df_actual[col] = ""
    df_actual = df_actual[column_order]

    # COMPONENTE CLAVE: El editor interactivo de Excel
    df_editado = st.data_editor(
        df_actual,
        use_container_width=True,
        hide_index=False,
        num_rows="dynamic",  # Permite al usuario borrar o añadir filas abajo con el botón nativo "+"
        column_config={
            "codigo": st.column_config.TextColumn("Código (ID)", help="Código único del alumno", required=True),
            "nombre": st.column_config.TextColumn("Apellidos y Nombres", width="large"),
            "nota1": st.column_config.NumberColumn("Nota 1", min_value=0, max_value=20, format="%.1f"),
            "nota2": st.column_config.NumberColumn("Nota 2", min_value=0, max_value=20, format="%.1f"),
            "nota3": st.column_config.NumberColumn("Nota 3", min_value=0, max_value=20, format="%.1f"),
            "promedio": st.column_config.NumberColumn("Promedio (Fx)", format="%.2f", disabled=True) # Bloqueado (Es una fórmula)
        }
    )

    # Si el usuario hace cualquier cambio en la tabla, guardamos en el historial y sincronizamos
    if not df_editado.equals(df_actual):
        guardar_historial()
        st.session_state.hoja = df_editado.to_dict(orient="records")
        actualizar_hash_y_promedios()
        st.rerun()

with col_acciones:
    st.subheader("⚡ Herramientas")
    
    # Botones estilo cintas de opciones de Excel
    if st.button("🔽 Ordenar A-Z (MergeSort Código)"):
        if st.session_state.hoja:
            guardar_historial()
            mergesort(st.session_state.hoja, 0, len(st.session_state.hoja) - 1)
            actualizar_hash_y_promedios()
            st.success("Ordenado alfanuméricamente.")
            st.rerun()
            
    if st.button("🔽 Ordenar Max-Min (QuickSort Promedio)"):
        if st.session_state.hoja:
            guardar_historial()
            quicksort(st.session_state.hoja, 0, len(st.session_state.hoja) - 1)
            actualizar_hash_y_promedios()
            st.success("Ordenado por rendimiento.")
            st.rerun()

    if st.button("⏪ Deshacer Cambio (Ctrl + Z)"):
        if st.session_state.historial:
            st.session_state.hoja = st.session_state.historial.pop()
            actualizar_hash_y_promedios()
            st.warning("Última acción revertida.")
            st.rerun()
        else:
            st.info("Nada que deshacer.")

    st.divider()
    
    # Sección de Búsqueda Binaria/Hash veloz
    st.subheader("🔍 Barra de Búsqueda")
    search_code = st.text_input("Buscar código alumno:").strip()
    if search_code:
        if search_code in st.session_state.indiceHash:
            idx = st.session_state.indiceHash[search_code]
            alumno = st.session_state.hoja[idx]
            st.info(f"**Fila {idx+1}:** {alumno['nombre']} \n\n **Promedio:** {alumno['promedio']}")
        else:
            st.error("No se encuentra en los registros indexados.")

    st.divider()

    # Sistema de Colas de Secretaría
    st.subheader("🏢 Fila de Espera (FIFO)")
    c_cod = st.text_input("Código para Encolar:").strip()
    col_b1, col_b2 = st.columns(2)
    with col_b1:
        if st.button("Encolar"):
            if c_cod in st.session_state.indiceHash:
                st.session_state.colaAtencion.append(c_cod)
                st.success(f"{c_cod} en cola.")
                st.rerun()
            else:
                st.error("Código inválido.")
    with col_b2:
        if st.button("Atender"):
            if st.session_state.colaAtencion:
                atendido = st.session_state.colaAtencion.popleft()
                if atendido in st.session_state.indiceHash:
                    st.balloons()
                    st.success(f"Atendiendo a: {st.session_state.hoja[st.session_state.indiceHash[atendido]]['nombre']}")
                else:
                    st.warning("El estudiante ya no existe en el Excel.")
            else:
                st.info("No hay nadie en cola.")
