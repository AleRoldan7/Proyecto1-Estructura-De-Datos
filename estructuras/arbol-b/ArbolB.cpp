//
// Created by alejandro on 27/3/26.
//

#include "ArbolB.h"
#include <iostream>
#include <fstream>
#include <string>

#include "../../utils/date/ConvertDate.h"
using namespace std;

static int fechaAEntero(const string& fecha) {
    if (fecha.size() < 10) return 0;
    int anio = stoi(fecha.substr(0, 4));
    int mes  = stoi(fecha.substr(5, 2));
    int dia  = stoi(fecha.substr(8, 2));
    return anio * 10000 + mes * 100 + dia;
}



ArbolB::ArbolB() {
    raiz         = nullptr;
    gradoMinimo  = 3;          // grado por defecto
}

ArbolB::ArbolB(int gradoMinimo) {
    raiz              = nullptr;
    this->gradoMinimo = gradoMinimo;
}

ArbolB::~ArbolB() {
    liberarNodo(raiz);
}

void ArbolB::liberarNodo(NodoB* nodo) {
    if (nodo == nullptr) return;
    if (!nodo->hoja()) {
        for (int i = 0; i <= nodo->getCantidadClaves(); i++) {
            liberarNodo(nodo->getHijo(i));
        }
    }
    delete nodo;
}


void ArbolB::insertar(Producto producto) {
    if (raiz == nullptr) {
        raiz = new NodoB(gradoMinimo, true);
        raiz->setClave(0, producto);
        raiz->incrementClave();
        return;
    }

    int maxClaves = 2 * gradoMinimo - 1;
    if (raiz->getCantidadClaves() == maxClaves) {
        NodoB* nuevaRaiz = new NodoB(gradoMinimo, false);
        nuevaRaiz->setHijo(0, raiz);
        dividirHijo(nuevaRaiz, 0, raiz);

        // Decidir en cuál de los dos hijos insertar
        int i = 0;
        int claveFecha = fechaAEntero(producto.getFechaCaducidad());
        int hijoFecha  = fechaAEntero(nuevaRaiz->getClave(0)->getFechaCaducidad());
        if (hijoFecha < claveFecha) i = 1;

        insertarNodoLleno(nuevaRaiz->getHijo(i), producto);
        raiz = nuevaRaiz;
    } else {
        insertarNodoLleno(raiz, producto);
    }
}


void ArbolB::insertarNodoLleno(NodoB* nodo, Producto producto) {
    int i          = nodo->getCantidadClaves() - 1;
    int claveFecha = fechaAEntero(producto.getFechaCaducidad());
    int maxClaves  = 2 * gradoMinimo - 1;

    if (nodo->hoja()) {
        // Desplazar claves mayores hacia la derecha
        while (i >= 0 &&
               fechaAEntero(nodo->getClave(i)->getFechaCaducidad()) > claveFecha) {
            nodo->setClave(i + 1, *nodo->getClave(i));
            i--;
        }
        nodo->setClave(i + 1, producto);
        nodo->incrementClave();
    } else {
        // Encontrar el hijo correcto
        while (i >= 0 &&
               fechaAEntero(nodo->getClave(i)->getFechaCaducidad()) > claveFecha) {
            i--;
        }
        i++;  // índice del hijo destino

        // Si el hijo está lleno, dividirlo primero
        if (nodo->getHijo(i)->getCantidadClaves() == maxClaves) {
            dividirHijo(nodo, i, nodo->getHijo(i));
            if (fechaAEntero(nodo->getClave(i)->getFechaCaducidad()) < claveFecha) {
                i++;
            }
        }
        insertarNodoLleno(nodo->getHijo(i), producto);
    }
}


void ArbolB::dividirHijo(NodoB* padre, int indice, NodoB* hijoLleno) {
    int t = gradoMinimo;

    // Nuevo nodo que recibirá las claves de la mitad derecha
    NodoB* nuevoNodo = new NodoB(t, hijoLleno->hoja());
    nuevoNodo->setClave(0, *nuevoNodo->getClave(0)); // asegurar estado limpio

    for (int j = 0; j < t - 1; j++) {
        nuevoNodo->setClave(j, *hijoLleno->getClave(j + t));
        nuevoNodo->incrementClave();
    }

    if (!hijoLleno->hoja()) {
        for (int j = 0; j < t; j++) {
            nuevoNodo->setHijo(j, hijoLleno->getHijo(j + t));
        }
    }

    int cantOriginal = hijoLleno->getCantidadClaves();
    for (int j = 0; j < cantOriginal - (t - 1); j++) {
        hijoLleno->decrementClave();
    }
    while (hijoLleno->getCantidadClaves() > t - 1) hijoLleno->decrementClave();

    for (int j = padre->getCantidadClaves(); j >= indice + 1; j--) {
        padre->setHijo(j + 1, padre->getHijo(j));
    }
    padre->setHijo(indice + 1, nuevoNodo);

    for (int j = padre->getCantidadClaves() - 1; j >= indice; j--) {
        padre->setClave(j + 1, *padre->getClave(j));
    }

    padre->setClave(indice, *hijoLleno->getClave(t - 1));
    padre->incrementClave();
}


