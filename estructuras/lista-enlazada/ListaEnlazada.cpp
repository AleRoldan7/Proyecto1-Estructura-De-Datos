//
// Created by alejandro on 5/3/26.
//

#include "ListaEnlazada.h"

// ═══════════════════════════════════════════════════════════════
//  Constructor / Destructor
// ═══════════════════════════════════════════════════════════════

ListaEnlazada::ListaEnlazada() {
    head = nullptr;
}

ListaEnlazada::~ListaEnlazada() {
    Nodo *aux = head;

    while (aux != nullptr) {
        Nodo *tmp = aux;
        aux = aux->getSiguiente();
        delete tmp;
    }
}

// ═══════════════════════════════════════════════════════════════
//  LISTA DESORDENADA
//  Inserta al final — O(n)
//  CORRECCIÓN: se usa new Nodo(producto) para guardar el dato.
// ═══════════════════════════════════════════════════════════════

void ListaEnlazada::insert(Producto producto) {
    Nodo *nodo = new Nodo(producto);   // BUG CORREGIDO: antes era new Nodo()

    if (head == nullptr) {
        head = nodo;
    } else {
        Nodo *aux = head;

        while (aux->getSiguiente() != nullptr) {
            aux = aux->getSiguiente();
        }

        aux->setSiguiente(nodo);
    }
}

// ───────────────────────────────────────────────────────────────
//  imprimir — recorre e imprime todos los nodos — O(n)
// ───────────────────────────────────────────────────────────────

void ListaEnlazada::imprimir() {
    Nodo *aux = head;

    while (aux != nullptr) {
        Producto producto = aux->getProducto();

        cout << "Nombre: "          << producto.getNombre()         << endl;
        cout << "Codigo: "          << producto.getCodigo()         << endl;
        cout << "Categoria: "       << producto.getCategoria()      << endl;
        cout << "Fecha caducidad: " << producto.getFechaCaducidad() << endl;
        cout << "Marca: "           << producto.getMarca()          << endl;
        cout << "Precio: "          << producto.getPrecio()         << endl;
        cout << "Cantidad: "        << producto.getCantidad()       << endl;
        cout << "---------------------------" << endl;

        aux = aux->getSiguiente();
    }
}

// ───────────────────────────────────────────────────────────────
//  buscar (lista desordenada) — búsqueda secuencial — O(n)
//  Recorre nodo a nodo hasta hallar coincidencia por nombre.
//  Peor caso: el producto está al final o no existe.
// ───────────────────────────────────────────────────────────────

void ListaEnlazada::buscar(string nombre) {
    Nodo *aux = head;

    while (aux != nullptr) {
        Producto producto = aux->getProducto();

        if (producto.getNombre() == nombre) {
            cout << "Producto encontrado" << endl;

            cout << "Nombre: "          << producto.getNombre()         << endl;
            cout << "Codigo: "          << producto.getCodigo()         << endl;
            cout << "Categoria: "       << producto.getCategoria()      << endl;
            cout << "Fecha Caducidad: " << producto.getFechaCaducidad() << endl;
            cout << "Marca: "           << producto.getMarca()          << endl;
            cout << "Precio: "          << producto.getPrecio()         << endl;
            cout << "Cantidad: "        << producto.getCantidad()       << endl;

            return;
        }

        aux = aux->getSiguiente();
    }

    cout << "No existe el producto" << endl;
}

// ───────────────────────────────────────────────────────────────
//  remove — elimina por objeto Producto (compara por código) — O(n)
// ───────────────────────────────────────────────────────────────

void ListaEnlazada::remove(Producto producto) {
    if (head == nullptr) {
        return;
    }

    if (head->getProducto().getCodigo() == producto.getCodigo()) {
        Nodo *aux = head;
        head = head->getSiguiente();
        delete aux;
        return;
    }

    Nodo *actual = head;

    while (actual->getSiguiente() != nullptr) {
        if (actual->getSiguiente()->getProducto().getCodigo() == producto.getCodigo()) {
            Nodo *aux = actual->getSiguiente();
            actual->setSiguiente(aux->getSiguiente());
            delete aux;
            return;
        }
        actual = actual->getSiguiente();
    }
}

// ───────────────────────────────────────────────────────────────
//  eliminar — elimina por código de barras — O(n)
// ───────────────────────────────────────────────────────────────

void ListaEnlazada::eliminar(string codigo) {
    if (head == nullptr) return;

    if (head->getProducto().getCodigo() == codigo) {
        Nodo *aux = head;
        head = head->getSiguiente();
        delete aux;
        return;
    }

    Nodo *actual = head;
    while (actual->getSiguiente() != nullptr) {
        if (actual->getSiguiente()->getProducto().getCodigo() == codigo) {
            Nodo *aux = actual->getSiguiente();
            actual->setSiguiente(aux->getSiguiente());
            delete aux;
            return;
        }
        actual = actual->getSiguiente();
    }
}

