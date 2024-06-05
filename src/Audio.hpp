#pragma once 

#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include <SFML/Audio.hpp>

#include <memory>
#include <string.h>
#include <iostream>

class Audio {
private: 
    sf::SoundBuffer* buffer; 
    sf::Sound sound;
    std::string soundFile;
public: 
    Audio() {
        buffer = new sf::SoundBuffer; 
    }
    void LoadAudio(std::string soundFile) {
        if (!this->buffer->loadFromFile(soundFile)) {
            std::cout << "Failed to load sound" << std::endl; 
        }
        sound.setBuffer(*buffer); 
    }

    void PlaySound() {
        sound.play(); 
    }
}; 
