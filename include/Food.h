#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>

class Snake;
class SpecialFood;

class Food {
public:
    Food();
    ~Food();

    // get the position of food
    const sf::Vector2f& getPosition() const;

    // resets food to starting position
    void reset();
    // render food on screen
    void render(sf::RenderWindow &window);
    // randomly place food on screen
    void randomizePosition(const Snake& snake, const SpecialFood& specialFood);

private:
    bool hasCollidedWithObject(const Snake& snake, const SpecialFood& specialFood, int x, int y) const;

    sf::RectangleShape m_food;
    sf::Texture m_texture;
};


#endif // FOOD_H
