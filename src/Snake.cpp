#include "ConfigConstants.h"
#include "GameScreen.h"
#include "Snake.h"

Snake::Snake() {
    m_speed = DEFAULT_SNAKE_SPEED;

    for (unsigned int i = 0; i < HEAD_VARIATIONS; ++i)
        for (unsigned int j = 0; j < DIRECTIONS; ++j) {
            sf::Texture* texture = new sf::Texture();
            texture -> loadFromFile(TEXTURE_DIRECTORY + HEAD_TEXTURES[i][j] + TEXTURE_EXTENSION);
            m_headTextures[i][j] = texture;
        }

    for (unsigned int i = 0; i < BODY_VARIATIONS; ++i)
        for (unsigned int j = 0; j < DIRECTIONS; ++j) {
            sf::Texture* texture = new sf::Texture();
            texture -> loadFromFile(TEXTURE_DIRECTORY + BODY_TEXTURES[i][j] + TEXTURE_EXTENSION);
            m_bodyTextures[i][j] = texture;
        }

    for (unsigned int i = 0; i < DIRECTIONS; ++i) {
        sf::Texture* texture = new sf::Texture();
        texture -> loadFromFile(TEXTURE_DIRECTORY + TAIL_TEXTURES[i] + TEXTURE_EXTENSION);
        m_tailTextures[i] = texture;
    }

    reset();
}

Snake::~Snake() {
    clearQueue();

    for (unsigned int i = 0; i < HEAD_VARIATIONS; ++i)
        for (unsigned int j = 0; j < DIRECTIONS; ++j)
            delete m_headTextures[i][j];

    for (unsigned int i = 0; i < BODY_VARIATIONS; ++i)
        for (unsigned int j = 0; j < DIRECTIONS; ++j)
            delete m_bodyTextures[i][j];

    for (unsigned int i = 0; i < DIRECTIONS; ++i)
        delete m_tailTextures[i];
}

const std::deque<SnakeBodyBlock*>& Snake::getBody() const {
    return m_snakeBody;
}

const sf::Vector2f& Snake::getHeadPosition() const {
    return m_snakeBody.back() -> shape.getPosition();
}

unsigned int Snake::getSpeed() const {
    return m_speed;
}

unsigned int Snake::getScore() const {
    return m_score;
}

bool Snake::hasLost() const {
    return m_lost;
}

Direction Snake::getDirection() const {
    return m_snakeBody.back() -> direction;
}

void Snake::setSpeed(unsigned int speed) {
    m_speed = speed;
}

void Snake::lose() {
    m_lost = true;
    m_snakeBody.back() -> direction = Direction::None;
}

void Snake::toggleLost() {
    m_lost = !m_lost;
}

void Snake::setDirection(Direction dir) {
    m_snakeBody.back() -> direction = dir;
    m_directionChanged = true;
}

void Snake::reset() {
    clearQueue();
    m_normalFoodEaten = 0;
    m_score = 0;
    m_lost = false;
    m_eaten = false;
    m_directionChanged = false;

    for (unsigned int i = 0; i < STARTING_BLOCKS; ++i) {
        SnakeBodyBlock* shape = createBlock(i * BLOCK_SIZE + STARTING_X, STARTING_Y, Direction::Right);
        shape -> shape.setTexture(m_bodyTextures[0][1]);
        m_snakeBody.push_back(shape);
    }

    m_snakeBody.front() -> shape.setTexture(m_tailTextures[1]);
}

void Snake::extend(const sf::Vector2f* nextPos) {
    // Prepare the extension
    SnakeBodyBlock* shape = createBlock(nextPos -> x, nextPos -> y, getDirection());

    // Apply the changes
    m_snakeBody.push_back(shape);
}

void Snake::move(const sf::Vector2f* nextPos) {
    SnakeBodyBlock* tail = m_snakeBody.front();

    // Prepare the tail for it to be the new head
    tail -> shape.setPosition(nextPos -> x, nextPos -> y);
    tail -> direction = getDirection();

    // Apply the changes
    m_snakeBody.pop_front(); // Takes the tail away
    m_snakeBody.push_back(tail); // And puts at the new head position

    updateTailTexture();
}

void Snake::tick(GameScreen& gameScreen) {
    sf::Vector2f* nextPos = nextHeadPosition();

    if (hasCollided(nextPos))
        gameScreen.reset();
    else {
        bool eaten = hasEaten(gameScreen, nextPos);

        if (eaten) {
            Food& food = gameScreen.getFood();
            SpecialFood& specialFood = gameScreen.getSpecialFood();
            extend(nextPos);

            if (*nextPos == food.getPosition()) {
                m_score += FOOD_SCORE;

                if (m_normalFoodEaten >= 4) {
                    m_normalFoodEaten = 0;
                    food.reset();
                    specialFood.randomizePosition(*this, food);
                    gameScreen.updateSpecialFoodTexture();
                } else
                    ++m_normalFoodEaten;

                food.randomizePosition(*this, specialFood);
            } else {
                m_score += SPECIAL_FOOD_SCORE + 2 * specialFood.getTimeToLive();
                specialFood.reset();
            }

            gameScreen.setScore(m_score);
        } else
            move(nextPos);

        // Update some textures
        updateHeadTexture(gameScreen);
        updateBodyTexture(m_snakeBody.size() - 2);
        m_eaten = eaten;
    }

    delete nextPos;
}

