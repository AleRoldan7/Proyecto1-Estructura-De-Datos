cmake_minimum_required(VERSION 4.1)
project(CatalogoProductos)

set(CMAKE_CXX_STANDARD 20)

add_executable(CatalogoProductos main.cpp
        clases/productos/Producto.cpp
        clases/productos/Producto.h
        estructuras/lista-enlazada/Nodo.cpp
        estructuras/lista-enlazada/Nodo.h
        estructuras/lista-enlazada/ListaEnlazada.cpp
        estructuras/lista-enlazada/ListaEnlazada.h)
