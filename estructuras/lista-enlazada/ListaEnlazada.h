//
// Created by alejandro on 5/3/26.
//

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include "Nodo.h"
#include <iostream>
using namespace std;

class ListaEnlazada {
private:
    Nodo *head;

public:
    ListaEnlazada();
    ~ListaEnlazada();

    // ── Lista desordenada ──────────────────────────────────────
    void insert(Producto producto);          // Inserta al final         O(n)
    void imprimir();                         // Imprime todos los nodos  O(n)
    void buscar(string nombre);              // Búsqueda secuencial      O(n)
    void remove(Producto producto);          // Elimina por objeto       O(n)
    void eliminar(string codigo);            // Elimina por código       O(n)

    // ── Lista ordenada (orden alfabético por nombre) ───────────
    void insertOrdenado(Producto producto);  // Inserta en posición      O(n)
    void buscarOrdenado(string nombre);      // Búsqueda con corte       O(n)
    void eliminarOrdenado(string nombre);    // Elimina con corte        O(n)
    void imprimirOrdenado();                 // Imprime en orden         O(n)
};

#endif //LISTAENLAZADA_H