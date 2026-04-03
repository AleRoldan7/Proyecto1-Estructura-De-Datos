//
// Created by alejandro on 27/3/26.
//

#ifndef CATALOGOPRODUCTOS_ARBOLB_H
#define CATALOGOPRODUCTOS_ARBOLB_H
#include "NodoB.h"


class ArbolB {
private:
    NodoB *raiz;
    int gradoMinimo;

    void insertarNodoLleno(NodoB *nodo, Producto producto);

    void dividirHijo(NodoB *padre, int indice, NodoB *hijoLleno);

    Producto *buscarRecursivo(NodoB *nodo, int fechaClave);

    void buscarRango(NodoB *nodo, int fechaInicio, int fechaFin);

    void recorridoInOrden(NodoB *nodo);

    void generarDotRecursivo(NodoB *nodo, std::fstream &archivo);

    void liberarNodo(NodoB *nodo);

public:
    ArbolB();

    ArbolB(int gradoMinimo);

    ~ArbolB();

    void insertar(Producto producto);

    Producto *buscarFecha(string fecha);

    void buscarRangoFecha(string fechaInicio, string fechaFin);

    void imprimirOrdenado();

    void generarDOT(string nombreArchivo);

    void eliminar(string fecha);

    void eliminarRecursivo(NodoB *nodo, int clave);

    void eliminarDeHoja(NodoB *nodo, int indice);

    void eliminarDeInterno(NodoB *nodo, int indice);

    Producto obtenerPredecesor(NodoB *nodo, int indice);

    Producto obtenerSucesor(NodoB *nodo, int indice);

    void llenar(NodoB *nodo, int indice);

    void fusionar(NodoB *nodo, int indice);

    void pedirPrestadoAnterior(NodoB *nodo, int indice);

    void pedirPrestadoSiguiente(NodoB *nodo, int indice);

    NodoB *getRaiz() const { return raiz; }
};


#endif //CATALOGOPRODUCTOS_ARBOLB_H
