#include "engine/mapObject.hpp"

mapObject::mapObject(int size)
{
    // Generate the map
    this->mapValues = generateMap(size);

    this->size = size;

    this->mapArray = convertTo1DMap();
}

mapObject::~mapObject()
{
    // Call the deleteMap function in the destructor
    this->deleteMap(this->mapValues, size);

    delete[] this-> mapArray;
}

void mapObject::deleteMap(int** map, int mapSize)
{
    for (int i = 0; i < mapSize; ++i)
    {
        delete[] map[i];
    }

    delete[] map;
}

//Thanks to Tottel on the raylib discord for this idea. Turns the map array into a 1D array for better management. It'll probably take ages to implement. 20/12/2023
int* mapObject::convertTo1DMap(){

    int arrayPosition = 0;
    int size = this->size * this->size;


    int* map = new int[size];
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {

            map[arrayPosition] = this->mapValues[i][j];

            std::cout << map[arrayPosition] << " ";

            if (((arrayPosition + 1) % this->size) == 0){
                std::cout << "\n";
            }
            

            arrayPosition++;

        }
    }
    std::cout << "\n";
    return map;

}


//Class end ----------------------------------------------

/*

    size = 4 new size = 16

    0(0,0,0)   1(0,1,1)   1(0,2,2)   0(0,3,3)
    
    0(1,0,4)   1(1,1,5)   1(1,2,6)   0(1,3,7)

    0(2,0,8)   1(2,1,9)   0(2,2,10)   1(2,3,11)

    0(3,0,12)   1(3,1,13)   0(3,2,14)   1(3,3,15)

*/

