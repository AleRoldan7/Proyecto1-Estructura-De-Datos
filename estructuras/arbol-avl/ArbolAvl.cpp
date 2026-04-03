//
// Created by alejandro on 6/3/26.
//

#include "ArbolAvl.h"
#include <fstream>

ArbolAvl::ArbolAvl() {
    raiz = nullptr;
}

int ArbolAvl::altura(NodoAvl *nodo) {
    if (nodo == nullptr) {
        return 0;
    }

    return nodo->getAltura();
}

int ArbolAvl::balance(NodoAvl *nodo) {
    if (nodo == nullptr) {
        return 0;
    }

    return altura(nodo->getIzquierda()) - altura(nodo->getDerecha());
}

NodoAvl *ArbolAvl::rotacionDerecha(NodoAvl *y) {
    NodoAvl *x = y->getIzquierda();
    NodoAvl *z = x->getDerecha();

    x->setDerecha(y);
    y->setIzquierda(z);

    y->setAltura(max(altura(y->getIzquierda()), altura(y->getDerecha())) + 1);
    x->setAltura(max(altura(x->getIzquierda()), altura(x->getDerecha())) + 1);

    return x;
}

NodoAvl *ArbolAvl::rotacionIzquierda(NodoAvl *x) {
    NodoAvl *y = x->getDerecha();
    NodoAvl *z = y->getIzquierda();

    y->setIzquierda(x);
    x->setDerecha(z);

    x->setAltura(max(altura(x->getIzquierda()), altura(x->getDerecha())) + 1);
    y->setAltura(max(altura(y->getIzquierda()), altura(y->getDerecha())) + 1);

    return y;
}

NodoAvl *ArbolAvl::nodoMinimo(NodoAvl *nodo) {
    NodoAvl *actual = nodo;

    while (actual->getIzquierda() != nullptr)
        actual = actual->getIzquierda();

    return actual;
}

