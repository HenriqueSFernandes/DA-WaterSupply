//
// Created by jose on 3/3/24.
//

#ifndef SUPPLYMANAGEMENT_H
#define SUPPLYMANAGEMENT_H

#include <utility>
#include "Graph.h"
#include "Location.h"

using namespace std;


class SupplyManagement {
public:
    SupplyManagement(string city_file, string reservoir_file, string station_file,
                     string pipe_file)
            : cityFile(std::move(city_file)),
              reservoirFile(std::move(reservoir_file)),
              stationFile(std::move(station_file)),
              pipeFile(std::move(pipe_file)) {
    }

    void createSupers();

    void readCities();

    void readReservoirs();

    void readStations();

    void readPipes();

    void assembleGraph();

    int edmondsKarp(Location source, Location target);

    int bfsEdmond(Location source, Location target);

    int FlowToCity(Location target);

    void resetNetwork();

    vector<Location> checkWaterAvailability();

    void removeReservoir(const Location& reservoir);

    int brokenReservoirFlow(const Location& reservoir);

    const Graph<Location> &getNetwork() const;

    void setNetwork(const Graph<Location> &network);

private:
    Graph<Location> network;
    string cityFile;
    string reservoirFile;
    string stationFile;
    string pipeFile;

};


#endif //SUPPLYMANAGEMENT_H
