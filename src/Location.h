//
// Created by memechanic on 08-03-2024.
//

#ifndef LOCATION_H
#define LOCATION_H

#include <string>

class Location {
protected:
    int id_;
    std::string code_;

public:
    Location(int id, const std::string& code);

    int getId() const;
    std::string getCode() const;
};

#endif //LOCATION_H

