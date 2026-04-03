//
// Created by alejandro on 27/3/26.
//

#include "Logger.h"
#include <fstream>

void Logger::logError(const std::string& message) {

    std::ofstream file("error", std::ios::out);

    file << message << std::endl;
}

