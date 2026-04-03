//
// Created by alejandro on 27/3/26.
//

#ifndef CATALOGOPRODUCTOS_CLEANCSV_H
#define CATALOGOPRODUCTOS_CLEANCSV_H
#include <chrono>
#include <string>

class CleanCSV {

public:
    static std::string removeQuotes(const std::string& str);
};


#endif //CATALOGOPRODUCTOS_CLEANCSV_H