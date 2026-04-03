// ═══════════════════════════════════════════════════════════════════
//  main.cpp  —  Catálogo de Productos · Supermercado EDD 2026
//  Menú con colores ANSI, preview de árboles en consola y export DOT
// ═══════════════════════════════════════════════════════════════════

#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <limits>

#include "clases/productos/Producto.h"
#include "estructuras/arbol-avl/ArbolAvl.h"
#include "estructuras/arbol-b/ArbolB.h"
#include "estructuras/arbol-b+/ArbolBMas.h"
#include "estructuras/lista-enlazada/ListaEnlazada.h"
#include "leer-archivos/CargarCSV.h"

using namespace std;
using namespace std::chrono;


namespace C {
    // Estilos
    const string RESET   = "\033[0m";
    const string BOLD    = "\033[1m";
    const string DIM     = "\033[2m";
    const string ITALIC  = "\033[3m";

    // Colores de texto
    const string NEGRO   = "\033[30m";
    const string ROJO    = "\033[31m";
    const string VERDE   = "\033[32m";
    const string AMARILLO= "\033[33m";
    const string AZUL    = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN    = "\033[36m";
    const string BLANCO  = "\033[37m";

    // Colores brillantes
    const string ROJO_B  = "\033[91m";
    const string VERDE_B = "\033[92m";
    const string AMAR_B  = "\033[93m";
    const string AZUL_B  = "\033[94m";
    const string MAG_B   = "\033[95m";
    const string CYAN_B  = "\033[96m";
    const string BLANC_B = "\033[97m";

    // Fondos
    const string BG_AZUL   = "\033[44m";
    const string BG_VERDE  = "\033[42m";
    const string BG_NEGRO  = "\033[40m";
    const string BG_CYAN   = "\033[46m";
}


static long long ahora_us() {
    return duration_cast<microseconds>(
        high_resolution_clock::now().time_since_epoch()
    ).count();
}


void limpiarPantalla() {
    cout << "\033[2J\033[H";
}

