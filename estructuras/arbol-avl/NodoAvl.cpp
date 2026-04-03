//
// Created by alejandro on 6/3/26.
//

#include "NodoAvl.h"

NodoAvl::NodoAvl(){
    derecha = nullptr;
    izquierda = nullptr;
    altura = 1;
}

NodoAvl::NodoAvl(Producto producto){
    this->producto = producto;
    derecha = nullptr;
    izquierda = nullptr;
    altura = 1;
}

int NodoAvl::getAltura(){
    return altura;
}

NodoAvl* NodoAvl::getIzquierda(){
    return izquierda;
}

NodoAvl* NodoAvl::getDerecha(){
    return derecha;
}

void NodoAvl::setIzquierda(NodoAvl* nodo){
    izquierda = nodo;
}

void NodoAvl::setDerecha(NodoAvl* nodo){
    derecha = nodo;
}

void NodoAvl::setAltura(int altura){
    this->altura = altura;
}

Producto NodoAvl::getProducto(){
    return producto;
}

void NodoAvl::setProducto(const Producto& producto){
    this->producto = producto;
}