#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include "bullet.h"

using namespace sf;

class Player {
public:
    sf::Clock clock;
    Texture texStanding;  // Texture for standing still
    Texture texMovingRight;  // Texture for moving right
    Texture texMovingLeft;   // Texture for moving left
    Sprite sprite;
    float speed = 0.4;
    int x, y;
    std::vector<Bullet> bullets;
    float fireRate = 0.2f; // Decreased firing rate for faster shooting
    int health = 3; // Player health
    int score = 0;  // Player score

    Player(std::string standingImagePath, std::string movingRightImagePath, std::string movingLeftImagePath) {
        // Load textures for different movements
        texStanding.loadFromFile(standingImagePath);
        texMovingRight.loadFromFile(movingRightImagePath);
        texMovingLeft.loadFromFile(movingLeftImagePath);

        // Set the initial texture to standing
        sprite.setTexture(texStanding);

        x = 720;
        y = 800;
        sprite.setPosition(x, y);
        sprite.setScale(0.5, 0.5);
    }

    void fire() {
        if (clock.getElapsedTime().asSeconds() >= fireRate) {
            float bulletX = sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
            float bulletY = sprite.getPosition().y;
            bullets.emplace_back(bulletX, bulletY, 800.0f); // Increased bullet speed for faster bullets
            clock.restart();
        }
    }

    void move(std::string s) {
    float delta_x = 0, delta_y = 0;
    if (s == "l") {
        delta_x = -1;
        currentDirection = "left";
    } else if (s == "r") {
        delta_x = 1;
        currentDirection = "right";
    } else if (s == "u") {
        delta_y = -1;
        // Ensure the player cannot move above the screen
        if (sprite.getPosition().y > 0) {
            delta_y *= speed;
        } else {
            delta_y = 0; // Stop vertical movement when at the top boundary
        }
    } else if (s == "d") {
        delta_y = 1;
        // Ensure the player cannot move beneath the screen
        if (sprite.getPosition().y < 900 - sprite.getGlobalBounds().height) {
            delta_y *= speed;
        } else {
            delta_y = 0; // Stop vertical movement when at the bottom boundary
        }
    }

    // Screen wrapping for horizontal movement
    if (s == "l" || s == "r") {
        // Wrap around from right to left
        if (sprite.getPosition().x <= -sprite.getGlobalBounds().width)
            sprite.setPosition(1440, sprite.getPosition().y);
        // Wrap around from left to right
        else if (sprite.getPosition().x >= 1440)
            sprite.setPosition(-sprite.getGlobalBounds().width, sprite.getPosition().y);
    }

    delta_x *= speed;
    sprite.move(delta_x, delta_y);
}

    void update(float deltaTime) {
        // Update bullets
        for (auto& bullet : bullets) {
            bullet.update(deltaTime);
        }

        // Remove bullets that are off-screen
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
            [](const Bullet& b) { return b.isOffScreen(); }), bullets.end());

        // Update animation based on key states
        updateAnimation();
    }

    void render(sf::RenderWindow& window) {
        window.draw(sprite);
        for (auto& bullet : bullets) {
            bullet.render(window);
        }
    }

    void decreaseHealth() {
        if (health > 0) {
            health--;
        }
    }

    bool isAlive() const {
        return health > 0;
    }

    void increaseScore(int points) {
        score += points;
    }

    int getHealth() const {
        return health;
    }

    int getScore() const {
        return score;
    }

private:
    std::string currentDirection = "standing"; // Current movement direction

    // Check if any movement key is pressed
    bool isMoving() const {
        return Keyboard::isKeyPressed(Keyboard::A) ||
               Keyboard::isKeyPressed(Keyboard::D) ||
               Keyboard::isKeyPressed(Keyboard::W) ||
               Keyboard::isKeyPressed(Keyboard::S);
    }

    // Update animation based on key states
    void updateAnimation() {
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            sprite.setTexture(texMovingLeft);
        } else if (Keyboard::isKeyPressed(Keyboard::D)) {
            sprite.setTexture(texMovingRight);
        } else if (!isMoving()) {
            sprite.setTexture(texStanding);
        }
    }
};
