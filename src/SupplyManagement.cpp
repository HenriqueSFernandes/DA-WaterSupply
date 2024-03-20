//
// Created by jose on 3/3/24.
//

#include "SupplyManagement.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <climits>

int parsePoPToInt(const std::string &str) {
    std::string cleanedStr = str;

    // Remove leading and trailing quotes
    if (!cleanedStr.empty() && cleanedStr.front() == '"')
        cleanedStr.erase(0, 1);
    if (!cleanedStr.empty() && cleanedStr.back() == '"')
        cleanedStr.pop_back();

    // Remove commas
    cleanedStr.erase(std::remove(cleanedStr.begin(), cleanedStr.end(), ','), cleanedStr.end());

    // Convert to integer
    return std::stoi(cleanedStr);
}

void SupplyManagement::createSupers() {
    Location source = Location(-1, "SOURCE");
    Location sink = Location(-2, "SINK");
    network.addVertex(source);
    network.addVertex(sink);
}

void SupplyManagement::readCities() {
    cout << "CITIES" << endl;
    string city;
    string id;
    string code;
    string demand;
    string population;
    ifstream cityCsv(cityFile);

    if (!cityCsv) {
        cerr << "Failed to open file\n";
        return;
    }

    string line;
    getline(cityCsv, line); // Ignore header

    // Iterate over every line of the file, split the line, create a new class and append that class to the list of classes.
    auto SuperSink = network.findVertex(Location(-1, "SINK"));
    while (getline(cityCsv, line)) {
        istringstream iss(line);
        getline(iss, city, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss, population, '\r');
        cout << " READ" << city << "/" << id << "/" << code << "/" << demand << "/" << population << endl;
        const string city_ = city; //just a quick fix
        Location city = Location(stoi(id), code);
        city.setType("C");
        city.setDemand(stod(demand));
        city.setMunicipality(city_);
        city.setPopulation(parsePoPToInt(population));
        network.addVertex(city);
        network.addDirectedEdgeWithResidual(city, SuperSink->getInfo(), INT_MAX);
    }

    cityCsv.close();
}

void SupplyManagement::readReservoirs() { // Reservoir,Municipality,Id,Code,Maximum Delivery (m3/sec),,
    cout << "RESERVOIRS" << endl;
    string name;
    string municipality;
    string id;
    string code;
    string limit;
    ifstream reservoirCsv(reservoirFile);

    if (!reservoirCsv) {
        cerr << "Failed to open file\n";
        return;
    }

    string line;
    getline(reservoirCsv, line); // Ignore header
    auto SuperSource = network.findVertex(Location(-1, "SOURCE"));

    // Iterate over every line of the file, split the line, create a new class and append that class to the list of classes.
    while (getline(reservoirCsv, line)) {
        istringstream iss(line);
        getline(iss, name, ',');
        getline(iss, municipality, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, limit, '\r');
        cout << " READ " << name << "/" << municipality << "/" << id << "/" << code << "/" << limit << endl;

        Location reservoir = Location(stoi(id), code);
        reservoir.setType("R");
        reservoir.setMunicipality(municipality);
        reservoir.setReservoirName(name);
        reservoir.setMaxDelivery(stod(limit));
        network.addVertex(reservoir);
        network.addDirectedEdgeWithResidual(SuperSource->getInfo(), reservoir, stod(limit));
    }

    reservoirCsv.close();
}

void SupplyManagement::readStations() { //Id,Code,,
    cout << "STATIONS" << endl;
    string id;
    string code;
    ifstream stationCsv(stationFile);

    if (!stationCsv) {
        cerr << "Failed to open file\n";
        return;
    }

    string line;
    getline(stationCsv, line); // Ignore header

    // Iterate over every line of the file, split the line, create a new class and append that class to the list of classes.
    while (getline(stationCsv, line)) {
        istringstream iss(line);
        getline(iss, id, ',');
        getline(iss, code, '\r');
        cout << " READ " << id << "/" << code << endl;
        if (code == "") break;
        Location station(stoi(id), code);
        station.setType("PS");
        network.addVertex(station);
    }

    stationCsv.close();
}


