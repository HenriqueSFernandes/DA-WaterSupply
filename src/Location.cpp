#include "Location.h"
#include <stdexcept>
#include <utility>

int Location::getId() const {
    return id_;
}

void Location::setId(int id) {
    id_ = id;
}

const std::string &Location::getCode() const {
    return code_;
}

void Location::setCode(const std::string &code) {
    code_ = code;
}

const std::string &Location::getType() const {
    return type_;
}

void Location::setType(const std::string &type) {
    type_ = type;
}

const std::string &Location::getReservoirName() const {
    if (this->getType() == "R") {
        return reservoir_name;
    } else {
        throw std::runtime_error("YOU TRIED TO GET A RESERVOIR NAME BUT LOCATION IS NOT A RESERVOIR");
    }
}

void Location::setReservoirName(const std::string &reservoirName) {
    if (this->getType() == "R") {
        reservoir_name = reservoirName;
    } else {
        throw std::runtime_error("YOU TRIED TO SET A RESERVOIR NAME BUT LOCATION IS NOT A RESERVOIR");
    }
}

double Location::getDemand() const {
    if (this->getType() == "C") {
        return demand;
    } else {
        throw std::runtime_error("YOU TRIED TO GET CITY DEMAND BUT LOCATION IS NOT A CITY");
    }
}

void Location::setDemand(double newDemand) {
    if (this->getType() == "C") {
        demand = newDemand;
    } else {
        throw std::runtime_error("YOU TRIED TO SET CITY DEMAND BUT LOCATION IS NOT A CITY");
    }
}

int Location::getPopulation() const {
    if (this->getType() == "C") {
        return population;
    } else {
        throw std::runtime_error("YOU TRIED TO GET CITY POPULATION BUT LOCATION IS NOT A CITY");
    }
}

void Location::setPopulation(int newPopulation) {
    if (this->getType() == "C") {
        population = newPopulation;
    } else {
        throw std::runtime_error("YOU TRIED TO SET CITY POPULATION BUT LOCATION IS NOT A CITY");
    }
}

int Location::getMaxDelivery() const {
    if (this->getType() == "R") {
        return maxDelivery;
    } else {
        throw std::runtime_error("YOU TRIED TO GET MAXDELIVERY BUT LOCATION IS NOT RESERVOIR");
    }
}

void Location::setMaxDelivery(int newMaxDelivery) {
    if (this->getType() == "R") {
        maxDelivery = newMaxDelivery;
    } else {
        throw std::runtime_error("YOU TRIED TO SET MAXDELIVERY BUT LOCATION IS NOT RESERVOIR");
    }
}

Location::Location(int id, std::string code) : id_(id), code_(std::move(code)) {}

bool Location::operator==(const Location &rhs) const {
    return code_ == rhs.code_;
}

bool Location::operator!=(const Location &rhs) const {
    return !(rhs == *this);
}

const std::string &Location::getMunicipality() const {
    if (this->getType() == "R" || this->getType() == "C") {
        return municipality;
    } else {
        throw std::runtime_error("THIS LOCATION HAS NO MUNICIPALITY VALUE");
    }
}

void Location::setMunicipality(const std::string &newMunicipality) {
    if (this->getType() == "R" || this->getType() == "C") {
        municipality = newMunicipality;
    } else {
        throw std::runtime_error("THIS LOCATION HAS NO MUNICIPALITY VALUE");
    }
}
