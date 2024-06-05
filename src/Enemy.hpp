#pragma once 

#include <iostream>
#include <string.h>
#include "Window.hpp"


#include <SFML/Graphics.hpp>

class Enemy {
private: 
    float moveSpeed; 
    int positionx, positiony; 
    bool isDead = false; 
    std::string texture_dir;
    sf::Texture* texture; 
    sf::FloatRect rect; 
    sf::Sprite sprite;  

public: 
    Enemy(int positionx, int positiony, float moveSpeed, std::string texture_path) : texture(), isDead(false) {
        this->positionx = positionx; 
        this->positiony = positiony; 
        this->moveSpeed = moveSpeed; 
        this->texture_dir = texture_path; 
        texture = new sf::Texture;
    }

    void CreateEnemy() {
        this->texture->loadFromFile(texture_dir);
        this->sprite.setTexture(*texture);
        this->sprite.setPosition(positionx, positiony); 
        this->sprite.setScale(0.06f, 0.06f);
        this->sprite.setColor(sf::Color::Blue);
        this->rect = sprite.getGlobalBounds();    
    }

    void MoveEnemy() { 
        sprite.move(0, moveSpeed); 
    }

    void DrawEnemies(Window& window) {
        window.DrawOnWindow(sprite);
    }

    void setAlive() {
        isDead = false;
    }

    void KillEnemy() {
        isDead = true;
    }

    bool getDeadState() { return isDead; }

    sf::FloatRect getRect() { return this->rect; }

    sf::Sprite& getSprite() { return sprite; }
};
