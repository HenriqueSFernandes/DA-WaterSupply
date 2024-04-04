#include "SupplyManagement.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>

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
    cout << "Loading cities..." << endl;
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
        const string city_ = city; //just a quick fix
        Location city = Location(stoi(id), code);
        city.setType("C");
        city.setDemand(stod(demand));
        city.setMunicipality(city_);
        city.setPopulation(parsePoPToInt(population));
        network.addVertex(city);
        network.addDirectedEdgeWithResidual(city, SuperSink->getInfo(), stod(demand));
    }

    cityCsv.close();
}

void SupplyManagement::readReservoirs() { // Reservoir,Municipality,Id,Code,Maximum Delivery (m3/sec),,
    cout << "Loading reservoirs..." << endl;
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
    cout << "Loading pumping stations..." << endl;
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
        if (code == "") break;
        Location station(stoi(id), code);
        station.setType("PS");
        network.addVertex(station);
    }

    stationCsv.close();
}


void SupplyManagement::readPipes() { //Service_Point_A,Service_Point_B,Capacity,Direction
    cout << "Loading pipes..." << endl;
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
                edge->getDest()->isProcessing() &&
                edge->isSelected()) { // se ainda n exceder a capacidade e n tiver visitado eu quero visitar

                edge->getDest()->setVisited(true);
                edge->getDest()->setPath(edge);
                myQueue.push(edge->getDest());
            }
        }
    }
    return 0;
}

cityFlow SupplyManagement::flowToCity(Location target) {
    resetNetwork();
    bool targetFound = false;
    string cityName;
    for (auto location: network.getVertexSet()) {
        if (location->getInfo().getType() == "C" && location->getInfo().getCode() != target.getCode()) {
            location->setProcesssing(false);
        } else if (location->getInfo().getType() == "C" && location->getInfo().getCode() == target.getCode()) {
            location->setProcesssing(true);
            targetFound = true;
            cityName = location->getInfo().getMunicipality();
        } else {
            location->setProcesssing(true);
        }
    }
    if (!targetFound) {
        throw invalid_argument("City not found!");
    }
    return {cityName, target.getCode(), edmondsKarp(Location(-1, "SOURCE"), Location(-1, "SINK"))};
}

void SupplyManagement::resetNetwork() {
    for (auto loc: network.getVertexSet()) {
        loc->setProcesssing(true);
        loc->setVisited(false);
        for (auto edge: loc->getAdj()) {
            edge->setFlow(0);
            edge->setSelected(true);
        }
    }
}

void SupplyManagement::removePumpingStations(set<Location> PumpingStations) {
    if (PumpingStations.empty()) return;
    for (auto ver: network.getVertexSet()) {
        if (PumpingStations.find(ver->getInfo()) != PumpingStations.end()) {

            ver->setProcesssing(false);
        }
    }
}


int SupplyManagement::pumpingFlow(set<Location> PumpingStations) {
    resetNetwork();
    int prev = edmondsKarp(Location(-1, "SOURCE"), Location(-1, "SINK"));
    map<string, int> cityValue;
    for (auto v: network.getVertexSet()) {
        string s;
        s = v->getInfo().getCode();
        for (auto e: v->getAdj()) {
            if (v->getInfo().getType() == "C" && e->getDest()->getInfo().getCode() == "SINK") {
                cityValue[s] = e->getFlow();
            }

        }
    }
    resetNetwork();
    removePumpingStations(PumpingStations);
    int res = edmondsKarp(Location(-1, "SOURCE"), Location(-1, "SINK"));
    for (auto v: network.getVertexSet()) {
        string city;
        city = v->getInfo().getCode();
        for (auto e: v->getAdj()) {
            if (v->getInfo().getType() == "C" && e->getDest()->getInfo().getCode() == "SINK") {
                if (cityValue[city] > e->getFlow()) {
                    cout << "THERE WAS A LOSS OF " << cityValue[city] - e->getFlow() << " IN CITY "
                         << v->getInfo().getMunicipality() << endl;
                }

            };
        }
    }
    int dif = prev - res;
    cout << "TOTAL " << res << " DIFFERENCE " << dif << endl;


    return res;
}

