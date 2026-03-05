//
// Created by alejandro on 5/3/26.
//

#include "Producto.h"


Producto::Producto(const string &nombre, const string &codigo, const string &categoria, const string &fechaCaducidad,
                   const string &marca, const double &precio, const int &cantidad) {

    this->nombre = nombre;
    this->codigo = codigo;
    this->categoria = categoria;
    this->fechaCaducidad = fechaCaducidad;
    this->marca = marca;
    this->precio = precio;
    this->cantidad = cantidad;
}

string Producto::getNombre() const {
    return nombre;
}

string Producto::getCodigo() const {
    return codigo;
}

string Producto::getCategoria() const {
    return categoria;
}

string Producto::getFechaCaducidad() const {
    return fechaCaducidad;
}

string Producto::getMarca() const {
    return marca;
}

double Producto::getPrecio() const {
    return precio;
}

int Producto::getCantidad() const {
    return cantidad;
}

void Producto::setNombre(const string &nombre) {
    this->nombre = nombre;
}

void Producto::setCodigo(const string &codigo) {
    this->codigo = codigo;
}

void Producto::setCategoria(const string &categoria) {
    this->categoria = categoria;
}

void Producto::setFechaCaducidad(const string &fecha) {
    this->fechaCaducidad = fecha;
}

void Producto::setMarca(const string &marca) {
    this->marca = marca;
}

void Producto::setPrecio(const double &precio) {
    this->precio = precio;
}

void Producto::setCantidad(const int &cantidad) {
    this->cantidad = cantidad;
}

