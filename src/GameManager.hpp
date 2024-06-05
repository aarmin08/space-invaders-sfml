#pragma once

#include "Enemy.hpp"
#include "Bullet.hpp" 

#include <iostream>

#include <SFML/System/Clock.hpp>

#include <ostream>
#include <random>
#include <chrono>
#include <thread>


#include "Window.hpp"
#include "Audio.hpp"

class GameManager {
private: 
    std::vector<Enemy> enemies; 
    int numberOfEnemiesToSpawn = 2; 
    float timeElapsedInSeconds; 

    std::vector<Bullet> bullets; 
    std::vector<int> enemiesToRemove; 
    std::vector<int> bulletsToRemove; 

    std::vector<int> enemiesCrossed; 
    bool spacebarwaspressed = false; 

    int threshold = 75;

    int positions[5] = {-300, -200, -100, 100, 200};
    int positionsY[5] = {-600, -650, -450, -500, -490};
    float speeds[5] = {0.05f, 0.07f, 0.08f, 0.09f, 0.04f}; 

    int iteration;
    int PlayerScore = 0; 
    bool playerLost = false;
    int HighScore = 0; 
    int bestTime = 0; 

    Audio audio;

    float incrementWave = 0.0f; 

public:
    void GameManagerSetup() {
        audio.LoadAudio("./Assets/expl.mp3");
    }
    void CreateEnemyInRandomPosition() {
        for (int i = 0; i < 6; i++) {
            Enemy enemy(positions[i], positionsY[i], 0.03f + incrementWave, "./Assets/c.png");
            enemy.CreateEnemy();
            enemies.push_back(enemy);
        } 

        incrementWave += 0.01f; 

        PlayerScore += 20;
    }

    void SetHighScore(int prevScore) { HighScore = prevScore; }

    void ManagerEnemyUpdate(Window& window) {
        for (auto& enemy : enemies) {
            enemy.MoveEnemy();
            enemy.DrawEnemies(window);
        }
    }

    void CreateBullet(Bullet bullet) {
        bullet.Create("./Assets/b.png"); 
        bullets.push_back(bullet); 
    }

    
    void BulletUpdate(Window& window) {
        for (auto it = bullets.begin(); it != bullets.end(); ) {
            if (it->shouldRemove(5.f)) {
                it = bullets.erase(it); 
            } else {
                it->BulletUpdate(window);
                ++it; 
            }
        }
    }

    int GetBestTime() { return bestTime; }

    void SetBestTime(int time) {
        if (time > bestTime) {
            bestTime = time;
        }
    }

    int getHighScore() {
        return HighScore;
    }

    void CheckForBulletAndEnemyInteractions() {
        for (size_t i = 0; i < bullets.size(); ++i) {
            bool bulletHit = false;
            for (size_t j = 0; j < enemies.size(); ++j) {
                if (bullets[i].getSprite().getGlobalBounds().intersects(enemies[j].getSprite().getGlobalBounds())) {
                    Audio audio1;
                    audio1.LoadAudio("./Assets/expl.mp3"); 
                    enemiesToRemove.push_back(j);
                    bulletHit = true;
                    PlayerScore+= 10;
                    audio.PlaySound();
                    //break; 
                }
            }
            if (bulletHit) {
                bulletsToRemove.push_back(i);
            }
        }
        for (int index : bulletsToRemove) {
            bullets.erase(bullets.begin() + index);
        }
                
        for (int index : enemiesToRemove) {
            enemies.erase(enemies.begin() + index);
        }
        bulletsToRemove.clear();
        enemiesToRemove.clear();
    }
    
    int getScore() { return PlayerScore; }

    /// @brief Check enemy position to see whether theyve crossed a certain thershold
    void CheckForLosePointCondition() {
        // Check every enemies position to see whether they have crossed a certan threshold 
        // If they cross that threshold, destroy them and deduct the players points
        // Just a matter of calculating the threshold now 
        for (size_t i = 0; i < enemies.size(); i++) {
            if (enemies[i].getSprite().getPosition().y > threshold) {
                // lose points here 
                // destroy the enemies too here
                PlayerScore -= 20; 
                enemiesCrossed.push_back(i); 
            }
        }

        for (int i : enemiesCrossed) {
            enemies.erase(enemies.begin() + i); 
        }

        enemiesCrossed.clear();
    } 

    void CalculateHighScore() {
        if (PlayerScore >= HighScore) {
            HighScore = PlayerScore; 
        }
    }

    void CheckForPlayerLost() {
        if (PlayerScore <= -40) {
            playerLost = true; 
        }
    }

    bool getPlayerCondition() { return playerLost; }
}; 
