#include "src/SupplyManagement.h"
#include "src/Menu.h"
#include <sstream>
#include <iostream>

int main() {
    SupplyManagement manager = SupplyManagement("../data/Cities_Madeira.csv", "../data/Reservoirs_Madeira.csv",
                                                "../data/Stations_Madeira.csv", "../data/Pipes_Madeira.csv");
    manager.createSupers();
    manager.readCities();
    manager.readReservoirs();
    manager.readStations();
    manager.readPipes();
    Menu menu(manager);
    menu.start();

    return 0;
}