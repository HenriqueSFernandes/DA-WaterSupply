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
    cout<<managerTester.edmondsKarpBalance(Location(-1, "SOURCE"), Location(-1, "SINK"));
    cout<<"NEW STATS"<<endl;
    managerTester.getNetworkStats(avg, var, maxi);
    cout<<"AVG IS"<<avg<<" VAR IS "<< var<<" MAX IS "<<maxi<<endl;

    return 0;
}