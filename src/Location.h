//
// Created by memechanic on 08-03-2024.
//

#ifndef LOCATION_H
#define LOCATION_H

#include <string>

class Location {
public:
    int getId() const;

    void setId(int id);

    const std::string &getCode() const;

    void setCode(const std::string &code);

    const std::string &getType() const;

    void setType(const std::string &type);

    const std::string &getReservoirName() const;

    void setReservoirName(const std::string &reservoirName);

    double getDemand() const;

    void setDemand(double demand);

    int getPopulation() const;

    void setPopulation(int population);

    int getMaxDelivery() const;

    void setMaxDelivery(int maxDelivery);


private:
    int id_;
public:
    Location(int id, const std::string &code);

private:
public:
    bool operator==(const Location &rhs) const;

    bool operator!=(const Location &rhs) const;

private:
    std::string code_;
    std::string type_;
    std::string reservoir_name;
    std::string municipality;
public:
    const std::string &getMunicipality() const;

    void setMunicipality(const std::string &municipality);

private:
    int maxDelivery;
    double demand;
    int population;
};

#endif //LOCATION_H

