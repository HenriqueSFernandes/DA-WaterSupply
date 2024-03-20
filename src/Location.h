//
// Created by memechanic on 08-03-2024.
//

#ifndef LOCATION_H
#define LOCATION_H

#include <string>

class Location {
public:
    [[nodiscard]] int getId() const;

    void setId(int id);

    [[nodiscard]] const std::string &getCode() const;

    void setCode(const std::string &code);

    [[nodiscard]] const std::string &getType() const;

    void setType(const std::string &type);

    [[nodiscard]] const std::string &getReservoirName() const;

    void setReservoirName(const std::string &reservoirName);

    [[nodiscard]] double getDemand() const;

    void setDemand(double newDemand);

    [[nodiscard]] int getPopulation() const;

    void setPopulation(int newPopulation);

    [[nodiscard]] int getMaxDelivery() const;

    void setMaxDelivery(int maxDelivery);

    Location(int id, std::string code);

    bool operator==(const Location &rhs) const;

    bool operator!=(const Location &rhs) const;

    [[nodiscard]] const std::string &getMunicipality() const;

    void setMunicipality(const std::string &municipality);

private:
    int id_;
    std::string code_;
    std::string type_;
    std::string reservoir_name;
    std::string municipality;
    int maxDelivery;
    double demand;
    int population;
};

#endif //LOCATION_H

