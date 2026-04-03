//
// Created by alejandro on 6/3/26.
//

#ifndef CATALOGOPRODUCTOS_NODOAVL_H
#define CATALOGOPRODUCTOS_NODOAVL_H
#include "../../clases/productos/Producto.h"


class NodoAvl {

    private:

    Producto producto;
    NodoAvl *derecha;
    NodoAvl *izquierda;
    int altura;

    public:

    NodoAvl();
    NodoAvl(Producto produto);
    int getAltura();
    NodoAvl *getIzquierda();
    NodoAvl *getDerecha();

    void setIzquierda(NodoAvl* nodo);
    void setDerecha(NodoAvl* nodo);
    void setProducto(const Producto& produto);
    void setAltura(int altura);

    Producto getProducto();
};


#endif //CATALOGOPRODUCTOS_NODOAVL_H