#include "vehicles/Jeep.h"

using namespace vehicle;

Jeep::Jeep(std::vector<model::Shape*> shapes, bool visible)
    : vehicle::Vehicle(shapes, visible)
{
    setCurrentFuel(500);
    setMaxFuel(500);
    setArmor(100);
    setName("Jeep");
    setMaxSpeed(5.3f);
    setAccel(1.8f);
    addPassOverTerrain(LAND);
    addPassOverTerrain(ROCK);
    addPassOverTerrain(MUD);
    addPassOverTerrain(SAND);
}

Jeep::~Jeep()
{

}
