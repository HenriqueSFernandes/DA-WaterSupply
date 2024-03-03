//
// Created by jose on 3/3/24.
//
#include "SupplyManagement.h"

int main() {
    SupplyManagement managerTester=SupplyManagement("data/Cities_Madeira.csv","data/Reservoirs_Madeira.csv","data/Stations_Madeira.csv","data/Pipes_Madeira.csv");
    managerTester.readCities();
    managerTester.readReservoirs();
    managerTester.readStations();
    managerTester.readPipes();


    return 0;
}