// Pausa hasta que el usuario presione ENTER
void pausar() {
    cout << "\n" << C::DIM << "  Presiona ENTER para continuar..." << C::RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Separador decorativo con color
void separador(const string &color = C::AZUL) {
    cout << color
         << "  ──────────────────────────────────────────────────\n"
         << C::RESET;
}

// Imprime un encabezado de sección
void titulo(const string &texto, const string &color = C::CYAN_B) {
    cout << "\n" << color << C::BOLD
         << "  ▌ " << texto
         << C::RESET << "\n";
    separador(color);
}

// Imprime resultado de tiempo de búsqueda
void mostrarTiempo(long long us) {
    string etiq;
    string col;
    if (us < 10)  { etiq = "ultra-rápido"; col = C::VERDE_B; }
    else if (us < 100) { etiq = "rápido";  col = C::VERDE; }
    else if (us < 1000){ etiq = "normal";  col = C::AMARILLO; }
    else               { etiq = "lento";   col = C::ROJO; }
    cout << C::DIM << "  ⏱  " << C::RESET
         << col << us << " µs" << C::RESET
         << C::DIM << " (" << etiq << ")" << C::RESET << "\n";
}


void mostrarBanner() {
    cout << "\n";
    cout << C::CYAN_B << C::BOLD;
    cout << "  ╔══════════════════════════════════════════════════╗\n";
    cout << "  ║                                                  ║\n";
    cout << "  ║     CATÁLOGO DE PRODUCTOS · SUPERMERCADO         ║\n";
    cout << "  ║         Estructuras de Datos  —  EDD 2026        ║\n";
    cout << "  ║                                                  ║\n";
    cout << "  ╚══════════════════════════════════════════════════╝\n";
    cout << C::RESET << "\n";

    cout << "  " << C::DIM << "Estructuras activas: " << C::RESET;
    cout << C::VERDE_B << "● AVL" << C::RESET << C::DIM << "(nombre)  ";
    cout << C::RESET << C::AZUL_B  << "● Árbol B" << C::RESET << C::DIM << "(fecha)  ";
    cout << C::RESET << C::MAG_B   << "● Árbol B+" << C::RESET << C::DIM << "(categoría)  ";
    cout << C::RESET << C::AMAR_B  << "● Lista" << C::RESET << C::DIM << "(secuencial)  ";
    cout << C::RESET << C::CYAN_B  << "● Lista Ord." << C::RESET << C::DIM << "(ordenada)\n";
    cout << C::RESET;
}


void mostrarMenu(int productosTotal) {
    mostrarBanner();

    cout << "  " << C::DIM << "Productos cargados: " << C::RESET
         << C::VERDE_B << C::BOLD << productosTotal << C::RESET << "\n\n";

    // Grupo 1 — Carga
    cout << "  " << C::AMAR_B << C::BOLD << "DATOS" << C::RESET << "\n";
    cout << "  " << C::AMAR_B << "  1" << C::RESET << "  Cargar catálogo desde CSV\n";
    cout << "  " << C::AMAR_B << "  2" << C::RESET << "  Agregar producto manualmente\n";
    cout << "  " << C::AMAR_B << "  3" << C::RESET << "  Eliminar producto\n";
    cout << "\n";

    // Grupo 2 — Búsquedas
    cout << "  " << C::CYAN_B << C::BOLD << "BÚSQUEDA" << C::RESET << "\n";
    cout << "  " << C::CYAN_B << "  4" << C::RESET
         << "  Por nombre        " << C::DIM << "→ AVL  O(log n)\n" << C::RESET;
    cout << "  " << C::CYAN_B << "  5" << C::RESET
         << "  Por categoría     " << C::DIM << "→ Árbol B+  O(log n + k)\n" << C::RESET;
    cout << "  " << C::CYAN_B << "  6" << C::RESET
         << "  Por rango de fecha" << C::DIM << "→ Árbol B  O(log n + k)\n" << C::RESET;
    cout << "\n";

    // Grupo 3 — Listados
    cout << "  " << C::VERDE_B << C::BOLD << "LISTADOS" << C::RESET << "\n";
    cout << "  " << C::VERDE_B << "  7" << C::RESET << "  Listar por nombre   (AVL in-order)\n";
    cout << "  " << C::VERDE_B << "  8" << C::RESET << "  Listar por fecha    (Árbol B in-order)\n";
    cout << "  " << C::VERDE_B << "  9" << C::RESET << "  Listar por categoría(Árbol B+ hojas)\n";
    cout << "\n";

    // Grupo 4 — Herramientas
    cout << "  " << C::MAG_B << C::BOLD << "HERRAMIENTAS" << C::RESET << "\n";
    cout << "  " << C::MAG_B << " 10" << C::RESET << "  Preview árbol en consola\n";
    cout << "  " << C::MAG_B << " 11" << C::RESET << "  Generar archivos DOT (.dot / .png)\n";
    cout << "  " << C::MAG_B << " 12" << C::RESET << "  Comparar tiempos de búsqueda\n";
    cout << "\n";

    cout << "  " << C::ROJO_B << "  0" << C::RESET << "  Salir\n";
    cout << "\n";
    cout << "  " << C::BLANC_B << "Opción: " << C::RESET;
}


Producto leerProducto() {
    string nombre, codigo, categoria, fecha, marca;
    double precio = 0;
    int    stock  = 0;

    auto campo = [](const string &etiq) {
        cout << "  " << C::CYAN << etiq << C::RESET << ": ";
    };

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    campo("Nombre        "); getline(cin, nombre);
    campo("Código barra  "); getline(cin, codigo);
    campo("Categoría     "); getline(cin, categoria);
    campo("Fecha (YYYY-MM-DD)"); getline(cin, fecha);
    campo("Marca         "); getline(cin, marca);
    campo("Precio        "); cin >> precio;
    campo("Stock         "); cin >> stock;

    return Producto(nombre, codigo, categoria, fecha, marca, precio, stock);
}


void imprimirProducto(const Producto *p, int idx = -1) {
    if (!p) return;
    if (idx >= 0)
        cout << "  " << C::DIM << "[" << idx << "] " << C::RESET;

    cout << C::BLANC_B << C::BOLD << p->getNombre() << C::RESET
         << C::DIM << "  (" << p->getCategoria() << ")" << C::RESET << "\n";

    cout << "  " << C::DIM << "Código   : " << C::RESET << p->getCodigo()         << "\n";
    cout << "  " << C::DIM << "Marca    : " << C::RESET << p->getMarca()           << "\n";
    cout << "  " << C::DIM << "Caduca   : " << C::RESET << p->getFechaCaducidad()  << "\n";
    cout << "  " << C::DIM << "Precio   : " << C::RESET
         << C::VERDE_B << "Q" << fixed << setprecision(2) << p->getPrecio() << C::RESET << "\n";
    cout << "  " << C::DIM << "Stock    : " << C::RESET << p->getCantidad() << " unidades\n";
}


void imprimirAVL_helper(NodoAvl *nodo, const string &prefix, bool esIzq) {
    if (!nodo) return;

    imprimirAVL_helper(nodo->getDerecha(),
                       prefix + (esIzq ? "│   " : "    "), false);

    string nom = nodo->getProducto().getNombre();
    if (nom.size() > 15) nom = nom.substr(0, 14) + "~";

    string conector = esIzq ? "└── " : "┌── ";
    string color    = (!nodo->getIzquierda() && !nodo->getDerecha())
                      ? C::VERDE
                      : C::AZUL_B;

    cout << prefix << C::DIM << conector << C::RESET
         << color << "[" << nom << "]" << C::RESET
         << C::DIM << " h=" << nodo->getAltura() << C::RESET << "\n";

    imprimirAVL_helper(nodo->getIzquierda(),
                       prefix + (esIzq ? "    " : "│   "), true);
}

void previewAVL(ArbolAvl &avl) {
    titulo("ÁRBOL AVL  —  Vista en consola (rotado 90°, derecha = arriba)", C::VERDE_B);
    cout << "  " << C::DIM << "● hojas en " << C::RESET
         << C::VERDE << "verde" << C::RESET
         << C::DIM << "  ● internos en " << C::RESET
         << C::AZUL_B << "azul" << C::RESET << "\n\n";

    NodoAvl *raiz = avl.getRaiz();
    if (!raiz) {
        cout << "  " << C::ROJO << "(árbol vacío)" << C::RESET << "\n";
        return;
    }
    imprimirAVL_helper(raiz, "  ", true);

    cout << "\n  " << C::DIM << "Raíz: " << C::RESET
         << C::BLANC_B << raiz->getProducto().getNombre() << C::RESET
         << C::DIM << "  |  Altura: " << C::RESET
         << C::AMAR_B << raiz->getAltura() << C::RESET << "\n";
}


#include <queue>
#include <vector>

void previewArbolB(ArbolB &arbolB) {
    titulo("ÁRBOL B  —  Vista en consola (nivel por nivel)", C::AZUL_B);
    cout << "  " << C::DIM << "(H) = hoja  |  Clave = fecha de caducidad\n\n" << C::RESET;

    NodoB *raiz = arbolB.getRaiz();
    if (!raiz) {
        cout << "  " << C::ROJO << "(árbol vacío)" << C::RESET << "\n";
        return;
    }

    struct Entry { NodoB *n; int lv; };
    queue<Entry> cola;
    cola.push({raiz, 0});
    int nivelActual = -1;
    vector<string> fila;

    auto flushFila = [&]() {
        if (fila.empty()) return;
        cout << "  " << C::DIM << "Nv " << nivelActual << "  " << C::RESET;
        for (auto &s : fila) cout << s << "  ";
        cout << "\n";
        fila.clear();
    };

    while (!cola.empty()) {
        auto [n, lv] = cola.front(); cola.pop();
        if (lv != nivelActual) { flushFila(); nivelActual = lv; }

        string rep;
        bool esHoja = n->hoja();
        rep += esHoja ? C::VERDE : C::AZUL_B;
        rep += "[";
        int cnt = n->getCantidadClaves();
        for (int i = 0; i < cnt; i++) {
            Producto *p = n->getClave(i);
            string fecha = p->getFechaCaducidad();
            if (fecha.size() > 10) fecha = fecha.substr(0, 10);
            rep += fecha;
            if (i < cnt - 1) rep += "│";
        }
        rep += esHoja ? "](H)" : "]";
        rep += C::RESET;

        fila.push_back(rep);

        if (!esHoja) {
            for (int i = 0; i <= cnt; i++) {
                if (n->getHijo(i)) cola.push({n->getHijo(i), lv + 1});
            }
        }
    }
    flushFila();
}


void previewArbolBMas(ArbolBMas &arbolBMas) {
    titulo("ÁRBOL B+  —  Vista en consola (nivel por nivel)", C::MAG_B);
    cout << "  " << C::DIM << "(I) = interno  (H) = hoja enlazada\n\n" << C::RESET;
    arbolBMas.mostrarArbol();
}


void compararTiempos(ArbolAvl &avl,
                     ListaEnlazada &lista,
                     ListaEnlazada &listaOrdenada,
                     const string &nombre) {
    const int N = 20, M = 5;

    titulo("COMPARACIÓN DE TIEMPOS DE BÚSQUEDA", C::MAG_B);
    cout << "  " << C::DIM << "Buscando: " << C::RESET
         << C::BLANC_B << "\"" << nombre << "\"" << C::RESET
         << C::DIM << "  |  N=" << N << " repeticiones × M=" << M << " series\n\n" << C::RESET;

    // ── Lista desordenada
    long long totL = 0;
    for (int m = 0; m < M; m++) {
        long long t0 = ahora_us();
        for (int i = 0; i < N; i++) lista.buscar(nombre);
        totL += ahora_us() - t0;
    }
    double promL = (double)totL / (M * N);

    // ── Lista ordenada
    long long totLO = 0;
    for (int m = 0; m < M; m++) {
        long long t0 = ahora_us();
        for (int i = 0; i < N; i++) listaOrdenada.buscarOrdenado(nombre);
        totLO += ahora_us() - t0;
    }
    double promLO = (double)totLO / (M * N);

    // ── AVL
    long long totA = 0;
    for (int m = 0; m < M; m++) {
        long long t0 = ahora_us();
        for (int i = 0; i < N; i++) avl.buscar(nombre);
        totA += ahora_us() - t0;
    }
    double promA = (double)totA / (M * N);

    // ── Tabla de resultados
    cout << "  " << C::DIM
         << "┌─────────────────────────────┬───────────────┬───────────────────┐\n"
         << "  │  Estructura                 │  Prom. (µs)   │  Complejidad      │\n"
         << "  ├─────────────────────────────┼───────────────┼───────────────────┤\n"
         << C::RESET;

    auto fila = [&](const string &etiq, double val, const string &o, const string &col){
        cout << "  │  " << col << left << setw(27) << etiq << C::RESET
             << C::DIM << "│  " << C::RESET
             << col << setw(13) << fixed << setprecision(2) << val << C::RESET
             << C::DIM << "│  " << C::RESET
             << C::DIM << left << setw(19) << o << C::RESET
             << C::DIM << "│\n" << C::RESET;
    };

    fila("Lista desordenada",  promL,  "O(n)",        C::AMAR_B);
    fila("Lista ordenada",     promLO, "O(n/2) prom", C::CYAN_B);
    fila("Árbol AVL",          promA,  "O(log n)",    C::VERDE_B);

    cout << "  " << C::DIM
         << "└─────────────────────────────┴───────────────┴───────────────────┘\n"
         << C::RESET;

    // ── Speedups ──────────────────────────────────────────────
    cout << "\n";
    if (promA > 0) {
        cout << "  " << C::VERDE_B << C::BOLD
             << "Speedup AVL vs Lista desordenada : "
             << fixed << setprecision(1) << promL / promA << "×" << C::RESET << "\n";
        cout << "  " << C::VERDE_B << C::BOLD
             << "Speedup AVL vs Lista ordenada    : "
             << fixed << setprecision(1) << promLO / promA << "×" << C::RESET << "\n";
    }
    if (promLO > 0) {
        cout << "  " << C::CYAN_B << C::BOLD
             << "Speedup Lista ord. vs desordenada: "
             << fixed << setprecision(1) << promL / promLO << "×" << C::RESET << "\n";
    }
}


void generarDots(ArbolB &arbolB, ArbolBMas &arbolBMas, ArbolAvl &avl) {
    titulo("GENERANDO ARCHIVOS DOT", C::MAG_B);

    auto generar = [](const string &dot, const string &png, auto lambda) {
        cout << "  " << C::DIM << "→ " << C::RESET << dot << " ... ";
        lambda();
        cout << C::VERDE_B << "✓" << C::RESET << "\n";

        string cmd = "dot -Tpng " + dot + " -o " + png + " 2>/dev/null";
        int ret = system(cmd.c_str());
        if (ret == 0)
            cout << "    " << C::VERDE << "PNG generado: " << png << C::RESET << "\n";
        else
            cout << "    " << C::DIM
                 << "  (instala Graphviz para auto-convertir: "
                 << "dot -Tpng " << dot << " -o " << png << ")"
                 << C::RESET << "\n";
    };

    generar("arbolAVL.dot", "arbolAVL.png",
            [&]{ avl.generarDOT("arbolAVL.dot"); });

    generar("arbolB.dot", "arbolB.png",
            [&]{ arbolB.generarDOT("arbolB.dot"); });

    generar("arbolBMas.dot", "arbolBMas.png",
            [&]{ arbolBMas.generarDOT("arbolBMas.dot"); });
}


void menuPreview(ArbolAvl &avl, ArbolB &arbolB, ArbolBMas &arbolBMas) {
    int op;
    do {
        limpiarPantalla();
        cout << "\n";
        cout << C::MAG_B << C::BOLD
             << "  ╔══════════════════════════════════╗\n"
             << "  ║   PREVIEW ÁRBOLES EN CONSOLA     ║\n"
             << "  ╚══════════════════════════════════╝\n"
             << C::RESET << "\n";

        cout << "  " << C::MAG_B << "1" << C::RESET << "  Árbol AVL         (por nombre)\n";
        cout << "  " << C::MAG_B << "2" << C::RESET << "  Árbol B           (por fecha)\n";
        cout << "  " << C::MAG_B << "3" << C::RESET << "  Árbol B+          (por categoría)\n";
        cout << "  " << C::MAG_B << "4" << C::RESET << "  Ver los 3 árboles seguidos\n";
        cout << "  " << C::ROJO  << "0" << C::RESET << "  Volver al menú principal\n";
        cout << "\n  Opción: ";
        cin >> op;

        limpiarPantalla();
        if (op == 1 || op == 4) { previewAVL(avl);          if(op==4) pausar(); }
        if (op == 2 || op == 4) { previewArbolB(arbolB);    if(op==4) pausar(); }
        if (op == 3 || op == 4) { previewArbolBMas(arbolBMas); }

        if (op >= 1 && op <= 4) pausar();

    } while (op != 0);
}


bool insertarEnTodo(const Producto &p,
                    ArbolAvl &avl, ArbolB &arbolB,
                    ArbolBMas &arbolBMas,
                    ListaEnlazada &lista,
                    ListaEnlazada &listaOrdenada,
                    int &total) {
    avl.insert(p);
    arbolB.insertar(p);
    arbolBMas.insertar(p);
    lista.insert(p);                  // lista desordenada
    listaOrdenada.insertOrdenado(p);  // lista ordenada
    total++;
    return true;
}



void eliminarDeTodo(const string &nombre, const string &fecha,
                    const string &categoria, const string &codigo,
                    ArbolAvl &avl, ArbolB &arbolB,
                    ArbolBMas &arbolBMas,
                    ListaEnlazada &lista,
                    ListaEnlazada &listaOrdenada,
                    int &total) {
    avl.eliminar(nombre);
    arbolB.eliminar(fecha);
    arbolBMas.eliminar(categoria, codigo);
    lista.eliminar(codigo);              // desordenada: elimina por código
    listaOrdenada.eliminarOrdenado(nombre); // ordenada: elimina por nombre con corte
    total--;
}


int main() {
    // ── Estructuras principales
    ArbolB        arbolB(3);          // grado mínimo t=3
    ArbolBMas     arbolBMas(3);
    ArbolAvl      avl;
    ListaEnlazada lista;              // lista desordenada
    ListaEnlazada listaOrdenada;      // lista ordenada alfabéticamente
    int           totalProductos = 0;

    int opcion;

    do {
        limpiarPantalla();
        mostrarMenu(totalProductos);
        cin >> opcion;

        limpiarPantalla();

        switch (opcion) {


        case 1: {
            titulo("CARGAR CATÁLOGO DESDE CSV", C::AMAR_B);
            string ruta;
            cout << "  " << C::CYAN << "Ruta del archivo CSV: " << C::RESET;
            cin >> ruta;

            cout << "\n  " << C::DIM << "Cargando..." << C::RESET << "\n\n";
            long long t0 = ahora_us();
            CargarCSV cargador(ruta, "errors.log");
            int n = cargador.cargar(&arbolB, &avl, &arbolBMas, &lista);
            long long dt = ahora_us() - t0;
            totalProductos += n;

            if (n > 0) {
                cout << "  " << C::DIM << "Construyendo lista ordenada..." << C::RESET << "\n";
                // Recorremos la lista desordenada e insertamos en la ordenada

                cout << "  " << C::VERDE_B << C::BOLD << "✓ " << n
                     << " productos cargados" << C::RESET
                     << C::DIM << " en " << dt/1000 << " ms" << C::RESET << "\n";
                if (n < totalProductos)
                    cout << "  " << C::AMARILLO
                         << "⚠  Algunos registros omitidos. Revisa errors.log"
                         << C::RESET << "\n";
            } else {
                cout << "  " << C::ROJO_B
                     << "✗ No se cargaron productos. Verifica la ruta y el formato."
                     << C::RESET << "\n";
            }
            pausar();
            break;
        }


        case 2: {
            titulo("AGREGAR PRODUCTO", C::AMAR_B);
            Producto p = leerProducto();
            if (insertarEnTodo(p, avl, arbolB, arbolBMas,
                               lista, listaOrdenada, totalProductos)) {
                cout << "\n  " << C::VERDE_B
                     << "✓ Producto insertado en todas las estructuras "
                     << C::DIM << "(incluye lista ordenada)" << C::RESET << "\n";
            }
            pausar();
            break;
        }

        case 3: {
            titulo("ELIMINAR PRODUCTO", C::ROJO_B);
            string nom, fecha, cat, cod;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  " << C::CYAN << "Nombre exacto  : " << C::RESET; getline(cin, nom);
            cout << "  " << C::CYAN << "Fecha caducidad: " << C::RESET; getline(cin, fecha);
            cout << "  " << C::CYAN << "Categoría      : " << C::RESET; getline(cin, cat);
            cout << "  " << C::CYAN << "Código barra   : " << C::RESET; getline(cin, cod);

            eliminarDeTodo(nom, fecha, cat, cod,
                           avl, arbolB, arbolBMas,
                           lista, listaOrdenada, totalProductos);
            cout << "\n  " << C::VERDE_B
                 << "✓ Producto eliminado de todas las estructuras."
                 << C::RESET << "\n";
            pausar();
            break;
        }


        case 4: {
            titulo("BUSCAR POR NOMBRE  →  Árbol AVL", C::CYAN_B);
            string nombre;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  " << C::CYAN << "Nombre: " << C::RESET;
            getline(cin, nombre);

            long long t0 = ahora_us();
            Producto *p = avl.buscar(nombre);
            long long dt = ahora_us() - t0;

            if (p) {
                cout << "\n";
                imprimirProducto(p);
                cout << "\n";
                mostrarTiempo(dt);
            } else {
                cout << "\n  " << C::ROJO << "✗ No se encontró \""
                     << nombre << "\"" << C::RESET << "\n";
            }
            pausar();
            break;
        }


        case 5: {
            titulo("BUSCAR POR CATEGORÍA  →  Árbol B+", C::MAG_B);
            string cat;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  " << C::CYAN << "Categoría: " << C::RESET;
            getline(cin, cat);

            long long t0 = ahora_us();
            arbolBMas.buscarCategoria(cat);
            long long dt = ahora_us() - t0;

            mostrarTiempo(dt);
            pausar();
            break;
        }


        case 6: {
            titulo("BUSCAR POR RANGO DE FECHA  →  Árbol B", C::AZUL_B);
            string fi, ff;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  " << C::CYAN << "Fecha inicio (YYYY-MM-DD): " << C::RESET;
            getline(cin, fi);
            cout << "  " << C::CYAN << "Fecha fin    (YYYY-MM-DD): " << C::RESET;
            getline(cin, ff);

            long long t0 = ahora_us();
            arbolB.buscarRangoFecha(fi, ff);
            long long dt = ahora_us() - t0;

            mostrarTiempo(dt);
            pausar();
            break;
        }


        case 7:
            titulo("LISTAR POR NOMBRE  →  AVL in-order", C::VERDE_B);
            avl.imprimir();
            pausar();
            break;


        case 8:
            titulo("LISTAR POR FECHA  →  Árbol B in-order", C::AZUL_B);
            arbolB.imprimirOrdenado();
            pausar();
            break;


        case 9:
            titulo("LISTAR POR CATEGORÍA  →  Árbol B+ (hojas)", C::MAG_B);
            arbolBMas.imprimirOrdenado();
            pausar();
            break;

        case 10:
            menuPreview(avl, arbolB, arbolBMas);
            break;


        case 11:
            generarDots(arbolB, arbolBMas, avl);
            pausar();
            break;


        case 12: {
            titulo("COMPARAR TIEMPOS DE BÚSQUEDA", C::MAG_B);
            string nombre;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  " << C::CYAN << "Nombre a buscar: " << C::RESET;
            getline(cin, nombre);
            // Ahora pasa también la lista ordenada
            compararTiempos(avl, lista, listaOrdenada, nombre);
            pausar();
            break;
        }


        case 0:
            limpiarPantalla();
            cout << "\n\n  " << C::CYAN_B << C::BOLD
                 << "¡Hasta pronto! " << C::RESET << "\n";
            cout << "  " << C::DIM << "Productos gestionados en esta sesión: "
                 << totalProductos << C::RESET << "\n\n";
            break;

        default:
            cout << "\n  " << C::ROJO << "✗ Opción inválida." << C::RESET << "\n";
            pausar();
        }

    } while (opcion != 0);

    return 0;
}
