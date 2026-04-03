# Proyecto1-Estructura-De-Datos
# Catálogo de Productos · Supermercado EDD 2026

Sistema de gestión de inventario para supermercado que implementa múltiples estructuras de datos para búsqueda y almacenamiento eficiente de productos.

## Estructuras de Datos Implementadas

| Estructura | Clave de Indexación | Uso Principal |
|---|---|---|
| Árbol AVL | Nombre del producto | Búsqueda/listado alfabético |
| Árbol B (t=3) | Fecha de caducidad | Búsqueda por rango de fechas |
| Árbol B+ (t=3) | Categoría | Listado por categoría |
| Lista Enlazada | — | Secuencial / pruebas comparativas |

---

## Estructura del Proyecto

```
proyecto/
├── main.cpp
├── clases/
│   └── productos/
│       ├── Producto.h
│       └── Producto.cpp
├── estructuras/
│   ├── arbol-avl/
│   │   ├── ArbolAvl.h / .cpp
│   │   └── NodoAvl.h / .cpp
│   ├── arbol-b/
│   │   ├── ArbolB.h / .cpp
│   │   └── NodoB.h / .cpp
│   ├── arbol-b+/
│   │   ├── ArbolBMas.h / .cpp
│   │   └── NodoBMas.h / .cpp
│   └── lista-enlazada/
│       ├── ListaEnlazada.h / .cpp
│       └── Nodo.h / .cpp
├── leer-archivos/
│   ├── CargarCSV.h
│   └── CargarCSV.cpp
└── utils/
    └── date/
        └── ConvertDate.h
```

---

## Requisitos

- Compilador C++17 o superior (g++ ≥ 9 recomendado)
- Make (opcional, para usar Makefile)
- Graphviz (`dot`) para generar imágenes de los árboles (opcional)

### Instalar dependencias (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install g++ graphviz
```

### Instalar dependencias (macOS con Homebrew)

```bash
brew install graphviz
```

---

## Compilación

### Compilación manual

Desde la raíz del proyecto, compila todos los `.cpp`:

```bash
g++ -std=c++17 -O2 -Wall \
    main.cpp \
    clases/productos/Producto.cpp \
    estructuras/arbol-avl/ArbolAvl.cpp \
    estructuras/arbol-avl/NodoAvl.cpp \
    estructuras/arbol-b/ArbolB.cpp \
    estructuras/arbol-b/NodoB.cpp \
    estructuras/arbol-b+/ArbolBMas.cpp \
    estructuras/arbol-b+/NodoBMas.cpp \
    estructuras/lista-enlazada/ListaEnlazada.cpp \
    estructuras/lista-enlazada/Nodo.cpp \
    leer-archivos/CargarCSV.cpp \
    -o supermercado
```

### Usando Makefile (si existe)

```bash
make
```

---

## Ejecución

```bash
./supermercado
```

Al iniciar se mostrará el menú principal con las siguientes opciones:

```
DATOS
  1  Cargar catálogo desde CSV
  2  Agregar producto manualmente
  3  Eliminar producto

BÚSQUEDA
  4  Por nombre        → AVL  O(log n)
  5  Por categoría     → Árbol B+  O(log n + k)
  6  Por rango de fecha→ Árbol B  O(log n + k)

LISTADOS
  7  Listar por nombre   (AVL in-order)
  8  Listar por fecha    (Árbol B in-order)
  9  Listar por categoría(Árbol B+ hojas)

HERRAMIENTAS
 10  Preview árbol en consola
 11  Generar archivos DOT (.dot / .png)
 12  Comparar tiempos de búsqueda

  0  Salir
```

---

## Formato del CSV

El archivo CSV debe tener **exactamente 7 columnas** en este orden, con cabecera en la primera fila:

```
Nombre,CodigoBarra,Categoria,FechaCaducidad,Marca,Precio,Stock
Leche Entera,7501055300494,Lácteos,2026-06-01,Lala,18.50,120
Pan Integral,7501000560041,Panadería,2026-04-15,Bimbo,22.00,80
```

- `FechaCaducidad` debe tener formato `YYYY-MM-DD`
- `Precio` puede ser decimal (punto como separador)
- `Stock` debe ser entero no negativo
- Los campos con comas deben ir entre comillas dobles

Los registros inválidos se omiten y se registran en `errors.log`.

---

## Generar Visualizaciones DOT

Desde el menú, elige la opción **11**. Se generarán archivos `.dot` para cada árbol. Para convertirlos a imagen:

```bash
dot -Tpng arbolAVL.dot -o arbolAVL.png
dot -Tpng arbolB.dot   -o arbolB.png
dot -Tpng arbolBMas.dot -o arbolBMas.png
```

---

## Notas

- La lista enlazada implementa **búsqueda secuencial** (sin ordenamiento) para comparativas de rendimiento con el AVL.
- El árbol B usa grado mínimo `t=3` (máximo 5 claves por nodo, mínimo 2).
- El árbol B+ mantiene hojas doblemente enlazadas para recorrido eficiente por categoría.
- Los tiempos de búsqueda se miden en microsegundos con `std::chrono::high_resolution_clock`.
