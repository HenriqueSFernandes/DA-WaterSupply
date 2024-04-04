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
    static int askForAValidInt();

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
};


#endif //WATER_SUPPLY_MENU_H
