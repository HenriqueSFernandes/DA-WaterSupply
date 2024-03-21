/// @file Menu.h
#ifndef WATER_SUPPLY_MENU_H
#define WATER_SUPPLY_MENU_H

#include <utility>
#include <iostream>
#include "SupplyManagement.h"

/**
 * @brief Class used to represent a user friendly menu.
 */
class Menu {
private:
    SupplyManagement supplyManager;
public:
    /**
     * @brief Parameterized constructor.
     * @param manager Supply manager.
     */
    explicit Menu(SupplyManagement manager) : supplyManager(std::move(manager)) {}

    /**
     * @brief Main menu.
     */
    void start();
};


#endif //WATER_SUPPLY_MENU_H