Producto* ArbolB::buscarFecha(string fecha) {
    if (raiz == nullptr) return nullptr;
    return buscarRecursivo(raiz, fechaAEntero(fecha));
}

Producto* ArbolB::buscarRecursivo(NodoB* nodo, int fechaClave) {
    int i = 0;
    int n = nodo->getCantidadClaves();

    while (i < n &&
           fechaAEntero(nodo->getClave(i)->getFechaCaducidad()) < fechaClave) {
        i++;
    }

    if (i < n && fechaAEntero(nodo->getClave(i)->getFechaCaducidad()) == fechaClave) {
        return nodo->getClave(i);
    }

    if (nodo->hoja()) return nullptr;

    // Bajar al hijo correspondiente
    return buscarRecursivo(nodo->getHijo(i), fechaClave);
}


void ArbolB::buscarRangoFecha(string fechaInicio, string fechaFin) {
    if (raiz == nullptr) {
        cout << "El arbol esta vacio." << endl;
        return;
    }
    int inicio = fechaAEntero(fechaInicio);
    int fin    = fechaAEntero(fechaFin);

    cout << "\n--- Productos con fecha de caducidad entre "
         << fechaInicio << " y " << fechaFin << " ---" << endl;

    buscarRango(raiz, inicio, fin);
    cout << "----------------------------------------------\n" << endl;
}

void ArbolB::buscarRango(NodoB* nodo, int fechaInicio, int fechaFin) {
    if (nodo == nullptr) return;

    int i = 0;
    int n = nodo->getCantidadClaves();

    while (i < n &&
           fechaAEntero(nodo->getClave(i)->getFechaCaducidad()) < fechaInicio) {
        // Antes de saltar la clave, revisar el subárbol izquierdo
        if (!nodo->hoja()) {
            buscarRango(nodo->getHijo(i), fechaInicio, fechaFin);
        }
        i++;
    }

    while (i < n &&
           fechaAEntero(nodo->getClave(i)->getFechaCaducidad()) <= fechaFin) {
        if (!nodo->hoja()) {
            buscarRango(nodo->getHijo(i), fechaInicio, fechaFin);
        }
        Producto* p = nodo->getClave(i);
        cout << "  [" << p->getFechaCaducidad() << "] "
             << p->getNombre()
             << " | Codigo: " << p->getCodigo()
             << " | Marca: "  << p->getMarca()
             << " | Precio: Q" << p->getPrecio()
             << " | Stock: " << p->getCantidad()
             << endl;
        i++;
    }

    // Visitar el último subárbol relevante
    if (!nodo->hoja() && i <= n) {
        buscarRango(nodo->getHijo(i), fechaInicio, fechaFin);
    }
}

void ArbolB::imprimirOrdenado() {
    if (raiz == nullptr) {
        cout << "El arbol esta vacio." << endl;
        return;
    }
    cout << "\n=== Productos ordenados por Fecha de Caducidad ===" << endl;
    recorridoInOrden(raiz);
    cout << "==================================================\n" << endl;
}

void ArbolB::recorridoInOrden(NodoB* nodo) {
    if (nodo == nullptr) return;

    int n = nodo->getCantidadClaves();
    for (int i = 0; i < n; i++) {
        // Visitar subárbol izquierdo
        if (!nodo->hoja()) {
            recorridoInOrden(nodo->getHijo(i));
        }
        Producto* p = nodo->getClave(i);
        cout << "  [" << p->getFechaCaducidad() << "] "
             << p->getNombre()
             << " | Marca: " << p->getMarca()
             << " | Precio: Q" << p->getPrecio()
             << endl;
    }
    // Visitar el hijo más a la derecha
    if (!nodo->hoja()) {
        recorridoInOrden(nodo->getHijo(n));
    }
}