void Snake::render(sf::RenderWindow &window) {
    for (auto shape : m_snakeBody)
        window.draw(shape -> shape);
}

sf::Vector2f* Snake::nextHeadPosition() const {
    sf::Vector2f headPos = getHeadPosition();

    switch (getDirection()) {
        case Direction::Left:
            headPos.x -= BLOCK_SIZE;

            if (headPos.x < START_PLAYGROUND_X)
                headPos.x = END_PLAYGROUND_X;
            break;
        case Direction::Right:
            headPos.x += BLOCK_SIZE;

            if (headPos.x > END_PLAYGROUND_X)
                headPos.x = START_PLAYGROUND_X;
            break;
        case Direction::Up:
            headPos.y -= BLOCK_SIZE;

            if (headPos.y < START_PLAYGROUND_Y)
                headPos.y = END_PLAYGROUND_Y;
            break;
        case Direction::Down:
            headPos.y += BLOCK_SIZE;

            if (headPos.y > END_PLAYGROUND_Y)
                headPos.y = START_PLAYGROUND_Y;
            break;
        default:
            break;
    }

    return new sf::Vector2f(headPos);
}

SnakeBodyBlock* Snake::createBlock(int x, int y, Direction dir) const {
    sf::RectangleShape shape({ BLOCK_SIZE, BLOCK_SIZE });
    shape.setFillColor(OBJECTS_COLOR);
    shape.setPosition(x, y);

    return new SnakeBodyBlock({ shape, dir });
}

bool Snake::hasCollided(const sf::Vector2f* nextPos) const {
    for (int i = m_snakeBody.size() - 4; i >= 0; --i)
        if (*nextPos == m_snakeBody[i] -> shape.getPosition())
            return true;

    return false;
}

bool Snake::hasEaten(GameScreen& gameScreen, const sf::Vector2f* nextPos) const {
    sf::Vector2f foodPos = gameScreen.getFood().getPosition();

    if (*nextPos == foodPos)
        return true;

    SpecialFood& specialFood = gameScreen.getSpecialFood();

    if (specialFood.isActive()) {
        sf::Vector2f specialFoodPos = specialFood.getPosition();
        sf::Vector2f specialFoodPos2 = { specialFoodPos.x + BLOCK_SIZE, specialFoodPos.y };
        return *nextPos == specialFoodPos || *nextPos == specialFoodPos2;
    }

    return false;
}

unsigned int Snake::getDirectionIndex(Direction dir) const {
    switch (dir) {
        case Direction::Left:
            return 0;
        case Direction::Right:
            return 1;
        case Direction::Up:
            return 2;
        case Direction::Down:
            return 3;
        default:
            return 4;
    }
}

unsigned int Snake::getBodyDirectionIndex(Direction prevDir, Direction dir) const {
    if (prevDir == dir)
        return getDirectionIndex(dir);

    if ((prevDir == Direction::Right && dir == Direction::Up) ||
        (prevDir == Direction::Down && dir == Direction::Left))
        return 0;

    if ((prevDir == Direction::Right && dir == Direction::Down) ||
        (prevDir == Direction::Up && dir == Direction::Left))
        return 1;

    if ((prevDir == Direction::Left && dir == Direction::Up) ||
        (prevDir == Direction::Down && dir == Direction::Right))
        return 2;

    if ((prevDir == Direction::Left && dir == Direction::Down) ||
        (prevDir == Direction::Up && dir == Direction::Right))
        return 3;

    return 4;
}

void Snake::clearQueue() {
    while (!m_snakeBody.empty()) {
        delete m_snakeBody.front();
        m_snakeBody.pop_front();
    }
}

void Snake::updateHeadTexture(GameScreen& gameScreen) {
    sf::Vector2f* nextPos = nextHeadPosition();
    unsigned int i = hasEaten(gameScreen, nextPos);
    SnakeBodyBlock* headBlock = m_snakeBody.back();
    unsigned int j = getDirectionIndex(headBlock -> direction);
    headBlock -> shape.setTexture(m_headTextures[i][j]);
    delete nextPos;
}

void Snake::updateBodyTexture(unsigned int index) {
    unsigned int i = m_eaten + 2 * m_directionChanged;
    unsigned int j = getBodyDirectionIndex(m_snakeBody[index - 1] -> direction, m_snakeBody[index] -> direction);
    m_snakeBody[index] -> shape.setTexture(m_bodyTextures[i][j]);
    m_eaten = false;
    m_directionChanged = false;
}

void Snake::updateTailTexture() {
    SnakeBodyBlock* tailBlock = m_snakeBody.front();
    unsigned int i = getDirectionIndex(tailBlock -> direction);
    tailBlock -> shape.setTexture(m_tailTextures[i]);
}
