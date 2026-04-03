//
// Created by alejandro on 30/3/26.
//

#include "ArbolBMas.h"
#include <iomanip>
#include <queue>
#include <vector>
#include <string>
using namespace std;


ArbolBMas::ArbolBMas() {
    orden       = 3;
    raiz        = nullptr;
    primeraHoja = nullptr;
}

ArbolBMas::ArbolBMas(int orden) {
    this->orden = orden;
    raiz        = nullptr;
    primeraHoja = nullptr;
}

ArbolBMas::~ArbolBMas() {
    liberarNodo(raiz);
}

void ArbolBMas::liberarNodo(NodoBMas *nodo) {
    if (nodo == nullptr) return;
    if (!nodo->getEsHoja()) {
        for (int i = 0; i <= nodo->getNumClaves(); i++)
            liberarNodo(nodo->getHijo(i));
    }
    delete nodo;
}



void ArbolBMas::insertar(const Producto &p) {
    const string &cat = p.getCategoria();

    if (raiz == nullptr) {
        raiz = new NodoBMas(orden, true);
        raiz->setClave(0, cat);
        raiz->setProducto(0, p);
        raiz->incrementarCLaves();
        primeraHoja = raiz;
        return;
    }

    if (raiz->lleno()) {
        NodoBMas *nuevaRaiz = new NodoBMas(orden, false);
        nuevaRaiz->setHijo(0, raiz);

        if (raiz->getEsHoja())
            dividirHojaHijo(nuevaRaiz, 0, raiz);
        else
            dividirHijo(nuevaRaiz, 0, raiz);

        int i = (nuevaRaiz->getClave(0) <= cat) ? 1 : 0;
        insertarEnNodo(nuevaRaiz->getHijo(i), cat, p);
        raiz = nuevaRaiz;
    } else {
        insertarEnNodo(raiz, cat, p);
    }
}


void ArbolBMas::insertarEnNodo(NodoBMas *nodo, const string &categoria, const Producto &p) {
    int i = nodo->getNumClaves() - 1;

    if (nodo->getEsHoja()) {
        while (i >= 0 && nodo->getClave(i) > categoria) {
            nodo->setClave(i + 1, nodo->getClave(i));
            nodo->setProducto(i + 1, nodo->getProducto(i));
            i--;
        }
        nodo->setClave(i + 1, categoria);
        nodo->setProducto(i + 1, p);
        nodo->incrementarCLaves();
    } else {
        while (i >= 0 && nodo->getClave(i) > categoria) i--;
        i++;

        NodoBMas *hijo = nodo->getHijo(i);

        if (hijo->lleno()) {
            // Dividir antes de bajar
            if (hijo->getEsHoja())
                dividirHojaHijo(nodo, i, hijo);
            else
                dividirHijo(nodo, i, hijo);

            // Reelegir hijo
            if (nodo->getClave(i) <= categoria) i++;
        }
        insertarEnNodo(nodo->getHijo(i), categoria, p);
    }
}


void ArbolBMas::dividirHojaHijo(NodoBMas *padre, int indice, NodoBMas *hijo) {
    int t = orden;

    NodoBMas *nuevaHoja = new NodoBMas(t, true);

    // Copiar la mitad derecha al nuevo nodo hoja
    int desde = t;
    int cant   = hijo->getNumClaves() - desde;

    for (int j = 0; j < cant; j++) {
        nuevaHoja->setClave(j, hijo->getClave(desde + j));
        nuevaHoja->setProducto(j, hijo->getProducto(desde + j));
        nuevaHoja->incrementarCLaves();
    }
    // Reducir el hijo original
    for (int j = 0; j < cant; j++) hijo->decrementarCLaves();

    nuevaHoja->setSiguiente(hijo->getSiguiente());
    if (hijo->getSiguiente() != nullptr)
        hijo->getSiguiente()->setAnterior(nuevaHoja);
    hijo->setSiguiente(nuevaHoja);
    nuevaHoja->setAnterior(hijo);

    for (int j = padre->getNumClaves() - 1; j >= indice; j--) {
        padre->setClave(j + 1, padre->getClave(j));
        padre->setHijo(j + 2, padre->getHijo(j + 1));
    }
    padre->setClave(indice, nuevaHoja->getClave(0));
    padre->setHijo(indice + 1, nuevaHoja);
    padre->incrementarCLaves();
}


