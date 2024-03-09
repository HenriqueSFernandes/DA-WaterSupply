//
// Created by jose on 3/3/24.
//

#ifndef LOCATION_H
#define LOCATION_H
#include <string>
//THIS IS JUST A DUMMY PLACE OTHER CLASS I AM USING TO TEST STUFF
//WILL LATER BE CHANGED WHEN ISSUE #3 IS COMPLETED
using namespace std;

class Location {
public:
    Location(const string &code){
        this->code=code;
    }
    bool operator==(const Location& other) const {
        // Implement comparison logic here
        // For example, compare the code of the locations
        return this->code == other.code;
    }

private:
    string code;
public:
    const string &getCode() const {
        return code;
    }
};



#endif //LOCATION_H
