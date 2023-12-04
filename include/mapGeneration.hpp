#include "raylib.h"
#include "mapArithmetics.hpp"

#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP

int** generateMap(int mapSize);

void delete2DIntArray(int** map, int mapSize);



#endif // MAP_GENERATOR_HPP