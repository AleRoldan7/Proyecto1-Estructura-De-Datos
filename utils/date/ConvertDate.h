//
// Created by alejandro on 26/3/26.
//

#ifndef CATALOGOPRODUCTOS_CONVERTDATE_H
#define CATALOGOPRODUCTOS_CONVERTDATE_H
#include <string>

class ConvertDate {

public:
    static int toInt(const std::string& date);
    static bool isValidFormat(const std::string& date);
    static int compareDate(const std::string& date1, const std::string& date2);
};


#endif //CATALOGOPRODUCTOS_CONVERTDATE_H