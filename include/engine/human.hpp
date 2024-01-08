#include <cstdint>
#include <stdlib.h>
#include <iostream>

#include "raylib.h"
#include "engine/mapArithmetics.hpp"

#ifndef HUMAN_HPP
#define HUMAN_HPP

class Human{

private:
    
    Texture2D texture;

public:

    //236 ish bytes per human. Not great, not terrible. Name will probably increase this.

    Vector3 position;

    uint8_t health;

    uint16_t ID;

    uint8_t traits[10];

    Human(Texture2D texture, Vector3 position = {0, 0, 0});
    ~Human();

    void render(Camera2D camera, Vector2 screenZero, Vector2 worldSize);

    void move(float tilesX, float tilesY);

    void setPosition(float tilesX, float tilesY);

    void update();

};

#endif


