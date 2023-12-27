#include "engine/mapObject.hpp"

mapObject::mapObject(int size)
{
    // Generate the map
    this->size = size;

    this->mapArray = generateMap(size);
}

mapObject::~mapObject()
{
    // Call the deleteMap function in the destructor

    delete[] this-> mapArray;
}

void mapObject::deleteMap(int* map, int mapSize)
{
    delete[] map;
}


