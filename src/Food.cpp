#include "ConfigConstants.h"
#include "Food.h"
#include "GameScreen.h"
#include <cstdlib>
#include <ctime>

Food::Food() {
    m_texture.loadFromFile(TEXTURE_DIRECTORY + "food" + TEXTURE_EXTENSION);
    m_food.setTexture(&m_texture);
    m_food.setSize({ FOOD_SIZE, FOOD_SIZE });
}

Food::~Food() { }

const sf::Vector2f& Food::getPosition() const {
    return m_food.getPosition();
}

void Food::reset() {
    m_food.setPosition(0, 0);
}

void Food::render(sf::RenderWindow& window) {
    window.draw(m_food);
}

void Food::randomizePosition(const Snake& snake, const SpecialFood& specialFood) {
    int x, y;
    srand(time(0));

    do {
        x = START_PLAYGROUND_X + (rand() % PLAYGROUND_WIDTH_BLOCKS) * BLOCK_SIZE;
        y = START_PLAYGROUND_Y + (rand() % PLAYGROUND_HEIGHT_BLOCKS) * BLOCK_SIZE;
    } while (hasCollidedWithObject(snake, specialFood, x, y));

    m_food.setPosition(x, y);
}

bool Food::hasCollidedWithObject(const Snake& snake, const SpecialFood& specialFood, int x, int y) const {
    sf::Vector2f newPos = { (float) x, (float) y };
    sf::Vector2f specialFoodPos = specialFood.getPosition();

    if (specialFoodPos.y == newPos.y &&
        (specialFoodPos.x == newPos.x || specialFoodPos.x + BLOCK_SIZE == newPos.x))
        return true;

    for (auto& block : snake.getBody())
        if (block -> shape.getPosition() == newPos)
            return true;

    return false;
}
