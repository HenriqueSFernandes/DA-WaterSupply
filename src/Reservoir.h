//
// Created by memechanic on 08-03-2024.
//

#ifndef RESERVOIR_H
#define RESERVOIR_H

#include "Location.h"
#include "City.h"

class Reservoir : public Location {
private:
    std::string name_;
    City municipality_;
    double max_delivery_;

public:
    Reservoir(int id, const std::string& code, const std::string& name, const City& municipality, double max_delivery);

    std::string getName() const;

    City getMunicipality() const;

    double getMaxDelivery() const;
};

#endif //RESERVOIR_H