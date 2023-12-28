#include "engine/mapGeneration.hpp"


int* generateMap(int mapSize) {

    int* map = new int[mapSize];

    srand(static_cast<unsigned int>(time(nullptr)));

    float offsetX = static_cast<float>(rand()) / RAND_MAX * 1000.0f;
    float offsetY = static_cast<float>(rand()) / RAND_MAX * 1000.0f;
    float scale = static_cast<float>(rand()) / RAND_MAX * 80.0f;

    std::cout << "[Info IGS] Generating\n"; //Game crashes here. Why? no fucking clue

    if (map == nullptr) {       //No clue why, but this shithead prevents some weird ass memory allocation issue which crashes everything. Careful. Edit: never mind, crashes anyways. Too bad!
        std::cout << "[Error IGS] Memory allocation failed. Fucking somehow\n";
        return nullptr;
    }

    for (int i = 0; i < mapSize; ++i) {

        for (int j = 0; j < mapSize; ++j) {

            float perlinValue = perlinGeneration(offsetX + i / scale, offsetY + j / scale);
            std::cout << "i: " << i << ", j: " << j << ", perlinValue: " << perlinValue << " map value: ";


            map[index2Dto1D(i, j, mapSize)] = (perlinValue < 0.5f) ? grass : water;

            std::cout << map[index2Dto1D(i, j, mapSize)] << "\n";


            
        }
    }

    std::cout << "[Info IGS] Generated!\n";

    return map;

}

void deleteIntArray(int* map, int mapSize) {
    
    delete[] map;
}

