#include "Location.h"
#include <stdexcept>

int Location::getId() const {
    return id_;
}

void Location::setId(int id) {
    id_ = id;
}

const std::__cxx11::basic_string<char> &Location::getCode() const {
    return code_;
}

void Location::setCode(const std::__cxx11::basic_string<char> &code) {
    code_ = code;
}

const std::__cxx11::basic_string<char> &Location::getType() const {
    return type_;
}

void Location::setType(const std::__cxx11::basic_string<char> &type) {
    type_ = type;
}

const std::__cxx11::basic_string<char> &Location::getReservoirName() const {
    if (this->getType() == "R") {
        return reservoir_name;
    } else {
        throw std::runtime_error("YOU TRIED TO GET A RESERVOIR NAME BUT LOCATION IS NOT A RESERVOIR");
    }

}

void Location::setReservoirName(const std::__cxx11::basic_string<char> &reservoirName) {
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

void Location::setDemand(double demand) {
    if (this->getType() == "C") {
        Location::demand = demand;
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

void Location::setPopulation(int population) {
    if (this->getType() == "C") {
        Location::population = population;
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

void Location::setMaxDelivery(int maxDelivery) {
    if (this->getType() == "R") {
        Location::maxDelivery = maxDelivery;
    } else {
        throw std::runtime_error("YOU TRIED TO SET MAXDELIVERY BUT LOCATION IS NOT RESERVOIR");
    }

}

Location::Location(int id, const std::string &code) : id_(id), code_(code) {}

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

void Location::setMunicipality(const std::string &municipality) {
    if (this->getType() == "R" || this->getType() == "C") {
        Location::municipality = municipality;
    } else {
        throw std::runtime_error("THIS LOCATION HAS NO MUNICIPALITY VALUE");
    }
}
bool Location::operator<(const Location &rhs) const {
    return code_ < rhs.code_;
}
