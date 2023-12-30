#include "engine/human.hpp"
#include <stdlib.h>

Human::Human(Texture2D texture, Vector2 position){
    
    this->ID = rand();
    
    this->health = 100;

    this->texture = texture;

    for(int trait: traits){

        traits[trait] = 0;

    }

    this->position = position;

}

Human::~Human(){

}

void Human::renderHuman(){

    DrawTexture(this->texture, position.x, position.y, WHITE);

}