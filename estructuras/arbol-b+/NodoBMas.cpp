//
// Created by alejandro on 30/3/26.
//

#include "NodoBMas.h"

using namespace std;

NodoBMas::NodoBMas(int orden, bool esHoja) {
    this->orden = orden;
    this->esHoja = esHoja;

    numClaves = 0;
    siguiente = nullptr;
    anterior = nullptr;

    int maxClaves = 2 * orden - 1;
    int maxHijos = 2 * orden;

    claves = new string[maxClaves];
    producto = new Producto[maxClaves];
    nodoHijo = new NodoBMas *[maxHijos];

    for (int i = 0; i < maxHijos; i++) nodoHijo[i] = nullptr;
}

NodoBMas::~NodoBMas() {
    delete [] claves;
    delete [] producto;
    delete [] nodoHijo;
}

bool NodoBMas::getEsHoja() {
    return esHoja;
}

int NodoBMas::getNumClaves() {
    return numClaves;
}

int NodoBMas::getOrden() {
    return orden;
}

string NodoBMas::getClave(int i) {
    return claves[i];
}

Producto NodoBMas::getProducto(int i) {
    return producto[i];
}

NodoBMas *NodoBMas::getHijo(int i) {
    return nodoHijo[i];
}

NodoBMas *NodoBMas::getSiguiente() {
    return siguiente;
}

NodoBMas *NodoBMas::getAnterior() {
    return anterior;
}

void NodoBMas::setClave(int i, string clave) {
    claves[i] = clave;
}

void NodoBMas::setProducto(int i, const Producto &p) {
    producto[i] = p;
}

void NodoBMas::setHijo(int i, NodoBMas *nodo) {
    nodoHijo[i] = nodo;
}

void NodoBMas::setSiguiente(NodoBMas *nodo) {
    siguiente = nodo;
}

void NodoBMas::setAnterior(NodoBMas *nodo) {
    anterior = nodo;
}

void NodoBMas::incrementarCLaves() {
    numClaves++;
}

void NodoBMas::decrementarCLaves() {
    if (numClaves > 0) {
        numClaves--;
    }
}

void NodoBMas::setNumClaves(int n) {
    numClaves = n;
}

bool NodoBMas::lleno() const {
    return numClaves == 2 * orden - 1;
}
