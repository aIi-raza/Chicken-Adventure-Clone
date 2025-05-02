#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "game.h"

using namespace sf;

class Menu {
public:
    // Constructor
    Menu() {
        // Load main menu font
        if (!font.loadFromFile("font/cig.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
            return;
        }

        // Load main menu background
        if (!bgTexture.loadFromFile("img/mmenu.png")) {
            std::cerr << "Error loading background image!" << std::endl;
            return;
        }
        bgSprite.setTexture(bgTexture);

        // Initialize buttons
        initializeButton(playButton, "img/play_button.png", playText, " ", 593, 452);
        initializeButton(leaderboardButton, "img/score_button.png", leaderboardText, " ", 593, 523);
        initializeButton(instructionsButton, "img/options_button.png", instructionsText, " ", 593, 594);
        initializeButton(quitButton, "img/quit_button.png", quitText, " ", 593, 722);
    }

    // Function to display the main menu
    void main_menu() {
        // Create the main menu window
        sf::RenderWindow menuWindow(sf::VideoMode(1440, 900), "Main Menu");

        // Main menu loop
        while (menuWindow.isOpen()) {
            sf::Event event;
            while (menuWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    menuWindow.close();
                }

                

                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mousePos = menuWindow.mapPixelToCoords(sf::Mouse::getPosition(menuWindow));

                    if (playButton.getGlobalBounds().contains(mousePos)) {
                        // Start the game when play button is clicked
                        Game g(&menuWindow); // Pass a pointer to the main menu window
                        g.start_game();
                    } else if (instructionsButton.getGlobalBounds().contains(mousePos)) {
                        // Handle instructions button click
                        menuWindow.close();
                        displayInstructions();
                    } else if (leaderboardButton.getGlobalBounds().contains(mousePos)) {
                        // Handle leaderboard button click
                        menuWindow.close();
                        displayLeaderboard();
                    } else if (quitButton.getGlobalBounds().contains(mousePos)) {
                        menuWindow.close(); // Close the window when quit button is clicked
                    }
                }
            }
            menuWindow.clear(sf::Color::Black); // Clear the menu window
            // Draw main menu elements here...
            menuWindow.draw(bgSprite); // Draw the background
            menuWindow.draw(playButton); // Draw the play button
            menuWindow.draw(playText); // Draw the play button text
            menuWindow.draw(instructionsButton); // Draw the instructions button
            menuWindow.draw(instructionsText); // Draw the instructions button text
            menuWindow.draw(leaderboardButton); // Draw the leaderboard button
            menuWindow.draw(leaderboardText); // Draw the leaderboard button text
            menuWindow.draw(quitButton); // Draw the quit button
            menuWindow.draw(quitText); // Draw the quit button text
            menuWindow.display(); // Display the menu window
        }
    }

private:
    sf::Font font; // Main menu font
    sf::Texture bgTexture; // Background texture
    sf::Sprite bgSprite; // Background sprite

    // Buttons and their texts
    sf::Sprite playButton;
    sf::Text playText;

    sf::Sprite instructionsButton;
    sf::Text instructionsText;

    sf::Sprite leaderboardButton;
    sf::Text leaderboardText;

    sf::Sprite quitButton;
    sf::Text quitText;

    // Function to initialize buttons with images
    void initializeButton(sf::Sprite& button, const std::string& imagePath, sf::Text& text, const std::string& buttonText, float posX, float posY) {
        sf::Texture* texture = new sf::Texture();
        if (!texture->loadFromFile(imagePath)) {
            std::cerr << "Error loading button image: " << imagePath << std::endl;
            return;
        }
        button.setTexture(*texture);
        button.setPosition(posX, posY);

        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        // Center the text on the button
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(button.getPosition().x + button.getGlobalBounds().width / 2.0f, button.getPosition().y + button.getGlobalBounds().height / 2.0f);
    }

    // Function to display the instructions menu
    void displayLeaderboard() {
        sf::RenderWindow leaderboardWindow(sf::VideoMode(1440, 900), "Leaderboard");

        sf::Texture leaderboardBgTexture;
        if (!leaderboardBgTexture.loadFromFile("img/leaderboard_menu.png")) {
            std::cerr << "Error loading leaderboard background image!" << std::endl;
            return;
        }
        sf::Sprite leaderboardBgSprite(leaderboardBgTexture);

        // Initialize the back button
        sf::Sprite backButton;
        sf::Text backText;
        initializeButton(backButton, "img/back_button.png", backText, " ", 30, 60);

        while (leaderboardWindow.isOpen()) {
            sf::Event event;
            while (leaderboardWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    leaderboardWindow.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mousePos = leaderboardWindow.mapPixelToCoords(sf::Mouse::getPosition(leaderboardWindow));
                    if (backButton.getGlobalBounds().contains(mousePos)) {
                        leaderboardWindow.close();
                        main_menu();
                    }
                }
            }

            leaderboardWindow.clear();
            leaderboardWindow.draw(leaderboardBgSprite);
            leaderboardWindow.draw(backButton);
            leaderboardWindow.draw(backText);
            leaderboardWindow.display();
        }
    }

    void displayInstructions() {
        sf::RenderWindow instructionsWindow(sf::VideoMode(1440, 900), "Instructions");

        // Load instructions content here
        sf::Texture instructionsTexture;
        if (!instructionsTexture.loadFromFile("img/instruction_menu.png")) {
            std::cerr << "Error loading instructions content image!" << std::endl;
            return;
        }
        sf::Sprite instructionsSprite(instructionsTexture);
        instructionsSprite.setPosition(0, 0); // Set position to top-left corner

        // Define a view for the instructions window
        sf::View view(sf::FloatRect(0, 0, 1440, 900)); // Full window view

        // Initialize the back button
        sf::Sprite backButton;
        sf::Text backText;
        initializeButton(backButton, "img/back_button.png", backText, "", 30, 60);

        float scrollSpeed = 40.0f; // Adjust scrolling speed

        while (instructionsWindow.isOpen()) {
            sf::Event event;
            while (instructionsWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    instructionsWindow.close();
                }

                // Handle mouse wheel events to scroll
                if (event.type == sf::Event::MouseWheelScrolled) {
                    if (event.mouseWheelScroll.delta > 0) {
                        // Scroll up
                        view.move(0, -scrollSpeed); // Adjust as needed
                    } else if (event.mouseWheelScroll.delta < 0) {
                        // Scroll down
                        view.move(0, scrollSpeed); // Adjust as needed
                    }

                    // Ensure that the view does not exceed the boundaries of the texture
                    sf::FloatRect textureBounds = instructionsSprite.getGlobalBounds();
                    if (view.getCenter().y - view.getSize().y / 2 < textureBounds.top) {
                        view.setCenter(view.getCenter().x, textureBounds.top + view.getSize().y / 2);
                    } else if (view.getCenter().y + view.getSize().y / 2 > textureBounds.top + textureBounds.height) {
                        view.setCenter(view.getCenter().x, textureBounds.top + textureBounds.height - view.getSize().y / 2);
                    }
                }

                // Handle back button click
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mousePos = instructionsWindow.mapPixelToCoords(sf::Mouse::getPosition(instructionsWindow));
                    if (backButton.getGlobalBounds().contains(mousePos)) {
                        instructionsWindow.close();
                        main_menu();
                    }
                }
            }

            instructionsWindow.clear();
            instructionsWindow.setView(view);
            instructionsWindow.draw(instructionsSprite);
            instructionsWindow.draw(backButton);
            instructionsWindow.draw(backText);
            instructionsWindow.display();
        }
    }
};

#endif // MENU_H