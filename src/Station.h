//
// Created by memechanic on 08-03-2024.
//

#ifndef STATION_H
#define STATION_H

#include "Location.h"

class Station : public Location {
public:
    Station(int id, const std::string &code);
};

#endif //STATION_H

