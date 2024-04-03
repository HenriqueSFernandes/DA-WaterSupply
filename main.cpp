//
// Created by jose on 3/3/24.
//
#include "src/SupplyManagement.h"
#include <sstream>
#include <iostream>

int main() {
    cout << "here" << endl;
    SupplyManagement managerTester = SupplyManagement("../data/Cities_Madeira.csv", "../data/Reservoirs_Madeira.csv",
                                                      "../data/Stations_Madeira.csv", "../data/Pipes_Madeira.csv");
    //MAYBE CALL OF THESE IN ONE SINGLE FUNCTION
    managerTester.createSupers();
    managerTester.readCities();
    managerTester.readReservoirs();
    managerTester.readStations();
    managerTester.readPipes();
    set<pair<Location, Location>> locations;
    locations.insert({managerTester.getNetwork().findVertex(Location(4, "PS_4"))->getInfo(),
                      managerTester.getNetwork().findVertex(Location(5, "PS_5"))->getInfo()});
    locations.insert({managerTester.getNetwork().findVertex(Location(9, "PS_9"))->getInfo(),
                      managerTester.getNetwork().findVertex(Location(10, "PS_10"))->getInfo()});
    managerTester.brokenPipeFlow(locations);
    managerTester.resetNetwork();

    return 0;
}