void ArbolBMas::dividirHijo(NodoBMas *padre, int indice, NodoBMas *hijo) {
    int t = orden;

    NodoBMas *nuevoNodo = new NodoBMas(t, false);

    for (int j = 0; j < t - 1; j++) {
        nuevoNodo->setClave(j, hijo->getClave(j + t));
        nuevoNodo->incrementarCLaves();
    }
    // Copiar hijos
    for (int j = 0; j < t; j++)
        nuevoNodo->setHijo(j, hijo->getHijo(j + t));

    // Reducir hijo
    string mediana = hijo->getClave(t - 1);
    int cantOriginal = hijo->getNumClaves();
    for (int j = 0; j < cantOriginal - (t - 1); j++) hijo->decrementarCLaves();
    while (hijo->getNumClaves() > t - 1) hijo->decrementarCLaves();

    // Insertar nuevoNodo en el padre
    for (int j = padre->getNumClaves() - 1; j >= indice; j--) {
        padre->setClave(j + 1, padre->getClave(j));
        padre->setHijo(j + 2, padre->getHijo(j + 1));
    }
    padre->setClave(indice, mediana);
    padre->setHijo(indice + 1, nuevoNodo);
    padre->incrementarCLaves();
}



void ArbolBMas::buscarCategoria(const string &categoria) const {
    if (raiz == nullptr) {
        cout << "El arbol B+ esta vacio." << endl;
        return;
    }

    NodoBMas *actual = raiz;
    while (!actual->getEsHoja()) {
        int i = 0;
        while (i < actual->getNumClaves() && actual->getClave(i) <= categoria)
            i++;
        int idx = 0;
        while (idx < actual->getNumClaves() && actual->getClave(idx) < categoria)
            idx++;
        actual = actual->getHijo(idx);
    }

    bool encontrado = false;
    cout << "\n=== Productos en categoria: " << categoria << " ===\n";

    while (actual != nullptr) {
        for (int i = 0; i < actual->getNumClaves(); i++) {
            if (actual->getClave(i) == categoria) {
                Producto pr = actual->getProducto(i);
                cout << "  Nombre  : " << pr.getNombre()        << "\n";
                cout << "  Codigo  : " << pr.getCodigo()        << "\n";
                cout << "  Marca   : " << pr.getMarca()         << "\n";
                cout << "  Caducidad: " << pr.getFechaCaducidad()<< "\n";
                cout << "  Precio  : Q" << pr.getPrecio()       << "\n";
                cout << "  Stock   : " << pr.getCantidad()      << "\n";
                cout << "  ---------------------------------\n";
                encontrado = true;
            } else if (actual->getClave(i) > categoria) {

                goto fin_busqueda;
            }
        }
        actual = actual->getSiguiente();
    }

    fin_busqueda:
    if (!encontrado)
        cout << "  No se encontraron productos en esa categoria.\n";
    cout << "=================================================\n\n";
}


void ArbolBMas::imprimirOrdenado() const {
    if (primeraHoja == nullptr) {
        cout << "El arbol B+ esta vacio." << endl;
        return;
    }

    cout << "\n=== PRODUCTOS ORDENADOS POR CATEGORIA (B+) ===\n";
    NodoBMas *hoja = primeraHoja;
    while (hoja != nullptr) {
        for (int i = 0; i < hoja->getNumClaves(); i++) {
            Producto p = hoja->getProducto(i);
            cout << "[" << hoja->getClave(i) << "] "
                 << p.getNombre()
                 << " | Q" << p.getPrecio()
                 << " | Stock: " << p.getCantidad()
                 << "\n";
        }
        hoja = hoja->getSiguiente();
    }
    cout << "==============================================\n\n";
}


