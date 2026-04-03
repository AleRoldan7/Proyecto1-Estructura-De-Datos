//
// Created by alejandro on 27/3/26.
//

#include "CleanCSV.h"

std::string CleanCSV::removeQuotes(const std::string& str) {

    if (str.length() >= 2 && str.front() == '"' && str.back() == '"') {

        return str.substr(1, str.length() - 2);
    }

    return str;
}

