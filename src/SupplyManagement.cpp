//
// Created by jose on 3/3/24.
//

#include "SupplyManagement.h"
#include <fstream>
#include <sstream>
#include <iomanip>

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
    while (getline(cityCsv, line)) {
        istringstream iss(line);
        getline(iss, city, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss, population, '\r');
        cout<<" READ"<<city<<"/"<<id<<"/"<<code<<"/"<<demand<<"/"<<population<<endl;
        Location location(code); //DUMMY VALUE FOR TESTING WILL USE CITY OBJECT IN FUTURE
        network.addVertex(location);
    }

    cityCsv.close();
}
void SupplyManagement::readReservoirs() { // Reservoir,Municipality,Id,Code,Maximum Delivery (m3/sec),,
    cout<<"RESERVOIRS"<<endl;
    string reservoir;
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

    // Iterate over every line of the file, split the line, create a new class and append that class to the list of classes.
    while (getline(reservoirCsv, line)) {
        istringstream iss(line);
        getline(iss, reservoir, ',');
        getline(iss, municipality, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, limit, ',');
        cout<<" READ "<<reservoir<<"/"<<municipality<<"/"<<id<<"/"<<code<<"/"<<limit<<endl;
        Location location(code); //DUMMY VALUE FOR TESTING WILL USE CITY OBJECT IN FUTURE
        network.addVertex(location);
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
        Location location(code); //DUMMY VALUE FOR TESTING WILL USE CITY OBJECT IN FUTURE
        network.addVertex(location);
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
        if(directed=="0") {
            network.addBidirectionalEdge(codeA,codeB,cap);
        }else {
            network.addDirectedEdgeWithResidual(codeA,codeB,cap);
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

