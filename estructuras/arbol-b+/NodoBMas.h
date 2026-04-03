//
// Created by alejandro on 30/3/26.
//

#ifndef CATALOGOPRODUCTOS_NODOBMAS_H
#define CATALOGOPRODUCTOS_NODOBMAS_H
#include <string>

#include "../../clases/productos/Producto.h"
using namespace std;

class NodoBMas {
private:
    string *claves;
    int numClaves;

    Producto *producto;

    NodoBMas **nodoHijo;

    bool esHoja;
    int orden;

    NodoBMas *siguiente;
    NodoBMas *anterior;

    public:

    NodoBMas(int orden, bool esHoja);
    ~NodoBMas();

    bool getEsHoja();
    int getNumClaves();
    int getOrden();

    string getClave(int i);
    Producto getProducto(int i);
    NodoBMas *getHijo(int i);
    NodoBMas *getSiguiente();
    NodoBMas *getAnterior();

    void setClave(int i, string clave);
    void setProducto(int i, const Producto &p);
    void setHijo(int i, NodoBMas *nodo);
    void setSiguiente(NodoBMas *nodoSiguiente);
    void setAnterior(NodoBMas *nodoAnterior);

    void incrementarCLaves();
    void decrementarCLaves();
    void setNumClaves(int n);
    bool lleno() const;
};


#endif //CATALOGOPRODUCTOS_NODOBMAS_H