void ArbolBMas::mostrarArbol() const {
    if (raiz == nullptr) {
        cout << "El arbol B+ esta vacio." << endl;
        return;
    }

    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════╗\n";
    cout << "║          ÁRBOL B+  —  Preview en consola             ║\n";
    cout << "║   (I) = nodo interno   (H) = nodo hoja               ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n\n";

    struct Entry { NodoBMas *nodo; int nivel; };
    queue<Entry> cola;
    cola.push({raiz, 0});

    int nivelActual = 0;
    cout << "  Nivel 0 (raíz): ";

    while (!cola.empty()) {
        Entry e = cola.front(); cola.pop();
        NodoBMas *n = e.nodo;
        int niv = e.nivel;

        if (niv > nivelActual) {
            nivelActual = niv;
            cout << "\n  Nivel " << nivelActual << ": ";
        }

        if (n->getEsHoja()) {
            cout << "(H)[";
        } else {
            cout << "(I)[";
        }
        for (int i = 0; i < n->getNumClaves(); i++) {

            string cat = n->getClave(i);
            if (cat.size() > 10) cat = cat.substr(0, 9) + "~";
            cout << cat;
            if (i < n->getNumClaves() - 1) cout << " | ";
        }
        cout << "]  ";


        if (!n->getEsHoja()) {
            for (int i = 0; i <= n->getNumClaves(); i++) {
                if (n->getHijo(i) != nullptr)
                    cola.push({n->getHijo(i), niv + 1});
            }
        }
    }

    cout << "\n\n";


    cout << "  ┌─ Lista enlazada de hojas (izq → der) ─────────────\n";
    cout << "  │  ";
    NodoBMas *hoja = primeraHoja;
    bool primero = true;
    while (hoja != nullptr) {
        if (!primero) cout << " ↔ ";
        cout << "[";
        for (int i = 0; i < hoja->getNumClaves(); i++) {
            string cat = hoja->getClave(i);
            if (cat.size() > 8) cat = cat.substr(0, 7) + "~";
            cout << cat;
            if (i < hoja->getNumClaves() - 1) cout << ",";
        }
        cout << "]";
        primero = false;
        hoja = hoja->getSiguiente();
    }
    cout << "\n  └────────────────────────────────────────────────────\n\n";
}



void ArbolBMas::generarDOT(const string &nombreArchivo) {
    fstream archivo;
    archivo.open(nombreArchivo, ios::out);

    if (!archivo.is_open()) {
        cout << "[ArbolBMas] Error: no se pudo crear el archivo " << nombreArchivo << endl;
        return;
    }

    archivo << "digraph BPlus {\n";
    archivo << "  graph [rankdir=TB, bgcolor=\"#ffffff\", nodesep=0.6, ranksep=1.0];\n";
    archivo << "  node  [shape=record, style=filled, fontname=\"Courier New\", fontsize=10];\n";
    archivo << "  edge  [color=\"#444444\", arrowsize=0.7];\n\n";

    if (raiz != nullptr) {
        int contadorHoja = 0;
        generarDotRecursivo(raiz, archivo, contadorHoja);

        archivo << "\n  // ── Lista enlazada de hojas ──\n";
        archivo << "  edge [style=dashed, color=\"#1565C0\", constraint=false];\n";
        NodoBMas *hoja = primeraHoja;
        while (hoja != nullptr && hoja->getSiguiente() != nullptr) {
            unsigned long long id1 = (unsigned long long)(void*)hoja;
            unsigned long long id2 = (unsigned long long)(void*)hoja->getSiguiente();
            archivo << "  n" << id1 << " -> n" << id2 << " [label=\"next\"];\n";
            hoja = hoja->getSiguiente();
        }
    }

    archivo << "}\n";
    archivo.close();

    cout << "[ArbolBMas] Archivo DOT generado: " << nombreArchivo << "\n";
    cout << "            Convertir con: dot -Tpng " << nombreArchivo << " -o arbolBMas.png\n";
}

