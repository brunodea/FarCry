#ifndef _ISLAND_ESCAPE_UNITLOADERFUNCTIONS_H_
#define _ISLAND_ESCAPE_UNITLOADERFUNCTIONS_H_

#include <string>
#include <vector>
#include "IslandEngine.h"
#include "vehicles/Vehicle.hpp"

namespace util
{
    class UnitAttribute
    {
    public:
        std::string m_attribute;
        std::string m_value;
    };

    std::vector<std::string> splitString(const char* str, const char* separator);
    model::GameObject* loadUnitFromFile(std::string filename);
    vehicle::Vehicle* getVehicleFromAttributes(std::vector<UnitAttribute> attrs);
}

#endif
