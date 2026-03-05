//
// Created by alejandro on 5/3/26.
//

#ifndef CATALOGOPRODUCTOS_NODO_H
#define CATALOGOPRODUCTOS_NODO_H
#include "../../clases/productos/Producto.h"


class Nodo {
private:
    Producto producto;
    Nodo *siguiente;

public:
    Nodo();
    Nodo(Producto p);
    Producto getProducto();
    void setProducto(Producto p);
    void setSiguiente(Nodo *p);
    Nodo *getSiguiente();
};


#endif //CATALOGOPRODUCTOS_NODO_H