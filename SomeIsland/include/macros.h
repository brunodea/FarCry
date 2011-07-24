#ifndef _SOME_ISLAND_MACROS_H_
#define _SOME_ISLAND_MACROS_H_

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

#define CONTROLLER Controller::instance()

#define PI 3.141592f

enum TerrainType
{
    LAND = 0x00000000,
    SHALLOW_WATER,
    DEEP_WATER,
    MUD,
    SAND,
    ROCK
};

#endif // _SOME_ISLAND_MACROS_H_
