#ifndef GAMESCREEN_H_INCLUDED
#define GAMESCREEN_H_INCLUDED

#include "Food.h"
#include "Snake.h"
#include "SpecialFood.h"
#include <SFML/Graphics.hpp>

class GameScreen {
public:
    GameScreen();
    ~GameScreen();

    Snake& getSnake();
    Food& getFood();
    SpecialFood& getSpecialFood();

    void setScore(unsigned int score);
    void updateSpecialFoodTexture();

    void reset();
    void handleKeyPressed(const sf::Keyboard::Key& keyPressed);
    void tick(sf::RenderWindow& window);

private:
    static std::string padNumberWithZeros(unsigned int number, unsigned int pad);

    bool m_isMoving;

    Snake m_snake;
    SpecialFood m_specialFood;
    Food m_food;

    sf::RectangleShape m_specialFoodIcon;
    sf::RectangleShape m_line;
    sf::RectangleShape m_playground;
    sf::Font m_font;
    sf::Text m_scoreText;
    sf::Text m_timerText;
};

#endif // GAMESCREEN_H_INCLUDED
