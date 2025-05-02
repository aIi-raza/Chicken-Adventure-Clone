#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <fstream> 
#include "player.h"
#include "pause_menu.h"
#include "enemy.h"
#include "menu.h"
#include "gameover_menu.h"


const char title[] = "OOP-Project, Spring-2024";
using namespace sf;

class Game {
public:
    sf::RenderWindow* mainMenuWindow;
    Sprite background; // Game background sprite
    Texture bg_texture;
    Player* p; // Player
    Dragon* dragon;
    PauseMenu* pauseMenu;
    bool isPaused = false;

    std::vector<std::unique_ptr<Enemy>> enemies; // Vector to store enemies
    enum WaveType { ALPHA, BETA, GAMMA, MONSTER1, MONSTER2, MONSTER3 , DRAGON};
    WaveType currentWave;

    float dragonWaveTimer = 0.0f;

    Game(sf::RenderWindow* mainMenuWindow) : mainMenuWindow(mainMenuWindow), dragon(nullptr) {
        // Load game background
        p = new Player("img/pship1.png", "img/pship1R.png", "img/pship1L.png");
        if (!bg_texture.loadFromFile("img/background0.jpeg")) {
            std::cerr << "Error loading game background image!" << std::endl;
            return;
        }
        background.setTexture(bg_texture);
        background.setScale(1, 1);


        // Initialize pause menu
        Font font;
        if (!font.loadFromFile("font/cig.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
        }
        pauseMenu = new PauseMenu(1440, 900, font);



        // Start with the first wave
        currentWave = ALPHA;
        spawnWave(currentWave);
    }

    void start_game() {
        mainMenuWindow->setVisible(false);
        srand(time(0));
        RenderWindow window(VideoMode(1440, 900), title);
        Clock clock;
        float timer = 0;

        // Create text objects for displaying health and score
        Font font;
        if (!font.loadFromFile("font/cig.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
        }
        Text healthText;
        healthText.setFont(font);
        healthText.setCharacterSize(24);
        healthText.setFillColor(Color::White);
        healthText.setPosition(10, 10);

        Text scoreText;
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(10, 40);

             int score = 0;

        while (window.isOpen()) {
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

                if (currentWave == DRAGON && dragon != nullptr) {
        dragon->update(time);
        dragon->render(window);
    }

            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed) 
                    window.close();
                

                if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape) {
                    isPaused = !isPaused;
                }

                if (isPaused && e.type == Event::MouseButtonPressed) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (pauseMenu->isResumeButtonPressed(mousePos)) {
                        isPaused = false;
                    } else if (pauseMenu->isHomeButtonPressed(mousePos)) {
                        window.close();
                        mainMenuWindow->setVisible(true);
                        return;
                    }
                }
            }

            if (!isPaused) {
                    if (Keyboard::isKeyPressed(Keyboard::A))
                        p->move("l");
                    if (Keyboard::isKeyPressed(Keyboard::D))
                        p->move("r");
                    if (Keyboard::isKeyPressed(Keyboard::W))
                        p->move("u");
                    if (Keyboard::isKeyPressed(Keyboard::S))
                        p->move("d");
                    if (Keyboard::isKeyPressed(Keyboard::Space))
                        p->fire();

                p->update(time); // Update player and bullets

                // Update health and score text
                healthText.setString("Lifes: " + std::to_string(p->getHealth()));
                scoreText.setString("Score: " + std::to_string(p->getScore()));

                // Clear the window and draw the background
                window.clear(Color::Black);
                window.draw(background);

                // Render player and bullets
                p->render(window);

                // Update and render enemies
                updateEnemies(time, window);

                // Draw UI elements
                window.draw(healthText);
                window.draw(scoreText);

                // Handle collisions
                handleCollisions(window);

                // Check if wave is complete
                checkWaveCompletion();
            }

            if (isPaused) {
                pauseMenu->draw(window);
            }

            window.display();  // Display all the sprites
        }
    }

private:
void spawnWave(WaveType wave) {
    switch (wave) {
        case ALPHA:
            alphaWave();
            break;
        case BETA:
            betaWave();
            break;
        case GAMMA:
            gammaWave();
            break;
        case MONSTER1:
            monster1Wave();
            break;
        case MONSTER2:
            monster2Wave();
            break;
        case MONSTER3:
            monster3Wave();
            break;
        case DRAGON:
            spawnDragon();
            break;
    }
}    


    void alphaWave() {
        // Parameters for the grid layout
        const int rows = 3;    // Number of rows in the grid
        const int cols = 5;    // Number of columns in the grid
        const float startX = 550.0f; // Starting X position
        const float startY = 100.0f; // Starting Y position
        const float offsetX = 100.0f; // Horizontal spacing between enemies
        const float offsetY = 100.0f; // Vertical spacing between enemies

        // Loop to create enemies in a grid layout
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                float x = startX + col * offsetX;
                float y = startY + row * offsetY;
                enemies.push_back(std::make_unique<Invader>(Invader::Alpha, x, y));
            }
        }
    }

    void betaWave() {
        // Parameters for the grid layout
        const int rows = 3;    // Number of rows in the grid
        const int cols = 5;    // Number of columns in the grid
        const float startX = 550.0f; // Starting X position
        const float startY = 100.0f; // Starting Y position
        const float offsetX = 100.0f; // Horizontal spacing between enemies
        const float offsetY = 100.0f; // Vertical spacing between enemies

        // Loop to create enemies in a grid layout
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                float x = startX + col * offsetX;
                float y = startY + row * offsetY;
                enemies.push_back(std::make_unique<Invader>(Invader::Beta, x, y));
            }
        }
    }

    void gammaWave() {
        // Parameters for the grid layout
        const int rows = 3;    // Number of rows in the grid
        const int cols = 5;    // Number of columns in the grid
        const float startX = 550.0f; // Starting X position
        const float startY = 100.0f; // Starting Y position
        const float offsetX = 100.0f; // Horizontal spacing between enemies
        const float offsetY = 100.0f; // Vertical spacing between enemies

        // Loop to create enemies in a grid layout
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                float x = startX + col * offsetX;
                float y = startY + row * offsetY;
                enemies.push_back(std::make_unique<Invader>(Invader::Gamma, x, y));
            }
        }
    }

    void monster1Wave() {
        // Spawn a single instance of Monster 1
        float x = 680.0f; // X position
        float y = 100.0f; // Y position
        enemies.push_back(std::make_unique<Monster>(Monster::Level1, x, y));
    }

    void monster2Wave() {
        // Spawn a single instance of Monster 2
        float x = 380.0f; // X position
        float y = 100.0f; // Y position
        enemies.push_back(std::make_unique<Monster>(Monster::Level2, x, y));
    }

    void monster3Wave() {
        // Spawn a single instance of Monster 3
        float x = 530.0f; // X position
        float y = 100.0f; // Y position
        enemies.push_back(std::make_unique<Monster>(Monster::Level3, x, y));
    }

