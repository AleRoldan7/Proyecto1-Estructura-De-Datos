//
// Created by alejandro on 5/3/26.
//

#include "Nodo.h"

Nodo::Nodo() {
    siguiente = nullptr;
}

Nodo::Nodo(Producto p) {
    producto = p;
    siguiente = nullptr;
}

Producto Nodo::getProducto() {
    return producto;
}

void Nodo::setProducto(Producto p) {
    producto = p;
}

Nodo *Nodo::getSiguiente() {
    return siguiente;
}

void Nodo::setSiguiente(Nodo* siguiente) {
    this->siguiente = siguiente;
}
