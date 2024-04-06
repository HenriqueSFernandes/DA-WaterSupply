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
    managerTester.resetNetwork();
    managerTester.edmondsKarp(Location(-1, "SOURCE"), Location(-1, "SINK"));

    double avg;
    double var;
    double  maxi;
    cout<<"PREV STATS"<<endl;
    managerTester.getNetworkStats(avg, var, maxi);
    cout<<"AVG IS"<<avg<<" VAR IS "<< var<<" MAX IS "<<maxi<<endl;
    cout<<"NEXT"<<endl;
    struct VertexComparator {
        bool operator()( Vertex<Location>* lhs,  Vertex<Location>* rhs) const {
            double var1=0;
            double var2=0;
            for( auto  edge : lhs->getAdj()){
                if( edge->getDest()->getInfo().getCode()=="SINK"){
                    var1 = (edge->getCapacity()-edge->getFlow())/edge->getCapacity();
                }
            }
            for( auto  edge : rhs->getAdj()){
                if( edge->getDest()->getInfo().getCode()=="SINK"){
                    var2 = (edge->getCapacity()-edge->getFlow())/edge->getCapacity();
                }
            }
            return var1 > var2;
        }
    };
    std::vector<Vertex<Location> *> cities;
    for( auto ver : managerTester.getNetwork().getVertexSet()){
        if(ver->getInfo().getType() == "C"){
            cities.push_back(ver);

        }
    }
    sort(cities.begin(),cities.end(),VertexComparator());
    managerTester.resetNetwork();

    for( auto ver : cities){

        cout<<"city "<<ver->getInfo().getMunicipality() <<endl;
        cout<<managerTester.FlowToCity(ver->getInfo())<<endl;
    }
    managerTester.getNetworkStats(avg, var, maxi);

    cout<<"AVG IS"<<avg<<" VAR IS "<< var<<" MAX IS "<<maxi<<endl;

    return 0;
}