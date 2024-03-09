//
// Created by jose on 3/3/24.
//
#include "src/SupplyManagement.h"
#include <sstream>
#include <iostream>
int main() {
    cout<<"here"<<endl;
    SupplyManagement managerTester=SupplyManagement("../data/Cities_Madeira.csv","../data/Reservoirs_Madeira.csv","../data/Stations_Madeira.csv","../data/Pipes_Madeira.csv");
    //MAYBE CALL OF THESE IN ONE SINGLE FUNCTION
    managerTester.createSupers();
    managerTester.readCities();
    managerTester.readReservoirs();
    managerTester.readStations();
    managerTester.readPipes();
    for(auto vertex :  managerTester.getNetwork().getVertexSet()){
        cout<<" VERTEX "<<vertex->getInfo().getCode()<<endl;
        for( auto edge : vertex->getAdj()){
            cout<<" HAS AN EDGE TO"<<edge->getDest()->getInfo().getCode()<< " OF CAPACITY"<<edge->getCapacity()<<endl;
        }
    }
    cout<<"DOING EDMOND KARP"<<endl;
    std::stringstream ss;
    cout << managerTester.edmondsKarp(Location(-1,"SOURCE"), Location(-1,"SINK"));
    for (auto v : managerTester.getNetwork().getVertexSet()) {
        ss << v->getInfo().getCode() << "-> (";
        for (const auto e : v->getAdj())
            ss << (e->getDest())->getInfo().getCode() << "[Flow: " << e->getFlow() << "] ";
        ss << ") || ";
    }
    std::cout << ss.str() << std::endl << std::endl;


    return 0;
}