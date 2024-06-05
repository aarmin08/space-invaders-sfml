#pragma

#ifndef PLAYER
#define PLAYER
#include "Window.hpp"
#include "Bullet.hpp"
#include "GameManager.hpp"

class Player {
private: 
    int initposx, initposy; 
    sf::Texture texture; 
    std::string dirpath; 
    sf::Sprite sprite; 
    sf::FloatRect rect; 
    sf::Clock clock;

    int score; 

    std::vector<Bullet> bullets; 

    bool spacebarwaspressed = false; 

    void MoveSprite(Window& window) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sprite.move(-0.15f,0); 
        } 
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sprite.move(.15f,0); 
        } 
        sf::Vector2f spritePosition = sprite.getPosition();
        sf::FloatRect spriteBounds = sprite.getGlobalBounds();

        if (spritePosition.x < -400) {
            sprite.setPosition(400 -spriteBounds.width, spritePosition.y); // Left bound
        } else if (spritePosition.x + spriteBounds.width > window.getRenderWindow().getSize().x - 10) {
            sprite.setPosition(-399, spritePosition.y); // Right bound
        }
    }

public: 
    Player(int initposx, int initposy, std::string dirpath) { 
        this->initposx = initposx; 
        this->initposy = initposy; 
        this->dirpath = dirpath; 
    }; 

    void CreatePlayer() {
        this->texture.loadFromFile(dirpath); 
        this->sprite.setTexture(texture); 
        this->sprite.setPosition(initposx, initposy); 
        this->sprite.setScale(0.06f, 0.06f); 
        this->rect = sprite.getGlobalBounds(); 
    }

    int getScore() { return score; }
    void updateScore(int increment) { score += increment; } 

    sf::Sprite& getSprite() {
        return sprite; 
    }

    sf::FloatRect& getRect() {
        return rect; 
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
        std::cout << "Player position set to: " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
    }

    void PlayerUpdate(Window& window, sf::Event event, GameManager& manager, bool shouldEndGame) {
        Bullet bullet(sprite.getPosition().x + 25, sprite.getPosition().y, 0.5f);
    
        window.DrawOnWindow(this->sprite); 

        if (!shouldEndGame){
            MoveSprite(window);
            bool spacebarIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
            if (spacebarIsPressed  && !spacebarwaspressed) {
                manager.CreateBullet(bullet);
            }
            manager.BulletUpdate(window);

            spacebarwaspressed = spacebarIsPressed;
        }
    }
    // Movement
};
#endif
