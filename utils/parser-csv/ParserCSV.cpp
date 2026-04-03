#include "ParserCSV.h"

#include "../../clases/productos/Producto.h"
#include "../clean-csv/CleanCSV.h"
#include "../logger-error/Logger.h"

bool ParserCSV::parseLine(const std::string &line, Producto &producto) {
    std::string values[7];

    int index = 0;
    std::string temp = "";

    for (char c: line) {
        if (c == ',') {
            values[index++] = temp;
            temp = "";
        } else {
            temp += c;
        }
    }

    values[index++] = temp;

    if (index != 7) {
        Logger::logError("Linea corrupta: " + line);

        return false;
    }

    try {
        producto.setNombre(CleanCSV::removeQuotes(values[0]));

        producto.setCodigo(CleanCSV::removeQuotes(values[1]));

        producto.setCategoria(CleanCSV::removeQuotes(values[2]));

        producto.setFechaCaducidad(CleanCSV::removeQuotes(values[3]));

        producto.setMarca(CleanCSV::removeQuotes(values[4]));

        producto.setPrecio(std::stod(values[5]));

        producto.setCantidad(std::stoi(values[6]));

    } catch (std::exception &e) {
        Logger::logError("Error conversion: " + line);

        return false;
    }

    return true;
}
