/// @file SupplyManagement.h
#ifndef SUPPLYMANAGEMENT_H
#define SUPPLYMANAGEMENT_H

#include <utility>
#include "Graph.h"
#include "Location.h"
#include <set>
#include <ostream>

using namespace std;

/**
 * @brief This struct represents a city with its flow.
 */
struct cityFlow {
    string name;
    string code;
    int flow;

    friend ostream &operator<<(ostream &os, const cityFlow &flow);
};

/**
 * @brief The main class of the program. It is responsible for running all the algorithms and controlling the network.
 */
class SupplyManagement {
public:
    /**
     * @brief Parameterized constructor.
     * @param city_file The path for the file with the cities.
     * @param reservoir_file The path for the file with the reservoirs.
     * @param station_file The path for the file with the pumping stations.
     * @param pipe_file The path for the file with the pipes.
     */
    SupplyManagement(string city_file, string reservoir_file, string station_file,
                     string pipe_file)
            : cityFile(std::move(city_file)),
              reservoirFile(std::move(reservoir_file)),
              stationFile(std::move(station_file)),
              pipeFile(std::move(pipe_file)) {
    }

    /**
     * @brief Creates the super source and super sink.
     */
    void createSupers();

    /**
     * @brief Reads the cities from the file.
     */
    void readCities();

    /**
     * @brief Reads the reservoirs from the file.
     */
    void readReservoirs();

    /**
     * @brief Reads the pumping stations from the file.
     */
    void readStations();

    /**
     * @brief Reads the pipes from the file.
     */
    void readPipes();

    /**
     * @brief The Edmonds Karp algorithms for finding the max flow between 2 locations.
     * @param source The source location.
     * @param target The target location.
     * @return The flow between the 2 locations.
     */
    int edmondsKarp(Location source, Location target);

    /**
     * @brief Auxiliary BFS function that is used in the edmondsKarp() function.
     * @param source The source location.
     * @param target The target location.
     * @return The flow between the 2 locations.
     */
    int bfsEdmond(Location source, Location target);

    /**
     * @brief This method calculates the theoretical maximum flow to a specific city, ignoring the other cities.
     * It does so by setting every other city processing attribute to false, and the Edmonds Karp algorithm only calculates the flow for a city with the processing attribute as true.
     * By doing this, the algorithm ignores the other cities and calculates the maximum theoretical flow to the given city.
     * @param target The target city.
     * @return The flow to the given city.
     */
    cityFlow flowToCity(Location target);

    /**
     * @brief This method calculates the actual flow to all cities.
     * @return The flow to all cities and the total flow.
     */
    pair<vector<cityFlow>, int> flowToAllCities();

    /**
     * @brief Resets the network by setting the processing to true and the visited to false.
     */
    void resetNetwork();

    /**
     * @brief Checks if the cities are receiving enough water.
     * @return A vector with the cities that are not receiving enough water.
     */
    vector<pair<Location, int>> checkWaterAvailability();

    /**
     * @brief Removes one or more reservoirs by setting their processing attribute to false.
     * @param reservoir
     */
    void removeReservoirs(set<Location> PumpingStations);

    /**
     * @brief This function calculates the impact of removing reservoirs, pumping stations and pipes on the flow of the network.
     * @param disabledReservoirs The disabled reservoirs.
     * @param disabledStations The disabled pumping stations.
     * @param disabledPipes The disabled pipes.
     * Additional information about the return value:
     * It's a pair. The first element is another pair with the old flow and the new flow. The second element is a vector of pairs. The first element is a pointer to the vertex, an the second is the original flow.
     * @return The global flow before and after disabling the locations and the affected cities.
     */
    pair<pair<int, int>, vector<pair<Vertex<Location> *, int>>>
    flowWithDisabledLocations(const set<Location> &disabledReservoirs, const set<Location> &disabledStations,
                              const set<pair<Location, Location>> &disabledPipes);

    /**
     * @brief Network getter.
     * @return The graph.
     */
    [[nodiscard]] const Graph<Location> &getNetwork() const;

    /**
     * @brief Network setter.
     * @param network The new network.
     */
    void setNetwork(const Graph<Location> &network);

    /**
     * @brief Removes a pumping station by setting its processing attribute to false.
     * @param PumpingStations A set of pumping stations.
     */
    void removePumpingStations(set<Location> PumpingStations);

    /**
     * @brief Removes a pipe by setting its selected attribute to false.
     * @param pipe_ends The pipe to be removed.
     */
    void removePipes(const set<pair<Location, Location>>

                     &pipe_ends);

private:
    Graph<Location> network;
    string cityFile;
    string reservoirFile;
    string stationFile;
    string pipeFile;
};


#endif //SUPPLYMANAGEMENT_H
