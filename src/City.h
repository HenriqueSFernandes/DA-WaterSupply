//
// Created by memechanic on 08-03-2024.
//

#ifndef CITY_H
#define CITY_H

#include "Location.h"

class City: public Location {
private:
    std::string name_;
    double demand_;
    int population_;

public:
    City(int id, const std::string& code, const std::string& name, double demand, int population);

    std::string getName() const;

    double getDemand() const;

    int getPopulation() const;
};

#endif //CITY_H
