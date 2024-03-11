//
// Created by memechanic on 08-03-2024.
//

#include "City.h"

City::City(int id, const std::string &code, const std::string &name, double demand, int population) :
        Location(id, code),
        name_(name),
        demand_(demand),
        population_(population) {}

std::string City::getName() const {
    return name_;
}

double City::getDemand() const {
    return demand_;
}

int City::getPopulation() const {
    return population_;
}
