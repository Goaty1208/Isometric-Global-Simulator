#include "engine/human.hpp"

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

void Human::render(Camera2D camera){

    Vector2 screenPosition = isometricToScreen(this->position);

    DrawTexture(this->texture, screenPosition.x + tileWidth / 2 - 4, screenPosition.y - tileHeight / 2, WHITE);

}

void::Human::update(){

    std::cout << "X: " << this->position.x << " Y: " << this->position.y << "\n";

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