vector<pair<Location, int>> SupplyManagement::checkWaterAvailability() {
    resetNetwork();
    edmondsKarp(Location(-1, "SOURCE"), Location(-1, "SINK"));
    vector<pair<Location, int>> citiesWithMoreDemandThanFlow;
    for (Vertex<Location> *location: network.getVertexSet()) {
        if (location->getInfo().getType() == "C") {
            int flow = (int) location->getAdj()[0]->getFlow();
            if (location->getInfo().getDemand() > flow) {
                citiesWithMoreDemandThanFlow.emplace_back(location->getInfo(), flow);
            }
        }
    }
    return citiesWithMoreDemandThanFlow;
}

void SupplyManagement::removeReservoirs(set<Location> reservoirs) {
    if (reservoirs.empty()) return;
    for (auto ver: network.getVertexSet()) {
        if (reservoirs.find(ver->getInfo()) != reservoirs.end()) {
            ver->setProcesssing(false);
        }
    }
}

int SupplyManagement::brokenReservoirFlow(set<Location> reservoirs) {
    resetNetwork();
    int prev = edmondsKarp(Location(-1, "SOURCE"), Location(-1, "SINK"));
    map<string, int> cityValue;
    for (auto v: network.getVertexSet()) {
        string s;
        s = v->getInfo().getCode();
        // TODO change this to adj[0]
        for (auto e: v->getAdj()) {
            if (v->getInfo().getType() == "C" && e->getDest()->getInfo().getCode() == "SINK") {
                cityValue[s] = e->getFlow();
            }
        }
    }
    resetNetwork();
    removeReservoirs(reservoirs);
    int res = edmondsKarp(Location(-1, "SOURCE"), Location(-1, "SINK"));
    for (auto v: network.getVertexSet()) {
        string city;
        city = v->getInfo().getCode();
        for (auto e: v->getAdj()) {
            if (v->getInfo().getType() == "C" && e->getDest()->getInfo().getCode() == "SINK") {
                if (cityValue[city] > e->getFlow()) {
                    if (v->getInfo().getDemand() <= e->getFlow())
                        cout << "THERE WAS A LOSS OF " << cityValue[city] - e->getFlow() << " IN CITY "
                             << v->getInfo().getMunicipality() << " BUT IT'S STILL "
                             << e->getFlow() - v->getInfo().getDemand() << " ABOVE DEMAND" << endl;
                    else
                        cout << "THERE WAS A LOSS OF " << cityValue[city] - e->getFlow() << " IN CITY "
                             << v->getInfo().getMunicipality() << " WHICH NOW HAS A DEFICIT OF "
                             << v->getInfo().getDemand() - e->getFlow() << endl;
                }
            };
        }
    }
    int dif = prev - res;
    cout << "TOTAL " << res << " DIFFERENCE " << dif << endl;
    return res;
}

void SupplyManagement::removePipes(const set<pair<Location, Location>> &pipe_ends) {
    if (pipe_ends.empty()) return;
    for (const auto &ends: pipe_ends) {
        Location orig = ends.first;
        Location dest = ends.second;
        for (auto ver: network.getVertexSet()) {
            for (auto edge: ver->getAdj()) {
                if (edge->getOrig()->getInfo() == orig && edge->getDest()->getInfo() == dest) {
                    edge->setSelected(false);
                    edge->getReverse()->setSelected(false);
                }
            }
        }
    }
}

