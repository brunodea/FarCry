#ifndef _ISLAND_ESCAPE_JEEP_H
#define _ISLAND_ESCAPE_JEEP_H

#include "vehicles/Vehicle.hpp"

namespace vehicle
{
    class Jeep:public vehicle::Vehicle
    {
        public:
            Jeep(bool visible);
            virtual ~Jeep();

        private:
    };
}

#endif // _ISLAND_ESCAPE_JEEP_H
