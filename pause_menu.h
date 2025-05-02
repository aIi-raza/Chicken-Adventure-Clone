#include <SFML/Graphics.hpp>

class PauseMenu {
public:
    sf::Sprite resumeButton;
    sf::Sprite homeButton;
    sf::Text resumeText;
    sf::Text homeText;

    PauseMenu(float width, float height, sf::Font& font) {
        // Load button textures
        if (!resumeTexture.loadFromFile("img/resume_button.png")) {
            std::cerr << "Error loading resume button image!" << std::endl;
        }
        resumeButton.setTexture(resumeTexture);
        resumeButton.setPosition(width / 2 - 100, height / 2 - 60);

        if (!homeTexture.loadFromFile("img/home_button.png")) {
            std::cerr << "Error loading home button image!" << std::endl;
        }
        homeButton.setTexture(homeTexture);
        homeButton.setPosition(width / 2 - 100, height / 2 + 10);

        // Initialize texts
        resumeText.setFont(font);
        resumeText.setString(" ");
        resumeText.setCharacterSize(24);
        resumeText.setFillColor(sf::Color::White);
        resumeText.setPosition(953, 381);

        homeText.setFont(font);
        homeText.setString(" ");
        homeText.setCharacterSize(24);
        homeText.setFillColor(sf::Color::White);
        homeText.setPosition(953, 452);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(resumeButton);
        window.draw(homeButton);
        window.draw(resumeText);
        window.draw(homeText);
    }

    bool isResumeButtonPressed(sf::Vector2i mousePos) {
        return resumeButton.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }

    bool isHomeButtonPressed(sf::Vector2i mousePos) {
        return homeButton.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }

private:
    sf::Texture resumeTexture;
    sf::Texture homeTexture;
};