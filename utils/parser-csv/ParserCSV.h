//
// Created by alejandro on 27/3/26.
//

#ifndef CATALOGOPRODUCTOS_PARSERCSV_H
#define CATALOGOPRODUCTOS_PARSERCSV_H
#include <string>


class Producto;

class ParserCSV {

public:

    static bool parseLine(const std::string& line, Producto& producto);
};


#endif //CATALOGOPRODUCTOS_PARSERCSV_H