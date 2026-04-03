//
// Created by alejandro on 6/3/26.
//

#ifndef CATALOGOPRODUCTOS_ARBOLAVL_H
#define CATALOGOPRODUCTOS_ARBOLAVL_H
#include "NodoAvl.h"


class ArbolAvl {
private:
    NodoAvl *raiz;

    int altura(NodoAvl *nodo);

    int balance(NodoAvl *nodo);

    NodoAvl *rotacionDerecha(NodoAvl *y);

    NodoAvl *rotacionIzquierda(NodoAvl *x);

    NodoAvl *insertar(NodoAvl *nodo, Producto producto);

    NodoAvl *buscar(NodoAvl *nodo, string nombre);

    void inOrden(NodoAvl *nodo);

public:
    ArbolAvl();

    void insert(Producto producto);

    Producto *buscar(string nombre);

    void imprimir();

    void eliminar(string nombre);

    NodoAvl *getRaiz() const { return raiz; }
    NodoAvl *eliminar(NodoAvl *nodo, string nombre);

    NodoAvl *nodoMinimo(NodoAvl *nodo);

    void generarDotRecursivo(NodoAvl *nodo, fstream &archivo);

    void generarDOT(string nombreArchivo);
};


#endif //CATALOGOPRODUCTOS_ARBOLAVL_H