NodoAvl *ArbolAvl::eliminar(NodoAvl *nodo, string nombre) {
    if (nodo == nullptr)
        return nodo;

    if (nombre < nodo->getProducto().getNombre())
        nodo->setIzquierda(eliminar(nodo->getIzquierda(), nombre));

    else if (nombre > nodo->getProducto().getNombre())
        nodo->setDerecha(eliminar(nodo->getDerecha(), nombre));

    else {
        // nodo encontrado
        if (nodo->getIzquierda() == nullptr || nodo->getDerecha() == nullptr) {
            NodoAvl *temp = nodo->getIzquierda() ? nodo->getIzquierda() : nodo->getDerecha();

            if (temp == nullptr) {
                delete nodo;
                nodo = nullptr;
            } else {
                *nodo = *temp; // copy
                delete temp;
            }
        } else {
            NodoAvl *temp = nodoMinimo(nodo->getDerecha());
            nodo->setProducto(temp->getProducto());
            nodo->setDerecha(eliminar(nodo->getDerecha(), temp->getProducto().getNombre()));
        }
    }

    if (nodo == nullptr)
        return nodo;

    nodo->setAltura(1 + max(altura(nodo->getIzquierda()), altura(nodo->getDerecha())));

    int factor = balance(nodo);

    // Rotaciones
    if (factor > 1 && balance(nodo->getIzquierda()) >= 0)
        return rotacionDerecha(nodo);

    if (factor > 1 && balance(nodo->getIzquierda()) < 0) {
        nodo->setIzquierda(rotacionIzquierda(nodo->getIzquierda()));
        return rotacionDerecha(nodo);
    }

    if (factor < -1 && balance(nodo->getDerecha()) <= 0)
        return rotacionIzquierda(nodo);

    if (factor < -1 && balance(nodo->getDerecha()) > 0) {
        nodo->setDerecha(rotacionDerecha(nodo->getDerecha()));
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

void ArbolAvl::generarDotRecursivo(
    NodoAvl *nodo,
    fstream &archivo
) {
    if (!nodo) return;

    Producto p = nodo->getProducto();

    archivo
            << "\""
            << p.getNombre()
            << "\" [label=\""
            << p.getNombre()
            << "\\nQ"
            << p.getPrecio()
            << "\"];\n";

    if (nodo->getIzquierda()) {
        archivo
                << "\""
                << p.getNombre()
                << "\" -> \""
                << nodo->getIzquierda()->getProducto().getNombre()
                << "\";\n";

        generarDotRecursivo(
            nodo->getIzquierda(),
            archivo
        );
    }

    if (nodo->getDerecha()) {
        archivo
                << "\""
                << p.getNombre()
                << "\" -> \""
                << nodo->getDerecha()->getProducto().getNombre()
                << "\";\n";

        generarDotRecursivo(
            nodo->getDerecha(),
            archivo
        );
    }
}

void ArbolAvl::generarDOT(string nombreArchivo) {
    fstream archivo;
    archivo.open(nombreArchivo, ios::out);

    if (!archivo.is_open()) {
        cout << "Error creando archivo DOT" << endl;
        return;
    }

    archivo << "digraph AVL {\n";

    // CONFIGURACION GENERAL
    archivo << "graph [\n";
    archivo << "  layout=dot,\n";
    archivo << "  rankdir=TB,\n";
    archivo << "  bgcolor=\"#ffffff\",\n";
    archivo << "  nodesep=0.6,\n";
    archivo << "  ranksep=0.8\n";
    archivo << "];\n";

    // ESTILO DE NODOS
    archivo << "node [\n";
    archivo << "  shape=circle,\n";
    archivo << "  style=filled,\n";
    archivo << "  fillcolor=\"#E3F2FD\",\n";
    archivo << "  color=\"#1E88E5\",\n";
    archivo << "  fontname=\"Arial\",\n";
    archivo << "  fontsize=11,\n";
    archivo << "  width=0.8,\n";
    archivo << "  height=0.8\n";
    archivo << "];\n";

    // ESTILO DE FLECHAS
    archivo << "edge [\n";
    archivo << "  color=\"#555555\",\n";
    archivo << "  arrowsize=0.7\n";
    archivo << "];\n\n";

    generarDotRecursivo(raiz, archivo);

    archivo << "}\n";

    archivo.close();

    cout << "DOT generado correctamente\n";
}

void ArbolAvl::inOrden(NodoAvl *nodo) {
    if (nodo == nullptr)
        return;

    inOrden(nodo->getIzquierda());

    Producto p = nodo->getProducto();

    cout << "Nombre: " << p.getNombre() << endl;
    cout << "Codigo: " << p.getCodigo() << endl;
    cout << "Categoria: " << p.getCategoria() << endl;
    cout << "Fecha caducidad: " << p.getFechaCaducidad() << endl;
    cout << "Marca: " << p.getMarca() << endl;
    cout << "Precio: Q" << p.getPrecio() << endl;
    cout << "Stock: " << p.getCantidad() << endl;
    cout << "---------------------------" << endl;

    inOrden(nodo->getDerecha());
}

void ArbolAvl::imprimir() {
    if (raiz == nullptr) {
        cout << "AVL vacio" << endl;
        return;
    }

    cout << "\n=== PRODUCTOS ORDENADOS POR NOMBRE (AVL) ===\n";

    inOrden(raiz);

    cout << "============================================\n";
}

void ArbolAvl::eliminar(string nombre) {
    raiz = eliminar(
        raiz,
        nombre
    );
}

void ArbolAvl::insert(Producto producto) {
    raiz = insertar(raiz, producto);
}

NodoAvl *ArbolAvl::insertar(NodoAvl *nodo, Producto producto) {
    if (nodo == nullptr)
        return new NodoAvl(producto);

    if (producto.getNombre() < nodo->getProducto().getNombre())
        nodo->setIzquierda(insertar(nodo->getIzquierda(), producto));
    else if (producto.getNombre() > nodo->getProducto().getNombre())
        nodo->setDerecha(insertar(nodo->getDerecha(), producto));
    else
        return nodo; // duplicado, no insertar

    nodo->setAltura(1 + max(altura(nodo->getIzquierda()), altura(nodo->getDerecha())));

    int factor = balance(nodo);

    if (factor > 1 && producto.getNombre() < nodo->getIzquierda()->getProducto().getNombre())
        return rotacionDerecha(nodo);

    if (factor < -1 && producto.getNombre() > nodo->getDerecha()->getProducto().getNombre())
        return rotacionIzquierda(nodo);

    if (factor > 1 && producto.getNombre() > nodo->getIzquierda()->getProducto().getNombre()) {
        nodo->setIzquierda(rotacionIzquierda(nodo->getIzquierda()));
        return rotacionDerecha(nodo);
    }

    if (factor < -1 && producto.getNombre() < nodo->getDerecha()->getProducto().getNombre()) {
        nodo->setDerecha(rotacionDerecha(nodo->getDerecha()));
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

NodoAvl *ArbolAvl::buscar(NodoAvl *nodo, string nombre) {
    if (nodo == nullptr) return nullptr;
    if (nombre == nodo->getProducto().getNombre()) return nodo;
    if (nombre < nodo->getProducto().getNombre()) return buscar(nodo->getIzquierda(), nombre);
    return buscar(nodo->getDerecha(), nombre);
}

Producto *ArbolAvl::buscar(string nombre) {
    NodoAvl *resultado = buscar(raiz, nombre);
    if (resultado == nullptr) return nullptr;
    static Producto encontrado;
    encontrado = resultado->getProducto();
    return &encontrado;
}
