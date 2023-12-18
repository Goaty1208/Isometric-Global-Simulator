#include "engine/mapObject.hpp"

mapObject::mapObject(int size)
{
    // Generate the map
    this->mapValues = generateMap(size);

    this->size = size;
}

mapObject::~mapObject()
{
    // Call the deleteMap function in the destructor
    this->deleteMap(this->mapValues, size);
}

void mapObject::deleteMap(int** map, int mapSize)
{
    for (int i = 0; i < mapSize; ++i)
    {
        delete[] map[i];
    }

    delete[] map;
}