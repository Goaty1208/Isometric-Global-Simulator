#include "raylib.h"
#include "mapArithmetics.hpp"

#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP

//What in the C++ is this shit -----------------------
int** generateMap(int mapSize) {
    int** map = new int*[mapSize];

    srand(static_cast<unsigned int>(time(nullptr)));

    float offsetX = static_cast<float>(rand()) / RAND_MAX * 1000.0f;
    float offsetY = static_cast<float>(rand()) / RAND_MAX * 1000.0f;
    float scale = static_cast<float>(rand()) / RAND_MAX * 80.0f;

    for (int i = 0; i < mapSize; ++i) {
        map[i] = new int[mapSize];

        for (int j = 0; j < mapSize; ++j) {
            float perlinValue = perlinGeneration(offsetX + i / scale, offsetY + j / scale);
            map[i][j] = (perlinValue < 0.5f) ? grass : water;
        }
    }

    return map;
}

//I like memory leaks. Note: this function must use the same map size as the size of the map it wants to delete, as otherwise things might very well explode.
void delete2DIntArray(int** map, int mapSize) {
    for (int i = 0; i < mapSize; ++i) {

        delete[] map[i];
    }

    delete[] map;
}

//----------------------------------------------------


#endif // MAP_GENERATOR_HPP