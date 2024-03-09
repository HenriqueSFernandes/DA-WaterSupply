//
// Created by jose on 3/3/24.
//

#include "SupplyManagement.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <climits>
#include "SpecialLocation.h"

int parsePoPToInt(const std::string& str) {
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
    SpecialLocation source=SpecialLocation(-1, "SOURCE");
    SpecialLocation sink=SpecialLocation(-1, "SINK");
    network.addVertex(source);
    network.addVertex(sink);
}

void SupplyManagement::readCities() {
    cout<<"CITIES"<<endl;
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
    auto SuperSink=network.findVertex(Location(-1,"SINK"));
    while (getline(cityCsv, line)) {
        istringstream iss(line);
        getline(iss, city, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss, population, '\r');
        cout<<" READ"<<city<<"/"<<id<<"/"<<code<<"/"<<demand<<"/"<<population<<endl;
        const string city_=city; //just a quick fix
        City city=City(stoi(id),code,city_,stod(demand),parsePoPToInt(population));

        network.addVertex(city);
        network.addDirectedEdgeWithResidual(city,SuperSink->getInfo(),INT_MAX);
    }

    cityCsv.close();
}
void SupplyManagement::readReservoirs() { // Reservoir,Municipality,Id,Code,Maximum Delivery (m3/sec),,
    cout<<"RESERVOIRS"<<endl;
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
    auto SuperSource=network.findVertex(Location(-1,"SOURCE"));

    // Iterate over every line of the file, split the line, create a new class and append that class to the list of classes.
    while (getline(reservoirCsv, line)) {
        istringstream iss(line);
        getline(iss, name, ',');
        getline(iss, municipality, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, limit, ',');
        cout<<" READ "<<name<<"/"<<municipality<<"/"<<id<<"/"<<code<<"/"<<limit<<endl;

        Reservoir reservoir= Reservoir(stoi(id),code,name,municipality,stod(limit));
        network.addVertex(reservoir);
        network.addDirectedEdgeWithResidual(SuperSource->getInfo(),reservoir,INT_MAX);
    }

    reservoirCsv.close();
}
void SupplyManagement::readStations() { //Id,Code,,
    cout<<"STATIONS"<<endl;
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
        cout<<" READ "<<id<<"/"<<code<<endl;
        if(code=="") break;
        Station station(stoi(id),code);
        network.addVertex(station);
    }

    stationCsv.close();
}


void SupplyManagement::readPipes() { //Service_Point_A,Service_Point_B,Capacity,Direction
    cout<<"PIPES"<<endl;
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
        cout<<" READ "<<codeA<<"/"<<codeB<<"/"<<capacity<<"/"<<directed<<endl;
        double cap=stod(capacity);
        auto source=network.findVertex(Location(0,codeA));
        auto dest=network.findVertex(Location(0,codeB));
        if(directed=="0") {

            network.addBidirectionalEdge(source->getInfo(),dest->getInfo(),cap);
        }else {
            network.addDirectedEdgeWithResidual(source->getInfo(),dest->getInfo(),cap);
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

