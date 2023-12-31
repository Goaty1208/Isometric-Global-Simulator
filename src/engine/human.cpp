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

    Vector2 screenSize = { static_cast<float>(windowWidth), static_cast<float>(windowHeight) };
    Vector2 worldSize = GetScreenToWorld2D(screenSize, camera);
    Vector2 screenZero = GetScreenToWorld2D({0.0f, 0.0f}, camera);

    Vector3 tilePosition = { static_cast<float>(this->position.x), static_cast<float>(this->position.y), 0.0f };
    Vector2 screenPosition = isometricToScreenTiles(tilePosition);
    
    if (((screenPosition.x + tileWidth >= screenZero.x && screenPosition.x <= worldSize.x) && (screenPosition.y + tileHeight >= screenZero.y && screenPosition.y <= worldSize.y))){

        DrawTexture(this->texture, this->position.x + this->texture.width, this->position.y + this->texture.height, WHITE);

    }


}

void::Human::update(){

    Vector2 isoPosition = isometricToScreenTiles(this->position);

    std::cout << "X: " << isoPosition.x << " Y: " << isoPosition.y << "\n";

    this->move(0.00001, 0.00001);

}

void Human::move(float tilesX, float tilesY) {

    float pixelX = tilesX * tileWidth;
    float pixelY = tilesY * tileHeight;

    this->position.x += pixelX;
    this->position.y += pixelY;
}

void Human::setPosition(float tilesX, float tilesY) {

    float pixelX = tilesX * tileWidth;
    float pixelY = tilesY * tileHeight;

    this->position.x = pixelX;
    this->position.y = pixelY;
}
