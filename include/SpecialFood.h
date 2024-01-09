#ifndef SPECIALFOOD_H_INCLUDED
#define SPECIALFOOD_H_INCLUDED

#include "ConfigConstants.h"
#include <SFML/Graphics.hpp>

class Snake;
class Food;

class SpecialFood {
public:
    SpecialFood();
    ~SpecialFood();

    bool isActive() const;
    unsigned int getTimeToLive() const;
    // get the position of special food
    const sf::Vector2f& getPosition() const;
    // get the active texture of special food
    const sf::Texture* getTexture() const;

    // resets special food to starting position
    void reset();
    // updates special food each tick
    void tick();
    // render food on screen
    void render(sf::RenderWindow &window);
    // randomly place special food on screen
    void randomizePosition(const Snake& snake, const Food& food);

private:
    bool hasCollidedWithObject(const Snake& snake, const Food& food, int x, int y) const;

    unsigned int m_timeToLive;
    sf::RectangleShape m_food;
    sf::Texture* m_textures[AMOUNT_SPECIAL_FOODS];
};

#endif // SPECIALFOOD_H_INCLUDED
