//
// Created by jose on 3/3/24.
//
#include "src/SupplyManagement.h"

int main() {
    cout<<"here"<<endl;
    SupplyManagement managerTester=SupplyManagement("../data/Cities_Madeira.csv","../data/Reservoirs_Madeira.csv","../data/Stations_Madeira.csv","../data/Pipes_Madeira.csv");
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

    return 0;
}