//
// Created by alejandro on 5/3/26.
//

#ifndef CATALOGOPRODUCTOS_PRODUCTO_H
#define CATALOGOPRODUCTOS_PRODUCTO_H
#include <iostream>
using namespace std;

class Producto {
private:
    string nombre;
    string codigo;
    string categoria;
    string fechaCaducidad;
    string marca;
    double precio;
    int cantidad;

public:
    Producto();

    Producto(const string &nombre, const string &codigo, const string &categoria, const string &fechaCaducidad,
             const string &marca, const double &precio, const int &cantidad);

    string getNombre() const;

    string getCodigo() const;

    string getCategoria() const;

    string getFechaCaducidad() const;

    string getMarca() const;

    double getPrecio() const;

    int getCantidad() const;

    void setNombre(const string &nombre);

    void setCodigo(const string &codigo);

    void setCategoria(const string &categoria);

    void setFechaCaducidad(const string &caducidad);

    void setMarca(const string &marca);

    void setPrecio(const double &precio);

    void setCantidad(const int &cantidad);
};


#endif //CATALOGOPRODUCTOS_PRODUCTO_H
