#pragma once

#include <SFML/Graphics.hpp>
#include <string.h>


class Window {
private: 
    int height, width;     
    std::string title;
    sf::RenderWindow window; 
 
public: 
    Window(int height, int width, std::string title) {
        this->height = height; 
        this->width = width; 
        this->title = title; 
    }; 

    void CreateWindow() {
        this->window.create(sf::VideoMode(width,height), title); 
        this->window.setKeyRepeatEnabled(false); 
    }

    void WindowDisplay(){
        this->window.display(); 
    }

    void DrawOnWindow(sf::Sprite sprite) {
        this->window.draw(sprite); 
    }

    void WindowClear() {
        this->window.clear(); 
    }

    sf::RenderWindow& getRenderWindow() {
        return window;
    }
};