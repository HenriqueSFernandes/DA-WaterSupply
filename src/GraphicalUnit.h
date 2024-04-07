/// @file GraphicalUnit.h
#ifndef WATER_SUPPLY_GRAPHICALUNIT_H
#define WATER_SUPPLY_GRAPHICALUNIT_H

#include <utility>
#include <iostream>
#include "SupplyManagement.h"
#include "../printImageToTerminal/Image/Script.hpp"
#include <map>
#include <string>

/**
 * @brief This class is responsible for displaying the map on the terminal.
 */
class GraphicalUnit {
private:
    SupplyManagement manager;
    bool isMadeira;
    map <string, pair<int, int>> cityCoordinates;
public:
    /**
     * @brief Parameterized constructor.
     * @param manager The main controller.
     */
    explicit GraphicalUnit(SupplyManagement manager, bool isMadeira) : manager(std::move(manager)),
                                                                       isMadeira(isMadeira) {
        readCities();
    }

    /**
     * @brief This method reads the coordinates of each city.
     */
    void readCities();

    /**
     * @brief This method displays the cities in the terminal.
     * @param affectedCities
     */
    void DisplayToTerminal(const vector<pair<Vertex<Location> *, int>> &affectedCities);
};


#endif //WATER_SUPPLY_GRAPHICALUNIT_H