// ═══════════════════════════════════════════════════════════════
//  LISTA ORDENADA (por nombre, orden alfabético ascendente)
// ═══════════════════════════════════════════════════════════════

// ───────────────────────────────────────────────────────────────
//  insertOrdenado — inserta manteniendo orden alfabético — O(n)
//  Recorre hasta encontrar el primer nodo cuyo nombre sea mayor
//  al del nuevo producto y lo inserta antes de él.
// ───────────────────────────────────────────────────────────────

void ListaEnlazada::insertOrdenado(Producto producto) {
    Nodo *nodo = new Nodo(producto);

    // Caso 1: lista vacía o nuevo nodo va antes que el head
    if (head == nullptr || producto.getNombre() < head->getProducto().getNombre()) {
        nodo->setSiguiente(head);
        head = nodo;
        return;
    }

    // Caso 2: buscar la posición correcta
    Nodo *actual = head;

    while (actual->getSiguiente() != nullptr &&
           actual->getSiguiente()->getProducto().getNombre() < producto.getNombre()) {
        actual = actual->getSiguiente();
    }

    // Insertar entre actual y actual->getSiguiente()
    nodo->setSiguiente(actual->getSiguiente());
    actual->setSiguiente(nodo);
}

// ───────────────────────────────────────────────────────────────
//  buscarOrdenado — búsqueda secuencial con corte anticipado — O(n)
//  Aprovecha el orden: si el nombre del nodo actual ya es mayor
//  al buscado, el producto no existe y se aborta la búsqueda.
//  Caso promedio: O(n/2). Peor caso: O(n) (último nodo o no existe).
// ───────────────────────────────────────────────────────────────

void ListaEnlazada::buscarOrdenado(string nombre) {
    Nodo *aux = head;

    while (aux != nullptr) {
        string nombreActual = aux->getProducto().getNombre();

        // Corte anticipado: si el nombre del nodo supera al buscado,
        // ya no puede existir más adelante (la lista está ordenada).
        if (nombreActual > nombre) {
            break;
        }

        if (nombreActual == nombre) {
            Producto producto = aux->getProducto();

            cout << "Producto encontrado (lista ordenada)" << endl;
            cout << "Nombre: "          << producto.getNombre()         << endl;
            cout << "Codigo: "          << producto.getCodigo()         << endl;
            cout << "Categoria: "       << producto.getCategoria()      << endl;
            cout << "Fecha Caducidad: " << producto.getFechaCaducidad() << endl;
            cout << "Marca: "           << producto.getMarca()          << endl;
            cout << "Precio: "          << producto.getPrecio()         << endl;
            cout << "Cantidad: "        << producto.getCantidad()       << endl;

            return;
        }

        aux = aux->getSiguiente();
    }

    cout << "No existe el producto" << endl;
}

// ───────────────────────────────────────────────────────────────
//  eliminarOrdenado — elimina de la lista ordenada por nombre — O(n)
//  Igual que eliminar() pero con corte anticipado.
// ───────────────────────────────────────────────────────────────

void ListaEnlazada::eliminarOrdenado(string nombre) {
    if (head == nullptr) return;

    // Caso: el nodo a eliminar es el head
    if (head->getProducto().getNombre() == nombre) {
        Nodo *aux = head;
        head = head->getSiguiente();
        delete aux;
        return;
    }

    Nodo *actual = head;

    while (actual->getSiguiente() != nullptr) {
        string nombreSig = actual->getSiguiente()->getProducto().getNombre();

        // Corte anticipado: si el siguiente ya supera el nombre, no existe
        if (nombreSig > nombre) return;

        if (nombreSig == nombre) {
            Nodo *aux = actual->getSiguiente();
            actual->setSiguiente(aux->getSiguiente());
            delete aux;
            return;
        }

        actual = actual->getSiguiente();
    }
}

// ───────────────────────────────────────────────────────────────
//  imprimirOrdenado — imprime la lista ordenada — O(n)
//  (mismo recorrido que imprimir, se incluye por claridad)
// ───────────────────────────────────────────────────────────────

void ListaEnlazada::imprimirOrdenado() {
    if (head == nullptr) {
        cout << "Lista ordenada vacia." << endl;
        return;
    }

    cout << "\n=== PRODUCTOS ORDENADOS ALFABETICAMENTE (Lista Ordenada) ===" << endl;

    Nodo *aux = head;

    while (aux != nullptr) {
        Producto producto = aux->getProducto();

        cout << "Nombre: "          << producto.getNombre()         << endl;
        cout << "Codigo: "          << producto.getCodigo()         << endl;
        cout << "Categoria: "       << producto.getCategoria()      << endl;
        cout << "Fecha caducidad: " << producto.getFechaCaducidad() << endl;
        cout << "Marca: "           << producto.getMarca()          << endl;
        cout << "Precio: "          << producto.getPrecio()         << endl;
        cout << "Cantidad: "        << producto.getCantidad()       << endl;
        cout << "---------------------------" << endl;

        aux = aux->getSiguiente();
    }

    cout << "============================================================" << endl;
}