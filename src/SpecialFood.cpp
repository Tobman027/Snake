#include "ConfigConstants.h"
#include "GameScreen.h"
#include "SpecialFood.h"

SpecialFood::SpecialFood() {
    for (unsigned int i = 0; i < AMOUNT_SPECIAL_FOODS; ++i) {
        sf::Texture* texture = new sf::Texture();
        texture -> loadFromFile(TEXTURE_DIRECTORY + SPECIAL_FOODS[i] + TEXTURE_EXTENSION);
        m_textures[i] = texture;
    }

    m_food.setSize({ SPECIAL_FOOD_WIDTH, SPECIAL_FOOD_HEIGHT });
    reset();
}

SpecialFood::~SpecialFood() {
    for (unsigned int i = 0; i < AMOUNT_SPECIAL_FOODS; ++i)
        delete m_textures[i];
}

bool SpecialFood::isActive() const {
    return m_timeToLive > 0;
}

unsigned int SpecialFood::getTimeToLive() const {
    return m_timeToLive;
}

const sf::Vector2f& SpecialFood::getPosition() const {
    return m_food.getPosition();
}

const sf::Texture* SpecialFood::getTexture() const {
    return m_food.getTexture();
}

void SpecialFood::reset() {
    m_timeToLive = 0;
    m_food.setPosition(0, 0);
}

void SpecialFood::tick() {
    if (isActive()) {
        if (m_timeToLive == 1)
            reset();
        else
            --m_timeToLive;
    }
}

void SpecialFood::render(sf::RenderWindow& window) {
    window.draw(m_food);
}

void SpecialFood::randomizePosition(const Snake& snake, const Food& food) {
    int x, y;
    srand(time(0));

    do {
        x = START_PLAYGROUND_X + (rand() % SPECIAL_PLAYGROUND_WIDTH_BLOCKS) * BLOCK_SIZE;
        y = START_PLAYGROUND_Y + (rand() % PLAYGROUND_HEIGHT_BLOCKS) * BLOCK_SIZE;
    } while (hasCollidedWithObject(snake, food, x, y));

    m_food.setPosition(x, y);
    m_timeToLive = SPECIAL_FOOD_LIFE;

    int randomIndex = rand() % AMOUNT_SPECIAL_FOODS;
    m_food.setTexture(m_textures[randomIndex]);
}

bool SpecialFood::hasCollidedWithObject(const Snake& snake, const Food& food, int x, int y) const {
    sf::Vector2f newPos = { (float) x, (float) y };
    sf::Vector2f newPos2 = { (float) (x + BLOCK_SIZE), (float) y };
    sf::Vector2f foodPos = food.getPosition();

    if (foodPos.y == newPos.y &&
        (foodPos.x == newPos.x || foodPos.x + BLOCK_SIZE == newPos2.x))
        return true;

    for (auto& block : snake.getBody()) {
        sf::Vector2f blockPos = block -> shape.getPosition();

        if (blockPos == newPos || blockPos == newPos2)
            return true;
    }

    return false;
}
