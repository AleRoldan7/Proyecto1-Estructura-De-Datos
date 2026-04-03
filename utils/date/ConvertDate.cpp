//
// Created by alejandro on 26/3/26.
//

#include "ConvertDate.h"

int ConvertDate::toInt(const std::string& date) {

    std::string temp = "";

    for (char c : date) {
        if (c != '-') {
            temp = temp + c;
        }
    }
    return toInt(temp);
}

bool ConvertDate::isValidFormat(const std::string& date) {

    if (date.length() < 10) {
        return false;
    }

    return date[4] == '-' && date[7] == '-';
}

int ConvertDate::compareDate(const std::string &date1, const std::string &date2) {

    int fecha1 = toInt(date1);
    int fecha2 = toInt(date2);

    if (fecha1 < fecha2) {
        return -1;
    }

    if (fecha1 > fecha2) {
        return 1;
    }

    return 0;
}


