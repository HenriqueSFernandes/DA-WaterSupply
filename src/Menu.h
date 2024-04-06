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
    SupplyManagement manager;
    set<Location> disabledReservoirs;
    set<Location> disabledStations;
    set<pair<Location, Location>> disabledPipes;
public:
    /**
     * @brief Parameterized constructor.
     * @param manager Supply manager.
     */
    explicit Menu(SupplyManagement manager) : manager(std::move(manager)) {}

    /**
     * @brief Loops until the input is a valid integer.
     * @return A valid integer.
     */
    static int getValidInt();

    /**
     * @brief Sets the terminal text color to red.
     */
    static void setColorRed();

    /**
     * @brief Sets the terminal text color to cyan.
     */
    static void setColorCyan();

    /**
     * @brief Reset the terminal text color to default.
     */
    static void resetColor();

    /**
     * @brief Main menu.
     */
    void start();

    /**
     * @brief Menu for analysing details of the network, like flow to the cities and if the demand is met.
     */
    void analyseMenu();

    /**
     * @brief Menu for enabling or disabling locations.F
     */
    void disableLocationsMenu();
};


#endif //WATER_SUPPLY_MENU_H
