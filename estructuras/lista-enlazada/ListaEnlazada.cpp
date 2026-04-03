//
// Created by alejandro on 5/3/26.
//

#include "ListaEnlazada.h"



ListaEnlazada::ListaEnlazada() {
    head = nullptr;
}

ListaEnlazada::~ListaEnlazada() {
    Nodo *aux = head;

    while (aux != nullptr) {
        Nodo *tmp = aux;
        aux = aux->getSiguiente();
        delete tmp;
    }
}



void ListaEnlazada::insert(Producto producto) {
    Nodo *nodo = new Nodo(producto);   /

    if (head == nullptr) {
        head = nodo;
    } else {
        Nodo *aux = head;

        while (aux->getSiguiente() != nullptr) {
            aux = aux->getSiguiente();
        }

        aux->setSiguiente(nodo);
    }
}


void ListaEnlazada::imprimir() {
    Nodo *aux = head;

    while (aux != nullptr) {
        Producto producto = aux->getProducto();

        cout << "Nombre: "          << producto.getNombre()         << endl;
        cout << "Codigo: "          << producto.getCodigo()         << endl;
        cout << "Categoria: "       << producto.getCategoria()      << endl;
        cout << "Fecha caducidad: " << producto.getFechaCaducidad() << endl;
        cout << "Marca: "           << producto.getMarca()          << endl;
        cout << "Precio: "          << producto.getPrecio()         << endl;
        cout << "Cantidad: "        << producto.getCantidad()       << endl;
        cout << "---------------------------" << endl;

        aux = aux->getSiguiente();
    }
}



void ListaEnlazada::buscar(string nombre) {
    Nodo *aux = head;

    while (aux != nullptr) {
        Producto producto = aux->getProducto();

        if (producto.getNombre() == nombre) {
            cout << "Producto encontrado" << endl;

            cout << "Nombre: "          << producto.getNombre()         << endl;
            cout << "Codigo: "          << producto.getCodigo()         << endl;
            cout << "Categoria: "       << producto.getCategoria()      << endl;
            cout << "Fecha Caducidad: " << producto.getFechaCaducidad() << endl;
            cout << "Marca: "           << producto.getMarca()          << endl;
            cout << "Precio: "          << producto.getPrecio()         << endl;
            cout << "Cantidad: "        << producto.getCantidad()       << endl;

            return;
        }

        aux = aux->getSiguiente();
    }

    cout << "No existe el producto" << endl;
}



void ListaEnlazada::remove(Producto producto) {
    if (head == nullptr) {
        return;
    }

    if (head->getProducto().getCodigo() == producto.getCodigo()) {
        Nodo *aux = head;
        head = head->getSiguiente();
        delete aux;
        return;
    }

    Nodo *actual = head;

    while (actual->getSiguiente() != nullptr) {
        if (actual->getSiguiente()->getProducto().getCodigo() == producto.getCodigo()) {
            Nodo *aux = actual->getSiguiente();
            actual->setSiguiente(aux->getSiguiente());
            delete aux;
            return;
        }
        actual = actual->getSiguiente();
    }
}


void ListaEnlazada::eliminar(string codigo) {
    if (head == nullptr) return;

    if (head->getProducto().getCodigo() == codigo) {
        Nodo *aux = head;
        head = head->getSiguiente();
        delete aux;
        return;
    }

    Nodo *actual = head;
    while (actual->getSiguiente() != nullptr) {
        if (actual->getSiguiente()->getProducto().getCodigo() == codigo) {
            Nodo *aux = actual->getSiguiente();
            actual->setSiguiente(aux->getSiguiente());
            delete aux;
            return;
        }
        actual = actual->getSiguiente();
    }
}


void ListaEnlazada::insertOrdenado(Producto producto) {
    Nodo *nodo = new Nodo(producto);

    if (head == nullptr || producto.getNombre() < head->getProducto().getNombre()) {
        nodo->setSiguiente(head);
        head = nodo;
        return;
    }

    Nodo *actual = head;

    while (actual->getSiguiente() != nullptr &&
           actual->getSiguiente()->getProducto().getNombre() < producto.getNombre()) {
        actual = actual->getSiguiente();
    }

    nodo->setSiguiente(actual->getSiguiente());
    actual->setSiguiente(nodo);
}



void ListaEnlazada::buscarOrdenado(string nombre) {
    Nodo *aux = head;

    while (aux != nullptr) {
        string nombreActual = aux->getProducto().getNombre();
.
        if (nombreActual > nombre) {
            break;
        }

        if (nombreActual == nombre) {
            Producto producto = aux->getProducto();

            cout << "Producto encontrado (lista ordenada)" << endl;
            cout << "Nombre: "          << producto.getNombre()         << endl;
            cout << "Codigo: "          << producto.getCodigo()         << endl;
            cout << "Categoria: "       << producto.getCategoria()      << endl;
            cout << "Fecha Caducidad: " << producto.getFechaCaducidad() << endl;
            cout << "Marca: "           << producto.getMarca()          << endl;
            cout << "Precio: "          << producto.getPrecio()         << endl;
            cout << "Cantidad: "        << producto.getCantidad()       << endl;

            return;
        }

        aux = aux->getSiguiente();
    }

    cout << "No existe el producto" << endl;
}



void ListaEnlazada::eliminarOrdenado(string nombre) {
    if (head == nullptr) return;

    // Caso: el nodo a eliminar es el head
    if (head->getProducto().getNombre() == nombre) {
        Nodo *aux = head;
        head = head->getSiguiente();
        delete aux;
        return;
    }

    Nodo *actual = head;

    while (actual->getSiguiente() != nullptr) {
        string nombreSig = actual->getSiguiente()->getProducto().getNombre();

        if (nombreSig > nombre) return;

        if (nombreSig == nombre) {
            Nodo *aux = actual->getSiguiente();
            actual->setSiguiente(aux->getSiguiente());
            delete aux;
            return;
        }

        actual = actual->getSiguiente();
    }
}



void ListaEnlazada::imprimirOrdenado() {
    if (head == nullptr) {
        cout << "Lista ordenada vacia." << endl;
        return;
    }

    cout << "\n=== PRODUCTOS ORDENADOS ALFABETICAMENTE (Lista Ordenada) ===" << endl;

    Nodo *aux = head;

    while (aux != nullptr) {
        Producto producto = aux->getProducto();

        cout << "Nombre: "          << producto.getNombre()         << endl;
        cout << "Codigo: "          << producto.getCodigo()         << endl;
        cout << "Categoria: "       << producto.getCategoria()      << endl;
        cout << "Fecha caducidad: " << producto.getFechaCaducidad() << endl;
        cout << "Marca: "           << producto.getMarca()          << endl;
        cout << "Precio: "          << producto.getPrecio()         << endl;
        cout << "Cantidad: "        << producto.getCantidad()       << endl;
        cout << "---------------------------" << endl;

        aux = aux->getSiguiente();
    }

    cout << "============================================================" << endl;
}