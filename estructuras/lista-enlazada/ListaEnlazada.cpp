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

    Nodo *nodo = new Nodo();

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

        cout << "Nombre: " << producto.getNombre() << endl;
        cout << "Codigo: " << producto.getCodigo() << endl;
        cout << "Categoria: " << producto.getCategoria() << endl;
        cout << "Fecha caducidad: " << producto.getFechaCaducidad() << endl;
        cout << "Marca: " << producto.getMarca() << endl;
        cout << "Precio: " << producto.getPrecio() << endl;
        cout << "Cantidad: " << producto.getCantidad() << endl;
        cout << "---------------------------" << endl;

        aux = aux->getSiguiente();
    }
}


void ListaEnlazada::buscar(string nombre) {

    Nodo *aux = head;

    while (aux != nullptr) {
        Producto producto = aux->getProducto();

        if (producto.getNombre() == nombre) {
            cout << "Producto encontrado " << endl;
            cout << "Nombre: " << producto.getNombre() << endl;
            cout << "Codigo: " << producto.getCodigo() << endl;
            cout << "Categoria: " << producto.getCategoria() << endl;
            cout << "Fecha Caducidad: " << producto.getFechaCaducidad() << endl;
            cout << "Marca: " << producto.getMarca() << endl;
            cout << "Precio: " << producto.getPrecio() << endl;
            cout << "Cantidad: " << producto.getCantidad() << endl;
        }

        aux = aux->getSiguiente();
    }

    cout << "No existe el producto " << endl;
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
