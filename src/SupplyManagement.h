/// @file SupplyManagement.h
#ifndef SUPPLYMANAGEMENT_H
#define SUPPLYMANAGEMENT_H

#include <utility>
#include "Graph.h"
#include "Location.h"
#include <set>

using namespace std;

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
    int FlowToCity(Location target);

    /**
     * @brief Resets the network by setting the processing to true and the visited to false.
     */
    void resetNetwork();

    /**
     * @brief Checks if the cities are receiving enough water.
     * @return A vector with the cities that are not receiving enough water.
     */
    vector<Location> checkWaterAvailability();

    /**
     * @brief Removes one or more reservoirs by setting their processing attribute to false.
     * @param reservoir
     */
    void removeReservoirs(set<Location> PumpingStations );

    /**
     * @brief This function evaluates if the cities are receiving enough water if one or more reservoirs are removed.
     * @param reservoir The reservoir to be removed.
     * @return The difference in flow after the removal.
     */
    int brokenReservoirFlow(set<Location> reservoirs);

    /**
     * @brief This function evaluates if the cities are receiving enough water if one or more pipes are removed.
     * @param pipe_ends The pipes to be removed.
     * @return The difference in flow after the removal.
     */
    int brokenPipeFlow(const set<pair<Location, Location>> &pipe_ends);

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
    void removePipes(const set<pair<Location, Location>> &pipe_ends);

    /**
     * @brief This function evaluates if the cities are receiving enough water if one or more pumping stations are removed.
     * @param PumpingStations The pumping stations to remove.
     * @return The difference in flow after removing the pumping stations.
     */
    int pumpingFlow(set<Location> PumpingStations);

private:
    Graph<Location> network;
    string cityFile;
    string reservoirFile;
    string stationFile;
    string pipeFile;
};


#endif //SUPPLYMANAGEMENT_H
