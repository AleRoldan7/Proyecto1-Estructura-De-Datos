#include <iostream>

#include "clases/productos/Producto.h"
#include <string>
using namespace std;

int main() {
    Producto producto("Cereal", "558855", "Granos",
        "2026-05-15", "Bimbo", 15.50, 5);

    cout << producto.getNombre() << producto.getFechaCaducidad() << endl;
    return 0;
}
