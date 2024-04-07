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
    managerTester.visitByDefault();
    managerTester.copy();
    managerTester.resetNetwork();
    cout<<"DOING EDMOND KARP"<<endl;
    std::stringstream ss;
    managerTester.resetNetwork();

    double avg;
    double var;
    double  maxi;
    for( auto ver : managerTester.getNetwork().getVertexSet()){
        for(auto edge : ver->getAdj()){
            cout<<edge->getOrig()->getInfo().getCode()<<" "<<edge->getDest()->getInfo().getCode()<<" flow "<<edge->getFlow()<<" cap "<<edge->getCapacity()<<endl;
        }
    }
    cout<<"PREV STATS"<<endl;
    cout << managerTester.edmondsKarp(Location(-1,"SOURCE"), Location(-1,"SINK"));
    managerTester.getNetworkStats(avg, var, maxi);
    cout<<"AVG IS"<<avg<<" VAR IS "<< var<<" MAX IS "<<maxi<<endl;
    cout<<"NEXT"<<endl;
    managerTester.resetNetwork();
    cout<<"DOING EDMOND KARP"<<endl;
    managerTester.resetNetwork();

    cout<< managerTester.edmondsKarpBalance(Location(-1,"SOURCE"), Location(-1,"SINK"));
    managerTester.getNetworkStats(avg, var, maxi);
    cout<<"AVG IS"<<avg<<" VAR IS "<< var<<" MAX IS "<<maxi<<endl;



    return 0;
}