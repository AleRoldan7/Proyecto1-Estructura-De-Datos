//
// Created by alejandro on 29/3/26.
//

#ifndef CATALOGOPRODUCTOS_CARGARCSV_H
#define CATALOGOPRODUCTOS_CARGARCSV_H

#include <string>
#include <fstream>
#include "../clases/productos/Producto.h"
#include "../estructuras/arbol-avl/ArbolAvl.h"
#include "../estructuras/arbol-b+/ArbolBMas.h"
#include "../estructuras/arbol-b/ArbolB.h"
#include  "../estructuras/lista-enlazada/ListaEnlazada.h"
using namespace std;

class CargarCSV {
private:
    string rutaArchivo;
    string rutaLog;

    // Quita las comillas que rodean un campo
    string quitarComillas(const string &campo);

    // Divide una línea CSV respetando campos entre comillas.
    // Retorna false si la línea tiene un número incorrecto de campos.
    bool parsearLinea(const string &linea, string campos[], int numCampos);

    // Escribe un mensaje en el archivo de log.
    void loggear(ofstream &log, int numLinea, const string &mensaje, const string &linea);

    // Verifica que una cadena represente un número decimal válido.
    bool esNumerico(const string &s);

    // Verifica que una cadena represente un entero no negativo.
    bool esEntero(const string &s);

    // Rollback: elimina el producto de todas las estructuras que ya lo aceptaron.
    void rollback(const Producto &p,
                   ArbolB *arbolB,
                   ArbolAvl *avl,
                   ArbolBMas *arbolBMas,
                   ListaEnlazada *lista,
                   bool insertadoB,
                   bool insertadoBMas,
                   bool insertadoAVL,
                   bool insertadoHash,
                   bool insertadoLista);

public:
    // rutaLog por defecto: "errors.log" en el directorio de trabajo
    CargarCSV(const string &rutaArchivo, const string &rutaLog = "errors.log");

    // Carga el CSV e inserta en todas las estructuras.
    // Retorna la cantidad de productos cargados exitosamente.
    int cargar(ArbolB *arbolB, ArbolAvl *arbolAVL, ArbolBMas *arbolBMas, ListaEnlazada *lista);
};


#endif //CATALOGOPRODUCTOS_CARGARCSV_H
