/// @file Menu.h
#ifndef WATER_SUPPLY_MENU_H
#define WATER_SUPPLY_MENU_H

#include <utility>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <regex>
#include "SupplyManagement.h"
#include "GraphicalUnit.h"

/**
 * @brief Class used to represent a user friendly menu.
 */
class Menu {
private:
    SupplyManagement manager;
    GraphicalUnit graphicalUnit;
    bool isMadeira;
    set<Location> disabledReservoirs;
    set<Location> disabledStations;
    set<pair<Location, Location>> disabledPipes;
public:
    /**
     * @brief Parameterized constructor.
     * @param manager Supply manager.
     */
    explicit Menu(SupplyManagement manager, GraphicalUnit graphicalUnit, bool isMadeira) : manager(std::move(manager)),
                                                                                           graphicalUnit(std::move(
                                                                                                   graphicalUnit)),
                                                                                           isMadeira(isMadeira) {}

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
     * @brief This function outputs the currently disabled reservoirs.
     */
    void printCurrentlyDisabledReservoirs();

    /**
     * @brief This function outputs the currently disabled pumping stations.
     */
    void printCurrentlyDisabledStations();

    /**
     * @brief This function outputs the currently disabled pipes.
     */
    void printCurrentlyDisabledPipes();

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

    /**
     * @brief This function clear the screen. It should work on all platforms.
     */
    static void clearScreen();

    /**
     * @brief This function print the flow to a specific city.
     */
    void printFlowToCity();

    /**
     * @brief This function prints the flow to all cities.
     */
    void printFlowToAllCities();

    /**
     * @brief This function prints the cities that are not receiving enough water.
     */
    void printWaterAvailability();

    /**
     * @brief This function adds reservoirs to the list of disabled reservoirs.
     */
    void disableReservoirs();

    /**
     * @brief This function adds reservoirs to the list of disabled pumping stations.
     */
    void disableStations();

    /**
     * @brief This function adds reservoirs to the list of disabled pipes.
     */
    void disablePipes();

    /**
     * @brief This function outputs the flow with disabled locations.
     */
    void printFlowWithDisabledLocations();

    /**
    * @brief This function outputs the balance menu
    */
    void balance();

    void checkBalance();

    void improveBalance();
};


#endif //WATER_SUPPLY_MENU_H
