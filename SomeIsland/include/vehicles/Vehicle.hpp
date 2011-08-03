#ifndef _ISLAND_ESCAPE_VEHICLE_H
#define _ISLAND_ESCAPE_VEHICLE_H

#include <string>
#include <vector>
#include "macros.h"
#include "IslandEngine.h"

namespace vehicle
{
    class Vehicle:public view::DrawableUnit
    {
        public:
            Vehicle(std::vector<model::Shape*> shapes, bool visible):DrawableUnit(shapes, visible) {}

            void setCurrentFuel(int fuelLevel) { m_CurrentFuel = fuelLevel; }
            void setMaxFuel(int maxFuelLevel) { m_MaxFuel = maxFuelLevel; }
            void setArmor(int armor) { m_Armor = armor; }
            void setName(std::string name) { m_Name = name; }
            void addPassOverTerrain(TerrainType type) { m_vPassOverTerrain.push_back(type); }

            int currentFuel() { return m_CurrentFuel; }
            int maxFuel() { return m_MaxFuel; }
            int armor() { return m_Armor; }

            std::string name() { return m_Name; }

            std::vector<TerrainType> passOverTerrain() { return m_vPassOverTerrain; }

        private:
            int m_CurrentFuel;
            int m_MaxFuel;
            int m_Armor;
            std::string m_Name;
            std::vector<TerrainType> m_vPassOverTerrain;
    };
}

#endif // VEHICLE_H
