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
    virtual ~Location() = default;

    Location(int id, const std::string &code);

    int getId() const;

    std::string getCode() const;

    bool operator==(const Location &other) const {
        return (code_ == other.code_);
    }
};

#endif //LOCATION_H

