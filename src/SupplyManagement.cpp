//
// Created by jose on 3/3/24.
//

#include "SupplyManagement.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <climits>
#include "SpecialLocation.h"

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
    auto *sourcePtr = new SpecialLocation(-1, "SOURCE");
    auto *sinkPtr = new SpecialLocation(-1, "SINK");
    network.addVertex(sourcePtr);
    network.addVertex(sinkPtr);
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
    Location sink = Location(-1, "SINK");
    Vertex<Location *> *SuperSink = network.findVertex(&sink);
    while (getline(cityCsv, line)) {
        istringstream iss(line);
        getline(iss, city, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss, population, '\r');
        cout << " READ" << city << "/" << id << "/" << code << "/" << demand << "/" << population << endl;
        const string city_ = city; //just a quick fix
        City *city = new City(stoi(id), code, city_, stod(demand), parsePoPToInt(population));

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
    Location source = Location(-1, "SOURCE");
    Vertex<Location *> *SuperSource = network.findVertex(&source);

    // Iterate over every line of the file, split the line, create a new class and append that class to the list of classes.
    while (getline(reservoirCsv, line)) {
        istringstream iss(line);
        getline(iss, name, ',');
        getline(iss, municipality, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, limit, ',');
        cout << " READ " << name << "/" << municipality << "/" << id << "/" << code << "/" << limit << endl;

        Reservoir *reservoir = new Reservoir(stoi(id), code, name, municipality, stod(limit));
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
        getline(iss, code, ',');
        cout << " READ " << id << "/" << code << endl;
        if (code == "") break;
        Station *station = new Station(stoi(id), code);
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
        Location sourceSearcher = Location(0, codeA);
        Location destSearcher = Location(0, codeB);
        auto source = network.findVertex(&sourceSearcher);
        auto dest = network.findVertex(&destSearcher);
        if (directed == "0") {
            network.addBidirectionalEdge(source->getInfo(), dest->getInfo(), cap);
        } else {
            network.addDirectedEdgeWithResidual(source->getInfo(), dest->getInfo(), cap);
        }
    }

    pipeCsv.close();
}

const Graph<Location *> &SupplyManagement::getNetwork() const {
    return network;
}

void SupplyManagement::setNetwork(const Graph<Location *> &network) {
    SupplyManagement::network = network;
}

void setUnvisited(Graph<Location *> *g) {
    for (auto el: g->getVertexSet()) {
        el->setVisited(false);
    }
}

void initiateGraphFlow(Graph<Location *> *g) {
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

    queue<Vertex<Location *> *> myQueue;
    auto sourceVertex = network.findVertex(&source);
    sourceVertex->setVisited(true);
    myQueue.push(sourceVertex);
    while (!myQueue.empty()) {
        auto cur = myQueue.front();
        myQueue.pop();
        if (*(cur->getInfo()) == target) {
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
            if (edge->getCapacity() - edge->getFlow() > 0 &&
                !edge->getDest()->isVisited()) { // se ainda n exceder a capacidade e n tiver visitado eu quero visitar
                edge->getDest()->setVisited(true);
                edge->getDest()->setPath(edge);
                myQueue.push(edge->getDest());
            }

        }
    }

    return 0;
}

SupplyManagement::~SupplyManagement() {
    for (Vertex<Location *> *vertex: network.getVertexSet()) {
        // Delete all outgoing edges from the vertex
        for (Edge<Location *> *edge: vertex->getAdj()) {
            delete edge;
        }
        // Delete the Location object associated with the vertex
        delete vertex->getInfo();
        // Delete the vertex itself
        delete vertex;
    }
}

