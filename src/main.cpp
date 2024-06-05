#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Camera.hpp"
#include "GameManager.hpp"
#include "Text.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <fstream>

// Window object
// Player Object
Window mainWindow(600,600,"Space Invaders"); 
Player mainPlayer(0,0,"./Assets/c.png"); 
Text text("Score: 0", 24, "./Assets/font.ttf");
Camera camera;  

GameManager manager; 

int scoreRef; 
bool shouldEndGame = false; 

bool GameBeginning = true; 


int main() {
    // Class initalisation
    mainWindow.CreateWindow(); 
    mainPlayer.CreatePlayer();
    camera.InitializeView(&mainWindow, sf::Vector2f(mainPlayer.getRect().left, mainPlayer.getRect().top-200)); 
    std::fstream scoreFile; 
    scoreFile.open("score.txt", std::ios::out | std::ios::in); 
    std::fstream bestTimeFile;
    // References to sfml objects
    sf::Sprite playerSprite = mainPlayer.getSprite(); 
    sf::RenderWindow* window = &mainWindow.getRenderWindow(); 

    std::string getPrevScore; 
    std::string getPrevTime; 

    mainPlayer.setPosition(-40, 0);
    window->setView(camera.getView()); 

    while (getline(scoreFile, getPrevScore)) {
        std::cout << getPrevScore;
    }
    scoreFile.close(); 

    bestTimeFile.open("t.txt", std::ios::out | std::ios::in);
    while (getline(bestTimeFile, getPrevTime)) {
        std::cout << getPrevTime; 
    }

    bestTimeFile.close();

    manager.SetHighScore(getPrevScore == "" ? 0 : std::stoi(getPrevScore));
    manager.SetBestTime(getPrevTime == "" ? 0 : std::stoi(getPrevTime));

    // Text initalisation
    text.CreateText();
    text.SetTextPosition(-40,-500);

    Text loseText("You've lost (Score reached less than -40)", 24, "./Assets/font.ttf");
    loseText.CreateText();
    loseText.SetTextPosition(-200, -250); 

    Text highScoreText("High Score: " , 24, "./Assets/font.ttf"); 
    highScoreText.CreateText(); 
    highScoreText.SetTextPosition(-300, -500); 
    
    Text introText("10 points for kill; -20 points for pass. Press R to begin", 20, "./Assets/font.ttf"); 
    introText.CreateText(); 

    Text time("", 24, "./Assets/font.ttf");
    time.CreateText();
    time.SetTextPosition(150, -500);

    Text bestTime("", 24, "./Assets/font.ttf");
    bestTime.CreateText(); 
    bestTime.SetTextPosition(-300, 40); 

    // Time management
    sf::Clock clock;
    sf::Clock otherClock;
    sf::Time timeSinceLastSpawn = sf::Time::Zero;

    sf::Time Time = sf::Time::Zero; 

    while (window->isOpen()) {
        sf::Event event; 
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                scoreFile.open("score.txt", std::ios::out | std::ios::in); 
                scoreFile << std::to_string(manager.getHighScore()); 
                scoreFile.close();
                window->close(); 
                window = NULL; 
                delete window; 
                window = nullptr; 
                return EXIT_SUCCESS;
            } 
        }
        // Constantly check for the players current state
        mainWindow.WindowClear(); 

        if (GameBeginning) {
            introText.SetTextPosition(-250, -250); 
            introText.RenderText(mainWindow); 

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                manager.GameManagerSetup();
                GameBeginning = false;
            }
        }


        mainPlayer.PlayerUpdate(mainWindow, event, manager, shouldEndGame);

        if (!shouldEndGame && !GameBeginning) {
            //Basically the entire gameloop, shit memory management by the way
            time.UpdateText(std::to_string(int(otherClock.getElapsedTime().asSeconds())) + (" Second(s)")); 
            time.RenderText(mainWindow);
            bestTime.UpdateText("Best Time:" + std::to_string(manager.GetBestTime()) + " Seconds");
            bestTime.RenderText(mainWindow);
            scoreRef = manager.getScore();
            shouldEndGame = manager.getPlayerCondition();            
            text.UpdateText("Score: " + std::to_string(scoreRef)); 
            text.RenderText(mainWindow); 
            highScoreText.UpdateText("High Score: " + std::to_string(manager.getHighScore())); 
            highScoreText.RenderText(mainWindow); 
            manager.ManagerEnemyUpdate(mainWindow);
            manager.CheckForBulletAndEnemyInteractions();
            manager.CalculateHighScore();
            manager.CheckForLosePointCondition();
            manager.SetBestTime(int(otherClock.getElapsedTime().asSeconds())); 
            sf::Time deltaTime = clock.restart();
            timeSinceLastSpawn += deltaTime;
            manager.CheckForPlayerLost(); 
            if (timeSinceLastSpawn >= sf::seconds(2)) {
                manager.CreateEnemyInRandomPosition();
                timeSinceLastSpawn = sf::Time::Zero;
            }
        } else if (shouldEndGame) {
            std::string timeAtWhichGameEnded = std::to_string(int(otherClock.getElapsedTime().asSeconds())); 
            clock.restart();
            // Show some text here that says the players lost, if i can get that to work damn
            scoreFile.open("score.txt", std::ios::out | std::ios::in); 
            loseText.RenderText(mainWindow);
            scoreFile << std::to_string(manager.getHighScore()); 
            scoreFile.close();
            bestTimeFile.open("t.txt", std::ios::out | std::ios::in); 
            bestTimeFile << timeAtWhichGameEnded;
            bestTimeFile.close();
        }

        mainWindow.WindowDisplay(); 
    }
    
    window = NULL;
    delete window;
    window = nullptr;  
    return EXIT_SUCCESS;
}