void ArbolB::generarDOT(string nombreArchivo) {
    fstream archivo;
    archivo.open(nombreArchivo, ios::out);

    if (!archivo.is_open()) {
        cerr << "[ArbolB] No se pudo crear el archivo: " << nombreArchivo << endl;
        return;
    }

    archivo << "digraph ArbolB {\n";
    archivo << "  node [shape=record, fontname=\"Courier New\", fontsize=10];\n";
    archivo << "  graph [label=\"Arbol B — Clave: FechaCaducidad\", "
               "fontsize=14, fontname=\"Arial\"];\n";
    archivo << "  edge [arrowsize=0.7];\n\n";

    if (raiz != nullptr) {
        generarDotRecursivo(raiz, archivo);
    }

    archivo << "}\n";
    archivo.close();

    cout << "[ArbolB] Archivo DOT generado: " << nombreArchivo << endl;
    cout << "         Para convertir a imagen ejecuta:" << endl;
    cout << "         dot -Tpng " << nombreArchivo << " -o arbolB.png" << endl;
}

void ArbolB::generarDotRecursivo(NodoB* nodo, fstream& archivo) {
    if (nodo == nullptr) return;

    unsigned long long id = (unsigned long long)(void*)nodo;

    archivo << "  n" << id << " [label=\"";
    int n = nodo->getCantidadClaves();
    for (int i = 0; i < n; i++) {
        archivo << "<f" << i << ">|";
        Producto* p = nodo->getClave(i);
        archivo << p->getFechaCaducidad()
                << "\\n" << p->getNombre().substr(0, 12);
        if (i < n - 1) archivo << "|";
    }
    archivo << "|<f" << n << ">\"];\n";

    // ── Recursión y aristas hacia los hijos ──
    if (!nodo->hoja()) {
        for (int i = 0; i <= n; i++) {
            NodoB* hijo = nodo->getHijo(i);
            if (hijo != nullptr) {
                unsigned long long idHijo = (unsigned long long)(void*)hijo;
                archivo << "  n" << id << ":f" << i
                        << " -> n" << idHijo << ";\n";
                generarDotRecursivo(hijo, archivo);
            }
        }
    }
}

void ArbolB::eliminar(string fecha) {

    int clave =
        ConvertDate::toInt(fecha);

    eliminarRecursivo(
        raiz,
        clave
    );

    if (raiz->getCantidadClaves() == 0) {

        NodoB* temp = raiz;

        if (raiz->hoja())
            raiz = nullptr;

        else
            raiz = raiz->getHijo(0);

        delete temp;
    }
}


void ArbolB::eliminarRecursivo(NodoB* nodo, int clave) {
    if (nodo == nullptr) return;

    int idx = 0;
    while (idx < nodo->getCantidadClaves() &&
           fechaAEntero(nodo->getClave(idx)->getFechaCaducidad()) < clave) {
        idx++;
    }

    // Clave encontrada
    if (idx < nodo->getCantidadClaves() &&
        fechaAEntero(nodo->getClave(idx)->getFechaCaducidad()) == clave) {

        if (nodo->hoja()) {
            eliminarDeHoja(nodo, idx);
        } else {
            eliminarDeInterno(nodo, idx);
        }
    }
    else {
        if (nodo->hoja()) return; // no existe

        bool ultimoHijo = (idx == nodo->getCantidadClaves());

        if (!ultimoHijo && nodo->getHijo(idx)->getCantidadClaves() < gradoMinimo) {
            llenar(nodo, idx);
        }

        if (ultimoHijo && nodo->getHijo(idx-1)->getCantidadClaves() < gradoMinimo) {
            llenar(nodo, idx-1);
        }

        int hijoCorrecto = (idx == nodo->getCantidadClaves()) ? idx-1 : idx;
        eliminarRecursivo(nodo->getHijo(hijoCorrecto), clave);
    }
}

void ArbolB::eliminarDeHoja(NodoB* nodo, int idx) {
    for (int i = idx + 1; i < nodo->getCantidadClaves(); i++) {
        nodo->setClave(i - 1, *nodo->getClave(i));
    }
    nodo->decrementClave();
}

// Eliminar de nodo interno
void ArbolB::eliminarDeInterno(NodoB* nodo, int idx) {
    int clave = fechaAEntero(nodo->getClave(idx)->getFechaCaducidad());

    // Predecesor
    if (nodo->getHijo(idx)->getCantidadClaves() >= gradoMinimo) {
        Producto pred = obtenerPredecesor(nodo, idx);
        nodo->setClave(idx, pred);
        eliminarRecursivo(nodo->getHijo(idx), fechaAEntero(pred.getFechaCaducidad()));
    }
    // Sucesor
    else if (nodo->getHijo(idx + 1)->getCantidadClaves() >= gradoMinimo) {
        Producto succ = obtenerSucesor(nodo, idx);
        nodo->setClave(idx, succ);
        eliminarRecursivo(nodo->getHijo(idx + 1), fechaAEntero(succ.getFechaCaducidad()));
    }
    // Fusionar
    else {
        fusionar(nodo, idx);
        eliminarRecursivo(nodo->getHijo(idx), clave);
    }
}

