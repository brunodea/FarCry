#ifndef _ISLAND_ESCAPE_VEHICLE_H
#define _ISLAND_ESCAPE_VEHICLE_H

#include <string>
#include "IslandEngine.h"

namespace vehicle
{
    class Vehicle:public view::DrawableUnit
    {
        public:
            Vehicle(model::Shape *shape, bool visible):DrawableUnit(shape, visible) {}

            void setCurrentFuel(int fuelLevel) { m_CurrentFuel = fuelLevel; }
            void setMaxFuel(int maxFuelLevel) { m_MaxFuel = maxFuelLevel; }
            void setArmor(int armor) { m_Armor = armor; }
            void setName(std::string name) { m_Name = name; }

            int currentFuel() { return m_CurrentFuel; }
            int maxFuel() { return m_MaxFuel; }
            int armor() { return m_Armor; }

            std::string name() { return m_Name; }

        private:
            int m_CurrentFuel;
            int m_MaxFuel;
            int m_Armor;
            std::string m_Name;
    };
}

#endif // VEHICLE_H
