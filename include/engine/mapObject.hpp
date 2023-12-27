#include "raylib.h"
#include "mapGeneration.hpp"
#include <iostream>

#ifndef MAP_OBJECT_HPP
#define MAP_OBJECT_HPP

class mapObject
{
public:
    int size;
    int* mapArray;

    mapObject(int size);
    ~mapObject();

    void updateMap(Vector2 position);

private:
    void deleteMap(int* map, int mapSize);
};

#endif
