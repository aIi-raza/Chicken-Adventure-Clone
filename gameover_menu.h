#include <SFML/Graphics.hpp>

class GameOverMenu {
public:
    sf::Sprite gameOverBackground; // Background sprite for the game over menu
    sf::Sprite gameOverButton;
    sf::Text gameOverText;

    GameOverMenu(float width, float height, sf::Font& font) {
        // Load background texture
        if (!backgroundTexture.loadFromFile("img/gg.png")) {
            std::cerr << "Error loading game over background image!" << std::endl;
        }
        gameOverBackground.setTexture(backgroundTexture);

        // Set position of the background sprite to cover the window
        gameOverBackground.setPosition(0, 0);
        gameOverBackground.setScale(width / gameOverBackground.getLocalBounds().width, height / gameOverBackground.getLocalBounds().height);

        // Load button texture
        if (!gameOverTexture.loadFromFile("img/exit.png")) {
            std::cerr << "Error loading game over button image!" << std::endl;
        }
        gameOverButton.setTexture(gameOverTexture);
        gameOverButton.setPosition(30, 60);

        // Initialize text
        gameOverText.setFont(font);
        gameOverText.setString(" ");
        gameOverText.setCharacterSize(24);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setPosition(953, 452);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(gameOverBackground); // Draw the background first
        window.draw(gameOverButton);
        window.draw(gameOverText);
    }

    bool isGameOverButtonPressed(sf::Vector2i mousePos) {
        return gameOverButton.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }

private:
    sf::Texture backgroundTexture; // Texture for the background image
    sf::Texture gameOverTexture;
};
