#include <cstdint>
#include "raylib.h"

#ifndef HUMAN_HPP
#define HUMAN_HPP

class Human{

private:
    

public:

    //236 ish bytes per human. Not great, not terrible. Name will probably increase this.

    Vector2 position; //Largest piece of data along with the texture

    uint8_t health;

    uint16_t ID;

    Texture2D texture;

    uint8_t traits[10];

    Human(Texture2D texture, Vector2 position);
    ~Human();

    void renderHuman();

};

#endif


