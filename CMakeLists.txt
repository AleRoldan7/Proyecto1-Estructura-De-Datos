cmake_minimum_required(VERSION 3.10)
project(CatalogoProductos)

set(CMAKE_CXX_STANDARD 20)

add_executable(CatalogoProductos main.cpp
        clases/productos/Producto.cpp
        clases/productos/Producto.h
        estructuras/lista-enlazada/Nodo.cpp
        estructuras/lista-enlazada/Nodo.h
        estructuras/lista-enlazada/ListaEnlazada.cpp
        estructuras/lista-enlazada/ListaEnlazada.h
        estructuras/arbol-avl/NodoAvl.cpp
        estructuras/arbol-avl/NodoAvl.h
        estructuras/arbol-avl/ArbolAvl.cpp
        estructuras/arbol-avl/ArbolAvl.h
        utils/date/ConvertDate.cpp
        utils/date/ConvertDate.h
        utils/logger-error/Logger.cpp
        utils/logger-error/Logger.h
        utils/performance/Timer.cpp
        utils/performance/Timer.h
        utils/clean-csv/CleanCSV.cpp
        utils/clean-csv/CleanCSV.h
        utils/parser-csv/ParserCSV.cpp
        utils/parser-csv/ParserCSV.h
        estructuras/arbol-b/ArbolB.cpp
        estructuras/arbol-b/ArbolB.h
        estructuras/arbol-b/NodoB.cpp
        estructuras/arbol-b/NodoB.h
        leer-archivos/CargarCSV.cpp
        leer-archivos/CargarCSV.h
        estructuras/arbol-b+/NodoBMas.cpp
        estructuras/arbol-b+/NodoBMas.h
        estructuras/arbol-b+/ArbolBMas.cpp
        estructuras/arbol-b+/ArbolBMas.h)