void spawnDragon() {
    // Position the dragon in the middle of the screen
    float x = 720.0f; // X position (centered horizontally)
    float y = 100.0f; // Y position

    // Create the dragon instance
    dragon = new Dragon(x, y);

    // Add the dragon to the enemies vector
    enemies.push_back(std::unique_ptr<Enemy>(dragon));

    // Update current wave to DRAGON
    currentWave = DRAGON;
}

void updateEnemies(float time, RenderWindow& window) {
    for (auto& enemy : enemies) {
        enemy->update(time);
        enemy->render(window);
    }

    // Handle dragon wave timer
    if (currentWave == DRAGON) {
        dragonWaveTimer += time;
        if (dragonWaveTimer >= 5.0f) {
            // Remove dragon and proceed to monster level 3 wave
            enemies.clear(); // Ensure all enemies (including dragon) are removed
            currentWave = MONSTER3;
            dragonWaveTimer = 0.0f; // Reset timer
            spawnWave(currentWave);
        }
    }
}


void handleCollisions(sf::RenderWindow& window) {
    // Handle bullet and enemy collisions
    for (auto bulletIt = p->bullets.begin(); bulletIt != p->bullets.end(); ) {
        bool bulletRemoved = false;
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
            if (bulletIt->getBounds().intersects((*enemyIt)->getBounds())) {
                // Collision detected, decrement enemy health
                (*enemyIt)->decrementHealth();

                // Check if enemy health is zero, if so, erase it and update score
                if ((*enemyIt)->getHealth() <= 0) {
                    p->increaseScore((*enemyIt)->getScore());
                    enemyIt = enemies.erase(enemyIt);
                } else {
                    ++enemyIt;
                }

                // Remove bullet
                bulletIt = p->bullets.erase(bulletIt);
                bulletRemoved = true;
                break;
            } else {
                ++enemyIt;
            }
        }

        if (!bulletRemoved) {
            ++bulletIt;
        }
    }

    // Handle player and enemy collisions
    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
        if (p->sprite.getGlobalBounds().intersects((*enemyIt)->getBounds())) {
            // Collision detected, decrement player and enemy health
            p->decreaseHealth();
            (*enemyIt)->decrementHealth();

            // Check if player health is zero, if so, handle game over logic
            if (!p->isAlive()) {
                // Display game over menu
                displayGameOverMenu(window);
            }

            // Check if enemy health is zero, if so, erase it and update score
            if ((*enemyIt)->getHealth() <= 0) {
                p->increaseScore((*enemyIt)->getScore());
                enemyIt = enemies.erase(enemyIt);
            } else {
                ++enemyIt;
            }

            // Reset player position to its original position
            p->sprite.setPosition(720,800);
        } else {
            ++enemyIt;
        }
    }
}
void displayGameOverMenu(sf::RenderWindow& window) {
    // Load the font for the menu
    sf::Font font;
    if (!font.loadFromFile("font/cig.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    GameOverMenu gameOverMenu(window.getSize().x, window.getSize().y, font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (gameOverMenu.isGameOverButtonPressed(sf::Vector2i(mousePos))) {
                    std::exit(EXIT_SUCCESS);
                }
            }
        }

        window.clear(sf::Color::Black);
        // Draw game over menu
        gameOverMenu.draw(window);
        window.display();
    }
}
void checkWaveCompletion() {
    if (enemies.empty()) {
        switch (currentWave) {
            case ALPHA:
                currentWave = MONSTER1;
                break;
            case MONSTER1:
                currentWave = BETA;
                break;
            case BETA:
                currentWave = MONSTER2;
                break;
            case MONSTER2:
                currentWave = GAMMA;
                break;
            case GAMMA:
                currentWave = DRAGON;
                break;
            case DRAGON:
                currentWave = MONSTER3;
                break;
            case MONSTER3:
                // Game completed or restart waves
                // Here you can decide what to do after the final wave
                break;
        }
        spawnWave(currentWave);
    }
}

};

#endif // GAME_H
