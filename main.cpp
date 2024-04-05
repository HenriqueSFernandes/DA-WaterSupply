//
// Created by jose on 3/3/24.
//
#include "src/SupplyManagement.h"
#include <sstream>
#include <iostream>

int main() {
    cout << "here" << endl;
    SupplyManagement managerTester = SupplyManagement("../data/Cities_Madeira.csv", "../data/Reservoirs_Madeira.csv",
                                                      "../data/Stations_Madeira.csv", "../data/Pipes_Madeira.csv");
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
    managerTester.getNetworkStats(avg, var, maxi);
    cout<<"AVG IS"<<avg<<" VAR IS "<< var<<" MAX IS "<<maxi<<endl;
    return 0;
}