int SupplyManagement::brokenPipeFlow(const set<pair<Location, Location>> &pipe_ends) {
    resetNetwork();
    int prev = edmondsKarp(Location(-1, "SOURCE"), Location(-1, "SINK"));
    map<string, int> cityValue;
    for (auto v: network.getVertexSet()) {
        string s;
        s = v->getInfo().getCode();
        for (auto e: v->getAdj()) {
            if (v->getInfo().getType() == "C" && e->getDest()->getInfo().getCode() == "SINK") {
                cityValue[s] = e->getFlow();
            }

        }
    }
    resetNetwork();
    removePipes(pipe_ends);

    int res = edmondsKarp(Location(-1, "SOURCE"), Location(-1, "SINK"));
    for (auto v: network.getVertexSet()) {
        string city;
        city = v->getInfo().getCode();
        for (auto e: v->getAdj()) {
            if (v->getInfo().getType() == "C" && e->getDest()->getInfo().getCode() == "SINK") {
                if (cityValue[city] > e->getFlow()) {
                    if (v->getInfo().getDemand() <= e->getFlow())
                        cout << "THERE WAS A LOSS OF " << cityValue[city] - e->getFlow() << " IN CITY "
                             << v->getInfo().getMunicipality() << " BUT IT'S STILL "
                             << e->getFlow() - v->getInfo().getDemand() << " ABOVE DEMAND" << endl;
                    else
                        cout << "THERE WAS A LOSS OF " << cityValue[city] - e->getFlow() << " IN CITY "
                             << v->getInfo().getMunicipality() << " WHICH NOW HAS A DEFICIT OF "
                             << v->getInfo().getDemand() - e->getFlow() << endl;
                }

            };
        }
    }
    int dif = prev - res;
    cout << "TOTAL " << res << " DIFFERENCE " << dif << endl;


    return res;
}

pair<vector<cityFlow>, int> SupplyManagement::flowToAllCities() {
    resetNetwork();
    edmondsKarp(Location(-1, "SOURCE"), Location(-1, "SINK"));
    int totalFlow = 0;
    vector<cityFlow> cities;
    for (Vertex<Location> *location: getNetwork().getVertexSet()) {
        if (location->getInfo().getType() == "C") {
            int flow = (int) location->getAdj()[0]->getFlow();
            cities.push_back({location->getInfo().getMunicipality(), location->getInfo().getCode(),
                              flow});
            totalFlow += flow;
        }
    }
    return {cities, totalFlow};
}

pair<pair<int, int>, vector<pair<Vertex<Location> *, int>>>
SupplyManagement::flowWithDisabledLocations(const set<Location> &disabledReservoirs,
                                            const set<Location> &disabledStations,
                                            const set<pair<Location, Location>> &disabledPipes) {
    resetNetwork();
    int previousGlobalFlow = edmondsKarp(Location(-1, "SOURCE"), Location(-1, "SINK"));
    map<string, int> cities;
    vector<pair<Vertex<Location> *, int>> impactedCities;
    for (Vertex<Location> *vertex: network.getVertexSet()) {
        if (vertex->getInfo().getType() == "C") {
            cities[vertex->getInfo().getCode()] = (int) vertex->getAdj()[0]->getFlow();
        }
    }
    resetNetwork();
    removeReservoirs(disabledReservoirs);
    removePumpingStations(disabledStations);
    removePipes(disabledPipes);
    int newGlobalFlow = edmondsKarp(Location(-1, "SOURCE"), Location(-1, "SINK"));
    for (Vertex<Location> *vertex: network.getVertexSet()) {
        if (vertex->getInfo().getType() == "C") {
            int newFlow = (int) vertex->getAdj()[0]->getFlow();
            int oldFlow = cities[vertex->getInfo().getCode()];
            if (newFlow < oldFlow) {
                impactedCities.emplace_back(vertex, oldFlow);
            }
        }
    }
    return {{previousGlobalFlow, newGlobalFlow}, impactedCities};
}

ostream &operator<<(ostream &os, const cityFlow &flow) {
    os << "\033[0;36m" << flow.name << "\033[0m" << ", with code " << flow.code << ", has a flow of "
       << "\033[0;36m"
       << flow.flow << "\033[0m" << ".";
    return os;
}
