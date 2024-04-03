//
// Created by jose on 3/3/24.
//
#include "src/SupplyManagement.h"
#include <sstream>
#include <iostream>

int main() {
    cout << "here" << endl;
    SupplyManagement managerTester = SupplyManagement("../data/Cities.csv", "../data/Reservoir.csv",
                                                      "../data/Stations.csv", "../data/Pipes.csv");
    //MAYBE CALL OF THESE IN ONE SINGLE FUNCTION
    managerTester.createSupers();
    managerTester.readCities();
    managerTester.readReservoirs();
    managerTester.readStations();
    managerTester.readPipes();
    managerTester.checkWaterAvailability();
    set<pair<Location, Location>> set1;
    set1.insert(make_pair(Location(35, "PS_35"), Location(8, "C_8")));
    set1.insert(make_pair(Location(15, "R_15"), Location(54, "PS_54")));
    set1.insert(make_pair(Location(36, "PS_36"), Location(12, "C_12")));
    managerTester.brokenPipeFlow(set1);
    return 0;
}