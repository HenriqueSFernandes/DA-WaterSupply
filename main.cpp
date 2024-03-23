//
// Created by jose on 3/3/24.
//
#include "src/SupplyManagement.h"
#include <sstream>
#include <iostream>

int main() {
    cout << "here" << endl;
    SupplyManagement managerTester = SupplyManagement("../data/Cities.csv", "../data/Reservoir.csv",
                                                      "../data/Stations.csv", "../data/Pipes.csv");
    //MAYBE CALL OF THESE IN ONE SINGLE FUNCTION
    managerTester.createSupers();
    managerTester.readCities();
    managerTester.readReservoirs();
    managerTester.readStations();
    managerTester.readPipes();
    cout<<"TESTING 3-2"<<endl;
    set<Location> myset;
    myset.insert(Location(10,"PS_10"));
    myset.insert(Location(11,"PS_11"));
    myset.insert(Location(12,"PS_12"));
    myset.insert(Location(81,"PS_81"));
    std::stringstream ss;
   managerTester.pumpingFlow(myset);
    for (auto v: managerTester.getNetwork().getVertexSet()) {
        ss << v->getInfo().getCode() << "-> (";
        for (const auto e: v->getAdj())
            ss << (e->getDest())->getInfo().getCode() << "[Flow: " << e->getFlow() << "] ";
        ss << ") || ";
    }
    std::cout << ss.str() << std::endl << std::endl;
    cout<<"FINISH"<<endl;
    return 0;
}