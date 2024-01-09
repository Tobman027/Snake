#include "ConfigConstants.h"
#include "GameScreen.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game");
    window.setFramerateLimit(std::min(DEFAULT_SNAKE_SPEED, FRAMERATE_LIMIT));

    GameScreen gameScreen;

    // Main loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
                gameScreen.handleKeyPressed(event.key.code);
        }

        gameScreen.tick(window);

        // Display the window
        window.display();
    }

    return 0;
}
