//
// Created by alejandro on 30/3/26.
//

#ifndef CATALOGOPRODUCTOS_ARBOLBMAS_H
#define CATALOGOPRODUCTOS_ARBOLBMAS_H
#include "NodoBMas.h"
#include <fstream>
#include <string>
using namespace std;

class ArbolBMas {
private:
    NodoBMas *raiz;
    NodoBMas *primeraHoja;
    int orden;

    void insertarEnNodo(NodoBMas *nodo, const string &categoria, const Producto &p);

    void dividirHijo(NodoBMas *padre, int indice, NodoBMas *hijo);

    void dividirHojaHijo(NodoBMas *padre, int indice, NodoBMas *hijo);

    void eliminarRecursivo(NodoBMas *nodo, const string &categoria, const string &codigoBarra);

    void eliminarDeHoja(NodoBMas *nodo, int idx);

    void eliminarDeInterno(NodoBMas *nodo, int idx);

    void llenar(NodoBMas *nodo, int idx);

    void pedirPrestadoAnterior(NodoBMas *nodo, int idx);

    void pedirPrestadoSiguiente(NodoBMas *nodo, int idx);

    void fusionar(NodoBMas *nodo, int idx);

    void generarDotRecursivo(NodoBMas *nodo, fstream &archivo, int &contadorHoja);

    void liberarNodo(NodoBMas *nodo);

    void imprimirNivelPorNivel() const;

public:
    ArbolBMas();

    ArbolBMas(int orden);

    ~ArbolBMas();

    void insertar(const Producto &p);

    void eliminar(const string &categoria, const string &codigoBarra);

    void buscarCategoria(const string &categoria) const;

    void imprimirOrdenado() const;

    void mostrarArbol() const;

    void generarDOT(const string &nombreArchivo);
};


#endif //CATALOGOPRODUCTOS_ARBOLBMAS_H
