#include "raylib.h"

#ifndef MAPOBJECT_HPP
#define MAPOBJECT_HPP

class mapObject
{
public:
    int size;
    int** values;

    mapObject(int size);
    ~mapObject();

    void updateMap(Vector2 position);

private:
    void deleteMap(int** map, int mapSize);
};

#endif
