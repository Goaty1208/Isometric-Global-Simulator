#include "mapObject.hpp"
#include "mapGeneration.hpp"

mapObject::mapObject(int size){

    //Generate the map
    values = generateMap(size);
}

mapObject::~mapObject()
{
    // Call the deleteMap function in the destructor
    deleteMap(values, size);
}

void mapObject::deleteMap(int** map, int mapSize)
{
    for (int i = 0; i < mapSize; ++i)
    {
        delete[] map[i];
    }

    delete[] map;
}

void mapObject::updateMap(Vector2 position)
{
    int x = static_cast<int>(position.x) - 1;
    int y = static_cast<int>(position.y) - 1;

    std::cout << "Before Update - values[" << x << "][" << y << "] = " << values[x][y] << "\n";

    // Check if the coordinates are within bounds before using them as indices
    if (x >= 0 && x < size && y >= 0 && y < size)
    {
        // Update map at the rounded coordinates
        switch (values[x][y])
        {
        case 1:
            values[x][y] = 0;
            break;
        case 0:
            values[x][y] = 1;
            break;
        }
    }

    std::cout << "After Update - values[" << x << "][" << y << "] = " << values[x][y] << "\n";
}
