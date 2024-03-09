//
// Created by jose on 3/3/24.
//

#ifndef SUPPLYMANAGEMENT_H
#define SUPPLYMANAGEMENT_H
#include "Graph.h"
#include "Location.h"

#include "City.h"
#include "Reservoir.h"
#include "Station.h"
using namespace std;


class SupplyManagement {
public:
    SupplyManagement(const string &city_file, const string &reservoir_file, const string &station_file,
        const string &pipe_file)
        : cityFile(city_file),
          reservoirFile(reservoir_file),
          stationFile(station_file),
          pipeFile(pipe_file) {
    }
    void createSupers();
    void readCities();
    void readReservoirs();
    void readStations();
    void readPipes();
    void assembleGraph();
    int edmondsKarp( Location source, Location target);
    int bfsEdmond(Location source, Location target);

    private:
    Graph<Location> network;
public:
    const Graph<Location> &getNetwork() const;

    void setNetwork(const Graph<Location> &network);

private:
    string cityFile;
    string reservoirFile;
    string stationFile;
    string pipeFile;

};



#endif //SUPPLYMANAGEMENT_H
