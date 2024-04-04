/// @file Location.h
#ifndef LOCATION_H
#define LOCATION_H

#include <string>

/**
 * @brief Class used to represent a location.
 * This location can be a reservoir, a city or a pumping station. The different methods may or may not apply to all instances of locations, for example when the function getReservoirName() is used on a city. In this cases, the methods return an error.
 */
class Location {
public:
    /**
     * @brief Parameterized constructor.
     * @param id The id.
     * @param code The code.
     */
    Location(int id, std::string code);

    /**
     * @brief Id getter
     * @return The id of the location.
     */
    [[nodiscard]] int getId() const;

    /**
     * @brief Id setter.
     * @param id The new id.
     */
    void setId(int id);

    /**
     * @brief Code getter.
     * @return The code.
     */
    [[nodiscard]] const std::string &getCode() const;

    /**
     * @brief Code setter.
     * @param code The new code.
     */
    void setCode(const std::string &code);

    /**
     * @brief Type getter (R for reservoir, C for city or PS for pumping station).
     * @return The type.
     */
    [[nodiscard]] const std::string &getType() const;

    /**
     * @brief Set type (R for reservoir, C for city or PS for pumping station).
     * @param type The new type.
     */
    void setType(const std::string &type);

    /**
     * @brief Reservoir name getter. If the location is not a reservoir, it throws an error.
     * @return The name of the reservoir.
     */
    [[nodiscard]] const std::string &getReservoirName() const;

    /**
     * @brief Reservoir name setter. If the location is not a reservoir, it throws an error.
     * @param reservoirName The new name.
     */
    void setReservoirName(const std::string &reservoirName);

    /**
     * @brief Demand getter. If the location is not a city, it throws an error.
     * @return The demand.
     */
    [[nodiscard]] double getDemand() const;

    /**
     * @brief Demand setter. If the location is not a city, it throws an error.
     * @param newDemand The new demand.
     */
    void setDemand(double newDemand);

    /**
     * @brief Population getter. If the location is not a city, it throws an error.
     * @return The population.
     */
    [[nodiscard]] int getPopulation() const;

    /**
     * @brief Population getter. If the location is not a city, it throws an error.
     * @param newPopulation The population.
     */
    void setPopulation(int newPopulation);

    /**
     * @brief Max delivery getter. If the location is not a reservoir, it throws an error.
     * @return The max delivery.
     */
    [[nodiscard]] int getMaxDelivery() const;

    /**
     * @brief Max delivery setter. If the location is not a reservoir, it throws an error.
     * @param maxDelivery The new max delivery.
     */
    void setMaxDelivery(int maxDelivery);

    /**
     * @brief Municipality getter. If the location is not a reservoir or a pumping station, it throws an error.
     * @return The municipality.
     */
    [[nodiscard]] const std::string &getMunicipality() const;

    /**
     * @brief Municipality setter. If the location is not a reservoir or a pumping station, it throws an error.
     * @param municipality The new municipality.
     */
    void setMunicipality(const std::string &municipality);

    /**
     * @brief Equality operator overload.
     * @param rhs The location to compare to.
     * @return True if the two locations are the same (two locations are the same if the code is the same).
     */
    bool operator==(const Location &rhs) const;

    /**
     * @brief Inequality operator overload.
     * @param rhs The location to compare to.
     * @return True if the two locations are different (two locations are different if the code is different).
     */
    bool operator!=(const Location &rhs) const;

    /**
     * @brief Less than operator overload.
     * @param rhs The location to compare to.
     * @return True if the code of the current location is less than the code of the other location.
     */
    bool operator<(const Location &rhs) const;


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