// Obtener predecesor
Producto ArbolB::obtenerPredecesor(NodoB* nodo, int idx) {
    NodoB* actual = nodo->getHijo(idx);
    while (!actual->hoja()) {
        actual = actual->getHijo(actual->getCantidadClaves());
    }
    return *actual->getClave(actual->getCantidadClaves() - 1);
}

// Obtener sucesor
Producto ArbolB::obtenerSucesor(NodoB* nodo, int idx) {
    NodoB* actual = nodo->getHijo(idx + 1);
    while (!actual->hoja()) {
        actual = actual->getHijo(0);
    }
    return *actual->getClave(0);
}

void ArbolB::llenar(NodoB* nodo, int idx) {
    if (idx != 0 && nodo->getHijo(idx - 1)->getCantidadClaves() >= gradoMinimo)
        pedirPrestadoAnterior(nodo, idx);
    else if (idx != nodo->getCantidadClaves() && nodo->getHijo(idx + 1)->getCantidadClaves() >= gradoMinimo)
        pedirPrestadoSiguiente(nodo, idx);
    else {
        if (idx != nodo->getCantidadClaves())
            fusionar(nodo, idx);
        else
            fusionar(nodo, idx - 1);
    }
}

void ArbolB::pedirPrestadoAnterior(NodoB* nodo, int idx) {
    NodoB* hijo = nodo->getHijo(idx);
    NodoB* hermano = nodo->getHijo(idx - 1);

    // Mover clave del padre al hijo
    for (int i = hijo->getCantidadClaves() - 1; i >= 0; i--)
        hijo->setClave(i + 1, *hijo->getClave(i));

    hijo->setClave(0, *nodo->getClave(idx - 1));

    if (!hijo->hoja()) {
        for (int i = hijo->getCantidadClaves(); i >= 0; i--)
            hijo->setHijo(i + 1, hijo->getHijo(i));
        hijo->setHijo(0, hermano->getHijo(hermano->getCantidadClaves()));
    }

    nodo->setClave(idx - 1, *hermano->getClave(hermano->getCantidadClaves() - 1));

    hermano->decrementClave();
    hijo->incrementClave();
}

void ArbolB::pedirPrestadoSiguiente(NodoB* nodo, int idx) {
    NodoB* hijo = nodo->getHijo(idx);
    NodoB* hermano = nodo->getHijo(idx + 1);

    hijo->setClave(hijo->getCantidadClaves(), *nodo->getClave(idx));

    if (!hijo->hoja())
        hijo->setHijo(hijo->getCantidadClaves() + 1, hermano->getHijo(0));

    nodo->setClave(idx, *hermano->getClave(0));

    for (int i = 1; i < hermano->getCantidadClaves(); i++)
        hermano->setClave(i - 1, *hermano->getClave(i));

    if (!hermano->hoja()) {
        for (int i = 1; i <= hermano->getCantidadClaves(); i++)
            hermano->setHijo(i - 1, hermano->getHijo(i));
    }

    hermano->decrementClave();
    hijo->incrementClave();
}

void ArbolB::fusionar(NodoB* nodo, int idx) {
    NodoB* hijo = nodo->getHijo(idx);
    NodoB* hermano = nodo->getHijo(idx + 1);

    hijo->setClave(gradoMinimo - 1, *nodo->getClave(idx));

    for (int i = 0; i < hermano->getCantidadClaves(); i++)
        hijo->setClave(i + gradoMinimo, *hermano->getClave(i));

    if (!hijo->hoja()) {
        for (int i = 0; i <= hermano->getCantidadClaves(); i++)
            hijo->setHijo(i + gradoMinimo, hermano->getHijo(i));
    }

    for (int i = idx + 1; i < nodo->getCantidadClaves(); i++)
        nodo->setClave(i - 1, *nodo->getClave(i));

    for (int i = idx + 2; i <= nodo->getCantidadClaves(); i++)
        nodo->setHijo(i - 1, nodo->getHijo(i));

    hijo->incrementClave();

    nodo->decrementClave();
    delete hermano;
}