//
// Created by memechanic on 08-03-2024.
//

#include "Location.h"

Location::Location(int id, const std::string &code) : id_(id), code_(code) {}

int Location::getId() const {
    return id_;
}

std::string Location::getCode() const {
    return code_;
}
