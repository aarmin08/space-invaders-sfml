#pragma once 
#include <SFML/Graphics/Text.hpp>
#include <string.h>
#include "Window.hpp"
#include <iostream> 

class Text{
private:
    sf::Text text; 
    std::string displaytext; 
    int fontSize;
    std::string fontDir; 
    sf::Font font; 
public: 
    Text(std::string textToDisplay, int size, std::string fontDir){
        this->displaytext = textToDisplay;
        this->fontSize = size; 
        this->fontDir = fontDir; 
    }

    void CreateText() {
        if (!font.loadFromFile(fontDir)) {
            std::cerr << "ERRRRRRR" << std::endl; 
        };
        std::cout << "Created font: " << font.getInfo().family << std::endl;
        //TODO: why isnt the damn text loading gang
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(fontSize); 
        text.setPosition(-40,0);
        text.setFont(font);
        text.setString(displaytext);
    }
    
    void SetTextPosition(int posx, int posy) {
        text.setPosition(posx, posy); 
    }
    void UpdateText(std::string textToDisplay) {
        text.setString(textToDisplay);
    }

    void RenderText(Window& window) {
        window.getRenderWindow().draw(this->text);
    }
    
    sf::Text& getText() { return this->text; }
}; 