void ArbolBMas::generarDotRecursivo(NodoBMas *nodo, fstream &archivo, int &contadorHoja) {
    if (nodo == nullptr) return;

    unsigned long long id = (unsigned long long)(void*)nodo;

    if (nodo->getEsHoja()) {
        archivo << "  n" << id << " [fillcolor=\"#E8F5E9\", color=\"#2E7D32\", label=\"{HOJA|";
        for (int i = 0; i < nodo->getNumClaves(); i++) {
            string cat  = nodo->getClave(i);
            string nom  = nodo->getProducto(i).getNombre();
            if (nom.size() > 14) nom = nom.substr(0, 13) + "~";
            for (char &c : cat) if (c == '"' || c == '<' || c == '>') c = '\'';
            for (char &c : nom) if (c == '"' || c == '<' || c == '>') c = '\'';
            archivo << cat << "\\n" << nom;
            if (i < nodo->getNumClaves() - 1) archivo << "|";
        }
        archivo << "}\"];\n";
        contadorHoja++;
    } else {
        archivo << "  n" << id << " [fillcolor=\"#E3F2FD\", color=\"#1565C0\", label=\"{";
        for (int i = 0; i < nodo->getNumClaves(); i++) {
            // Puerto izquierdo del hijo i
            archivo << "<f" << i << ">|";
            string cat = nodo->getClave(i);
            for (char &c : cat) if (c == '"' || c == '<' || c == '>') c = '\'';
            archivo << cat;
            if (i < nodo->getNumClaves() - 1) archivo << "|";
        }
        archivo << "|<f" << nodo->getNumClaves() << ">}\"];\n";

        // Recursión en hijos y aristas
        for (int i = 0; i <= nodo->getNumClaves(); i++) {
            NodoBMas *hijo = nodo->getHijo(i);
            if (hijo != nullptr) {
                unsigned long long idHijo = (unsigned long long)(void*)hijo;
                archivo << "  n" << id << ":f" << i << " -> n" << idHijo << ";\n";
                generarDotRecursivo(hijo, archivo, contadorHoja);
            }
        }
    }
}



void ArbolBMas::eliminar(const string &categoria, const string &codigoBarra) {
    if (raiz == nullptr) {
        cout << "[ArbolBMas] Arbol vacio, nada que eliminar.\n";
        return;
    }
    eliminarRecursivo(raiz, categoria, codigoBarra);

    if (raiz->getNumClaves() == 0 && !raiz->getEsHoja()) {
        NodoBMas *temp = raiz;
        raiz = raiz->getHijo(0);
        temp->setHijo(0, nullptr); // evitar doble liberación
        delete temp;
    }
}

void ArbolBMas::eliminarRecursivo(NodoBMas *nodo, const string &categoria, const string &codigoBarra) {
    int idx = 0;
    while (idx < nodo->getNumClaves() && nodo->getClave(idx) < categoria)
        idx++;

    if (nodo->getEsHoja()) {
        for (int i = 0; i < nodo->getNumClaves(); i++) {
            if (nodo->getClave(i) == categoria &&
                nodo->getProducto(i).getCodigo() == codigoBarra) {
                eliminarDeHoja(nodo, i);
                return;
            }
        }
        cout << "[ArbolBMas] Producto no encontrado en hoja.\n";
    } else {

        bool claveEnNodo = (idx < nodo->getNumClaves() && nodo->getClave(idx) == categoria);
        int hijoIdx = claveEnNodo ? idx : idx;

        int bajar = idx; // hijo idx cubre claves < clave[idx]

        NodoBMas *hijo = nodo->getHijo(bajar);
        if (hijo != nullptr && hijo->getNumClaves() < orden) {
            llenar(nodo, bajar);

            eliminarRecursivo(nodo, categoria, codigoBarra);
            return;
        }
        if (hijo != nullptr)
            eliminarRecursivo(hijo, categoria, codigoBarra);
    }
}

void ArbolBMas::eliminarDeHoja(NodoBMas *nodo, int idx) {
    for (int i = idx + 1; i < nodo->getNumClaves(); i++) {
        nodo->setClave(i - 1, nodo->getClave(i));
        nodo->setProducto(i - 1, nodo->getProducto(i));
    }
    nodo->decrementarCLaves();
}

void ArbolBMas::llenar(NodoBMas *nodo, int idx) {
    bool puedeIzq = (idx != 0 &&
                     nodo->getHijo(idx - 1)->getNumClaves() >= orden);
    bool puedeDer = (idx != nodo->getNumClaves() &&
                     nodo->getHijo(idx + 1)->getNumClaves() >= orden);

    if (puedeIzq)
        pedirPrestadoAnterior(nodo, idx);
    else if (puedeDer)
        pedirPrestadoSiguiente(nodo, idx);
    else {
        if (idx != nodo->getNumClaves())
            fusionar(nodo, idx);
        else
            fusionar(nodo, idx - 1);
    }
}

