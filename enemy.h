#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath> // Include cmath for sin function

class Enemy {
public:
    virtual ~Enemy() = default;
    enum Type { ALPHA, BETA, GAMMA };
     Type type;
    // float health;  // Add health attribute
    float speed;
    float health;
    virtual int getScore() const = 0;
        // Function to decrement enemy's health
    void decrementHealth() {
        health--;
    }

    // Function to get enemy's health
    int getHealth() const {
        return health;
    }
    Type getType() const {
        return type;
    }


    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual void shoot() = 0;


protected:
    Enemy(Type type, float startX, float startY)
        : type(type), x(startX), y(startY) {
        // Initialize sprite, position, etc.
    }
    
    float x, y;
    sf::Sprite sprite;
    sf::Texture texture;

};

class Invader : public Enemy {
public:
    enum Type { Alpha, Beta, Gamma };

    Invader(Type type, float startX, float startY, float scale = 1.0f)
        : Enemy(static_cast<Enemy::Type>(type), startX, startY), invaderType(type) {
        switch (invaderType) {
            case Alpha:
                if (!texture.loadFromFile("img/alpha.png")) {
                    std::cerr << "Error loading Alpha invader texture!" << std::endl;
                }
                speed = 10.0f;
                health = 1.0f;
                sprite.setScale(0.7, 0.7);
                break;
            case Beta:
                if (!texture.loadFromFile("img/beta.png")) {
                    std::cerr << "Error loading Beta invader texture!" << std::endl;
                }
                speed = 15.0f;
                health = 1.0f;
                sprite.setScale(0.57, 0.57); // Adjust scale for Beta invader
                break;
            case Gamma:
                if (!texture.loadFromFile("img/gamma.png")) {
                    std::cerr << "Error loading Gamma invader texture!" << std::endl;
                }
                speed = 20.0f;
                health = 2.0f;
                sprite.setScale(0.60, 0.60); // Adjust scale for Gamma invader
                break;
        }
        sprite.setTexture(texture);
        sprite.setPosition(startX, startY);
    }

    void update(float deltaTime) override {
        // Adjust the bounce height and frequency as needed
        float bounceHeight = 6.0f; // Adjust the bounce height
        float bounceFrequency = 0.5f; // Adjust the bounce frequency

        // Calculate the vertical displacement using a sine wave
        float displacement = bounceHeight * std::sin(bounceFrequency * y);

        // Update the sprite position
        sprite.setPosition(x, y + displacement);

        // Move the invader downwards
        y += speed * deltaTime;
    }

    void render(sf::RenderWindow& window) override {
        window.draw(sprite);
    }

    sf::FloatRect getBounds() const override {
        return sprite.getGlobalBounds();
    }

    void shoot() override {
        // Implement shoot behavior based on invader type
        switch (invaderType) {
            case Alpha:
                // Alpha invader shooting behavior
                break;
            case Beta:
                // Beta invader shooting behavior
                break;
            case Gamma:
                // Gamma invader shooting behavior
                break;
        }
    }

    int getScore() const override {
        switch (invaderType) {
            case Alpha:
                return 10;
            case Beta:
                return 20;
            case Gamma:
                return 30;
        }
        return 0;
    }


private:
    Type invaderType;
    float timeSinceLastShot; // Time since the last shot
    float shotInterval; // Interval between shots
};

class Monster : public Enemy {
public:
    enum Level { Level1, Level2, Level3 };

    Monster(Level level, float startX, float startY, float scale = 1.0f)
        : Enemy(Enemy::Type::GAMMA, startX, startY), monsterLevel(level) {
        switch (monsterLevel) {
            case Level1:
                if (!texture.loadFromFile("img/monster1.png")) {
                    std::cerr << "Error loading Level 1 monster texture!" << std::endl;
                }
                speed = 300.0f;
                health = 5.0f;
                sprite.setScale(0.9, 0.9);
                break;
            case Level2:
                if (!texture.loadFromFile("img/monster2.png")) {
                    std::cerr << "Error loading Level 2 monster texture!" << std::endl;
                }
                speed = 350.0f;
                health = 7.0f;
                sprite.setScale(0.4, 0.4);
                break;
            case Level3:
                if (!texture.loadFromFile("img/monster3.png")) {
                    std::cerr << "Error loading Level 3 monster texture!" << std::endl;
                }
                speed = 400.0f;
                health = 10.0f;
                sprite.setScale(0.55, 0.55);
                break;
        }
        sprite.setTexture(texture);
        sprite.setPosition(startX, startY);
    }

void update(float deltaTime) override {
    // Check if the monster has reached the left or right edge of the screen
    if (sprite.getPosition().x <= 350 || sprite.getPosition().x >= 1150 - sprite.getGlobalBounds().width) {
        // Reverse the direction of movement if the edge is reached
        speed *= -1;
    }

    // Update the position of the monster based on its speed
    sprite.move(speed * deltaTime, 0);
}

    void render(sf::RenderWindow& window) override {
        window.draw(sprite);
    }

    sf::FloatRect getBounds() const override {
        return sprite.getGlobalBounds();
    }

    void shoot() override {
        // Monster shooting behavior
    }

    int getScore() const override {
        switch (monsterLevel) {
            case Level1:
                return 40;
            case Level2:
                return 45;
            case Level3:
                return 50;
        }
        return 0;
    }

private:
    Level monsterLevel;
};

class Dragon : public Enemy {
public:
    Dragon(float startX, float startY, float scale = 0.4f)
        : Enemy(Enemy::Type::GAMMA, startX, startY), diving(false), diveTimer(0.0f) {
        if (!texture.loadFromFile("img/dragon.png")) {
            std::cerr << "Error loading dragon texture!" << std::endl;
        }
        speed = 200.0f; // Adjust speed to match the game requirements
        health = 1000.0f;
        sprite.setTexture(texture);
        sprite.setScale(scale, scale);
        sprite.setPosition(startX, startY);
    }

    void update(float deltaTime) override {
        // Horizontal movement with boundary check
        if (sprite.getPosition().x <= 0 || sprite.getPosition().x >= 1440 - sprite.getGlobalBounds().width) {
            speed *= -1; // Reverse direction on boundary collision
        }
        sprite.move(speed * deltaTime, 0);

        // Diving motion
        float bounceHeight = 50.0f; // Adjust bounce height
        float bounceFrequency = 2.0f; // Adjust bounce frequency
        float displacement = bounceHeight * std::sin(bounceFrequency * y);
        sprite.setPosition(sprite.getPosition().x, y + displacement);

        y += deltaTime; // Increment y to create the wave effect
    }

    void render(sf::RenderWindow& window) override {
        window.draw(sprite);
    }

    sf::FloatRect getBounds() const override {
        return sprite.getGlobalBounds();
    }

    void shoot() override {
        // Dragon shooting behavior
    }

    int getScore() const override {
        return 1000; // Return an appropriate score value for defeating a dragon
    }

private:
    sf::Texture texture;
    bool diving;
    float diveTimer;
    const float diveInterval = 5.0f; // Adjust the interval between dives
    const float diveSpeed = 200.0f; // Adjust the speed of the dive movement
};
#endif // ENEMY_H
