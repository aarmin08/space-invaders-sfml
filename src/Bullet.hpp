#pragma once 

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Window.hpp"

class Bullet {
private: 
    int initposx, initposy; 
    float velocity; 
    bool toDestroy; 
    sf::Sprite sprite; 
    sf::Texture* texture; 

    sf::FloatRect bulletRect; 

    sf::Time creationTime; 
    sf::Clock clock; 

    Window* window; 
    bool shouldDestroy = false;
public: 
    Bullet(int initposx, int initposy, float velocity) {
        this->initposx = initposx; 
        this->initposy = initposy; 
        this->velocity = velocity;   
    }

    void Create(std::string texture) {
        this->texture = new sf::Texture; 
        if(!this->texture->loadFromFile(texture)) {
            std::cout << "ERR" << std::endl; 
        }
        sprite.setTexture(*this->texture);
        sprite.setScale(0.06f, 0.06f); 
        sprite.setPosition(initposx, initposy); 

        bulletRect = sprite.getGlobalBounds();  
    }

    void BulletUpdate(Window& window) {
        sprite.move(0, -velocity); 
        window.DrawOnWindow(this->sprite); 
    }; 

    sf::Sprite& getSprite() { return this->sprite; }

    sf::FloatRect& getRect() { return this->bulletRect; }

    void ShouldDestroy() {
        shouldDestroy = true; 
    }

    bool getDestroyState() {
        return shouldDestroy;
    }

    bool shouldRemove(float lifetime) const {
        return clock.getElapsedTime() - creationTime >= sf::seconds(lifetime);
    }

}; 
