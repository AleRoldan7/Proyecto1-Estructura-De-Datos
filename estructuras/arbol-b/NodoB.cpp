//
// Created by alejandro on 27/3/26.
//

#include "NodoB.h"
#include <string>

NodoB::NodoB(int gradoMinimo, bool esHoja) {
    this->gradoMinimo    = gradoMinimo;
    this->esHoja         = esHoja;
    this->cantidadClaves = 0;

    this->clave = new Producto[2 * gradoMinimo - 1];

    this->hijos = new NodoB*[2 * gradoMinimo]();
}

NodoB::~NodoB() {
    delete[] clave;
    delete[] hijos;
}


int NodoB::getCantidadClaves() {
    return cantidadClaves;
}

bool NodoB::hoja() {
    return esHoja;
}

Producto* NodoB::getClave(int indice) {
    return &clave[indice];
}

NodoB* NodoB::getHijo(int indice) {
    return hijos[indice];
}


void NodoB::setClave(int indice, Producto producto) {
    clave[indice] = producto;
}

void NodoB::setHijo(int indice, NodoB* nodo) {
    hijos[indice] = nodo;
}

void NodoB::incrementClave() {
    cantidadClaves++;
}

void NodoB::decrementClave() {
    cantidadClaves--;
}
