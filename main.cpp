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
    managerTester.checkWaterAvailability();
    set<Location> reservoirs;
    reservoirs.insert(Location(11, "R_11"));
    reservoirs.insert(Location(10, "R_10"));
    managerTester.brokenReservoirFlow(reservoirs);
    return 0;
}