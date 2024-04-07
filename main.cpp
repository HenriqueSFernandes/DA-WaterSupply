#include "src/SupplyManagement.h"
#include "src/Menu.h"
#include <iostream>
#include "src/GraphicalUnit.h"

bool chooseCSV() {
    string option;
    while (true) {
        cout << "Which dataset to you want to use?\n";
        cout << "1) Madeira\n2) Mainland\n0) Exit\n";
        cin >> option;
        if (option == "1") {
            return true;
        } else if (option == "2") {
            return false;
        } else if (option == "0") {
            exit(0);
        } else {
            Menu::setColorRed();
            cout << "Invalid option, please choose again.\n";
            Menu::resetColor();
        }
    }
}

int main() {
    Menu::clearScreen();
    bool useMadeiraCSV = chooseCSV();

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
    manager.copy();
    Menu menu(manager, graphicalUnit, useMadeiraCSV);
    menu.start();

    return 0;
}