void SupplyManagement::readPipes() { //Service_Point_A,Service_Point_B,Capacity,Direction
    cout << "PIPES" << endl;
    string codeA;
    string codeB;
    string capacity;
    string directed;
    ifstream pipeCsv(pipeFile);

    if (!pipeCsv) {
        cerr << "Failed to open file\n";
        return;
    }

    string line;
    getline(pipeCsv, line); // Ignore header

    // Iterate over every line of the file, split the line, create a new class and append that class to the list of classes.
    while (getline(pipeCsv, line)) {
        istringstream iss(line);
        getline(iss, codeA, ',');
        getline(iss, codeB, ',');
        getline(iss, capacity, ',');
        getline(iss, directed, '\r');
        cout << " READ " << codeA << "/" << codeB << "/" << capacity << "/" << directed << endl;
        double cap = stod(capacity);
        auto source = network.findVertex(Location(0, codeA));
        auto dest = network.findVertex(Location(0, codeB));
        if (directed == "0") {

            network.addBidirectionalEdge(source->getInfo(), dest->getInfo(), cap);
        } else {
            network.addDirectedEdgeWithResidual(source->getInfo(), dest->getInfo(), cap);
        }

    }

    pipeCsv.close();
}

const Graph<Location> &SupplyManagement::getNetwork() const {
    return network;
}

void SupplyManagement::setNetwork(const Graph<Location> &network) {
    SupplyManagement::network = network;
}

void setUnvisited(Graph<Location> *g) {
    for (auto el: g->getVertexSet()) {
        el->setVisited(false);

    }
}

void initiateGraphFlow(Graph<Location> *g) {
    for (auto el: g->getVertexSet()) {
        for (auto edge: el->getAdj()) {
            edge->setFlow(0);
        }
    }
}

int SupplyManagement::edmondsKarp(Location source, Location target) {
    // O algorithmo de edmond karp uso bfs
    int curflow = -1;
    int res = 0;
    initiateGraphFlow(&network);
    while (curflow != 0) {
        setUnvisited(&network);
        curflow = bfsEdmond(source, target);
        res += curflow;
    }
    return res;
}

int SupplyManagement::bfsEdmond(Location source, Location target) {

    queue<Vertex<Location> *> myQueue;
    auto sourceVertex = network.findVertex(source);
    sourceVertex->setVisited(true);
    myQueue.push(sourceVertex);
    while (!myQueue.empty()) {
        auto cur = myQueue.front();
        myQueue.pop();
        if (cur->getInfo() == target) {
            if (cur->getPath() == NULL) return 0;
            else {
                int bottleNeck = cur->getPath()->getCapacity();
                auto edge = cur->getPath();
                while (edge != NULL) {
                    bottleNeck = min((int) (edge->getCapacity() - edge->getFlow()), bottleNeck);
                    edge = edge->getOrig()->getPath();
                }
                int res = bottleNeck;
                edge = cur->getPath();
                while ((edge != NULL)) {
                    edge->setFlow(edge->getFlow() + bottleNeck);
                    edge->getReverse()->setCapacity(edge->getReverse()->getCapacity() + bottleNeck);
                    edge = edge->getOrig()->getPath();
                }

                return res;
            }
        }
        for (auto edge: cur->getAdj()) {
            if (edge->getCapacity() - edge->getFlow() > 0 && !edge->getDest()->isVisited() &&
                edge->getDest()->isProcessing()) { // se ainda n exceder a capacidade e n tiver visitado eu quero visitar

                edge->getDest()->setVisited(true);
                edge->getDest()->setPath(edge);
                myQueue.push(edge->getDest());
            }

        }
    }

    return 0;
}

int SupplyManagement::FlowToCity(Location target) {
    for (auto location: network.getVertexSet()) {
        if (location->getInfo().getType() == "C" && location->getInfo().getCode() != target.getCode()) {
            location->setProcesssing(false);
        } else {
            location->setProcesssing(true);
        }
    }
    return edmondsKarp(Location(-1, "SOURCE"), Location(-1, "SINK"));

}

void SupplyManagement::resetNetwork() {
    for (auto loc: network.getVertexSet()) {
        loc->setProcesssing(true);
        loc->setVisited(false);
        for (auto edge: loc->getAdj()) {
            edge->setFlow(0);
        }
    }
}

bool SupplyManagement::checkWaterAvailability() {
    edmondsKarp(Location(-1, "SOURCE"), Location(-1, "SINK"));

}
