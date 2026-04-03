//
// Created by alejandro on 27/3/26.
//

#ifndef CATALOGOPRODUCTOS_NODOB_H
#define CATALOGOPRODUCTOS_NODOB_H
#include "../../clases/productos/Producto.h"

class NodoB {

private:
   Producto* clave;
   NodoB** hijos;

   int gradoMinimo;
   int cantidadClaves;
   bool esHoja;

public:

   NodoB(int gradoMinimo, bool esHoja);
   ~NodoB();

   int getCantidadClaves();
   bool hoja();

   Producto* getClave(int indice);
   NodoB* getHijo(int indice);

   void setClave(int indice, Producto producto);
   void setHijo(int indice, NodoB* nodo);

   void incrementClave();
   void decrementClave();
};


#endif //CATALOGOPRODUCTOS_NODOB_H