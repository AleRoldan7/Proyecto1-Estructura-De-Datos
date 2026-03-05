//
// Created by alejandro on 5/3/26.
//

#ifndef CATALOGOPRODUCTOS_LISTAENLAZADA_H
#define CATALOGOPRODUCTOS_LISTAENLAZADA_H
#include "Nodo.h"


class ListaEnlazada {
    private:
    Nodo *head;

    public:
    ListaEnlazada();
    ~ListaEnlazada();
    void insert(Producto producto);
    void remove(Producto producto);
    void buscar(string nombre);
    void imprimir();

};


#endif //CATALOGOPRODUCTOS_LISTAENLAZADA_H