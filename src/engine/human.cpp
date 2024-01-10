#include "engine/human.hpp"

#include <cstdlib>
#include <ctime>

Human::Human(Texture2D texture, Vector3 position){
    
    this->ID = rand();
    
    this->health = 100;

    this->texture = texture;

    for(int trait: traits){

        traits[trait] = 0;

    }


    this->position.x = position.x;
    this->position.y = position.y;

}

Human::~Human(){

}

void Human::render(Camera2D camera, Vector2 screenZero, Vector2 worldSize){

    Vector2 screenPosition;
    
    if (this == nullptr){
        std::cerr << "How the fuck? Human " << this->ID << " is a null pointer.\n";
        return;
    }
    
    screenPosition = isometricToScreen(this->position);

    if (((screenPosition.x + (this->texture.width * 4) >= screenZero.x && screenPosition.x <= worldSize.x) && (screenPosition.y + (this->texture.height * 2) >= screenZero.y && screenPosition.y - (this->texture.height * 2) <= worldSize.y))){
        
        DrawTexture(this->texture, screenPosition.x + tileWidth / 2 - 4, screenPosition.y - tileHeight / 2, WHITE);

    }
    
    

}

void::Human::update(){

    this->position.x += 0.01f;
    this->position.y += 0.01f;

}

void Human::move(float tilesX, float tilesY) {

    this->position.x += tilesX;
    this->position.y += tilesY;
}

void Human::setPosition(float tilesX, float tilesY) {

    Vector2 screenPosition = isometricToScreen({tilesX, tilesY});

    screenPosition.x -= tileWidth / 2;
    screenPosition.y += 0;

    screenPosition = screenToIsometricPrecise(screenPosition);

    this->position.x = screenPosition.x;
    this->position.y = screenPosition.y;
}
