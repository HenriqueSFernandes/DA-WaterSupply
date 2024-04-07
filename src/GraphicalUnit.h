//
// Created by jose on 4/6/24.
//

#ifndef WATER_SUPPLY_GRAPHICALUNIT_H
#define WATER_SUPPLY_GRAPHICALUNIT_H

#include <utility>
#include <iostream>
#include "SupplyManagement.h"
#include "../printImageToTerminal/Image/Script.hpp"
#include <map>
#include <string>
class GraphicalUnit {
private:
    SupplyManagement manager;
    map<string ,pair<int, int>> cityCoordinates;
public:
    void readCities();
    GraphicalUnit(const SupplyManagement& manager) : manager(manager) {
        readCities();
    }
    void DisplayToTerminal(vector<pair<Vertex<Location> *, int>> affectedCities);
};



#endif //WATER_SUPPLY_GRAPHICALUNIT_H
