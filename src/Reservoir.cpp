//
// Created by memechanic on 08-03-2024.
//

#include "Reservoir.h"

Reservoir::Reservoir(int id, const std::string& code, const std::string& name, const City& municipality, double max_delivery):
    Location(id, code),
    municipality_(municipality),
    name_(name),
    max_delivery_(max_delivery) {}

std::string Reservoir::getName() const {
    return name_;
}

City Reservoir::getMunicipality() const {
    return municipality_;
}

double Reservoir::getMaxDelivery() const {
    return max_delivery_;
}
