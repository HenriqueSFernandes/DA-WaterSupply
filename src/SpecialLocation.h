//
// Created by jose on 3/9/24.
//

#ifndef SPECIALLOCATION_H
#define SPECIALLOCATION_H
#include "Location.h"


class SpecialLocation : public Location {
private:
    std::string code;
    int index;
public:
    SpecialLocation(int id, const std::string &code)
        : ::Location(id, code) {
    }
};



#endif //SPECIALLOCATION_H
