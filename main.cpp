#include "src/SupplyManagement.h"
#include "src/Menu.h"
#include <sstream>
#include <iostream>
#include "src/GraphicalUnit.h"

int main() {

    bool useMadeiraCSV = true;

    string cityFile = "../data/Cities.csv";
    string reservoirFile = "../data/Reservoir.csv";
    string stationFile = "../data/Stations.csv";
    string pipeFile = "../data/Pipes.csv";
    if (useMadeiraCSV) {
        cityFile = "../data/Cities_Madeira.csv";
        reservoirFile = "../data/Reservoirs_Madeira.csv";
        stationFile = "../data/Stations_Madeira.csv";
        pipeFile = "../data/Pipes_Madeira.csv";
    }

    SupplyManagement manager = SupplyManagement(cityFile, reservoirFile, stationFile, pipeFile);

    manager.createSupers();
    manager.readCities();
    manager.readReservoirs();
    manager.readStations();
    manager.readPipes();
    GraphicalUnit graphicalUnit;

    Menu menu(manager, graphicalUnit, useMadeiraCSV);
    menu.start();


    return 0;
}