void ArbolBMas::pedirPrestadoAnterior(NodoBMas *nodo, int idx) {
    NodoBMas *hijo    = nodo->getHijo(idx);
    NodoBMas *hermano = nodo->getHijo(idx - 1);

    for (int i = hijo->getNumClaves() - 1; i >= 0; i--) {
        hijo->setClave(i + 1, hijo->getClave(i));
        hijo->setProducto(i + 1, hijo->getProducto(i));
    }
    if (!hijo->getEsHoja()) {
        for (int i = hijo->getNumClaves(); i >= 0; i--)
            hijo->setHijo(i + 1, hijo->getHijo(i));
    }

    hijo->setClave(0, nodo->getClave(idx - 1));
    if (hijo->getEsHoja())
        hijo->setProducto(0, hermano->getProducto(hermano->getNumClaves() - 1));
    else
        hijo->setHijo(0, hermano->getHijo(hermano->getNumClaves()));

    nodo->setClave(idx - 1, hermano->getClave(hermano->getNumClaves() - 1));

    hermano->decrementarCLaves();
    hijo->incrementarCLaves();
}

void ArbolBMas::pedirPrestadoSiguiente(NodoBMas *nodo, int idx) {
    NodoBMas *hijo    = nodo->getHijo(idx);
    NodoBMas *hermano = nodo->getHijo(idx + 1);

    hijo->setClave(hijo->getNumClaves(), nodo->getClave(idx));
    if (hijo->getEsHoja())
        hijo->setProducto(hijo->getNumClaves(), hermano->getProducto(0));
    else
        hijo->setHijo(hijo->getNumClaves() + 1, hermano->getHijo(0));

    nodo->setClave(idx, hermano->getClave(0));

    for (int i = 1; i < hermano->getNumClaves(); i++) {
        hermano->setClave(i - 1, hermano->getClave(i));
        hermano->setProducto(i - 1, hermano->getProducto(i));
    }
    if (!hermano->getEsHoja()) {
        for (int i = 1; i <= hermano->getNumClaves(); i++)
            hermano->setHijo(i - 1, hermano->getHijo(i));
    }

    hijo->incrementarCLaves();
    hermano->decrementarCLaves();
}

void ArbolBMas::fusionar(NodoBMas *nodo, int idx) {
    NodoBMas *hijo    = nodo->getHijo(idx);
    NodoBMas *hermano = nodo->getHijo(idx + 1);

    // Bajar clave del padre al hijo
    if (!hijo->getEsHoja()) {
        hijo->setClave(hijo->getNumClaves(), nodo->getClave(idx));
        hijo->incrementarCLaves();
    }

    for (int i = 0; i < hermano->getNumClaves(); i++) {
        hijo->setClave(hijo->getNumClaves(), hermano->getClave(i));
        hijo->setProducto(hijo->getNumClaves(), hermano->getProducto(i));
        hijo->incrementarCLaves();
    }
    if (!hijo->getEsHoja()) {
        for (int i = 0; i <= hermano->getNumClaves(); i++)
            hijo->setHijo(hijo->getNumClaves() - hermano->getNumClaves() + i,
                          hermano->getHijo(i));
    }

    // Actualizar lista enlazada de hojas
    if (hijo->getEsHoja()) {
        hijo->setSiguiente(hermano->getSiguiente());
        if (hermano->getSiguiente() != nullptr)
            hermano->getSiguiente()->setAnterior(hijo);
    }

    // Eliminar clave del padre y ajustar hijos
    for (int i = idx + 1; i < nodo->getNumClaves(); i++) {
        nodo->setClave(i - 1, nodo->getClave(i));
        nodo->setHijo(i, nodo->getHijo(i + 1));
    }
    nodo->decrementarCLaves();

    hermano->setNumClaves(0); // vaciar antes de delete
    delete hermano;
}