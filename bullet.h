#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet {
public:
    Bullet(float posX, float posY, float speed) : speed(speed) {
        if (!texture.loadFromFile("img/laser.png")) {
            std::cerr << "Error loading bullet texture!" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(posX, posY);
        sprite.setScale(0.4f, 0.4f); // Adjusted bullet size
        //std::cout << "Bullet created at: (" << posX << ", " << posY << ")" << std::endl;
    }

    void update(float deltaTime) {
        sprite.move(0, -speed * deltaTime);
        //std::cout << "Bullet position: (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")" << std::endl;
    }

    void render(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }

    bool isOffScreen() const {
        return sprite.getPosition().y + sprite.getGlobalBounds().height < 0;
    }

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
};
