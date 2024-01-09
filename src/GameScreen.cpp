#include "GameScreen.h"

GameScreen::GameScreen() {
    m_isMoving = false;
    m_food.randomizePosition(m_snake, m_specialFood);

    // Creates the objects of the UI
    m_font.loadFromFile(FONT_FILE);

    m_specialFoodIcon.setSize({ SPECIAL_FOOD_WIDTH, SPECIAL_FOOD_HEIGHT });
    m_specialFoodIcon.setPosition(SPECIAL_FOOD_X, SPECIAL_FOOD_Y);

    m_line.setSize({ LINE_WIDTH, LINE_HEIGHT });
    m_line.setFillColor(OBJECTS_COLOR);
    m_line.setPosition(LINE_X, LINE_Y);

    m_playground.setSize({ PLAYGROUND_WIDTH, PLAYGROUND_HEIGHT });
    m_playground.setFillColor(BACKGROUND_COLOR);
    m_playground.setOutlineThickness(PIXEL_SIZE);
    m_playground.setOutlineColor(OBJECTS_COLOR);
    m_playground.setPosition(PLAYGROUND_X, PLAYGROUND_Y);

    m_scoreText.setFont(m_font);
    m_scoreText.setFillColor(OBJECTS_COLOR);
    m_scoreText.setCharacterSize(TEXT_HEIGHT);
    m_scoreText.setString("0000");
    m_scoreText.setPosition(SCORE_X, SCORE_Y);

    m_timerText.setFont(m_font);
    m_timerText.setFillColor(OBJECTS_COLOR);
    m_timerText.setCharacterSize(TEXT_HEIGHT);
    m_timerText.setPosition(TIMER_X, TIMER_Y);
}

GameScreen::~GameScreen() { }

Snake& GameScreen::getSnake() {
    return m_snake;
}

Food& GameScreen::getFood() {
    return m_food;
}

SpecialFood& GameScreen::getSpecialFood() {
    return m_specialFood;
}

void GameScreen::setScore(unsigned int score) {
    m_scoreText.setString(padNumberWithZeros(score, SCORE_DIGIT_COUNT));
}

void GameScreen::updateSpecialFoodTexture() {
    m_specialFoodIcon.setTexture(m_specialFood.getTexture());
}

void GameScreen::reset() {
    m_snake.reset();
    m_specialFood.reset();
    m_food.randomizePosition(m_snake, m_specialFood);
}

void GameScreen::handleKeyPressed(const sf::Keyboard::Key& keyPressed) {
    if (!m_isMoving) {
        Direction dir = m_snake.getDirection();

        if (keyPressed == sf::Keyboard::Left && dir != Direction::Right) {
            m_snake.setDirection(Direction::Left);
            m_isMoving = true;
        } else if (keyPressed == sf::Keyboard::Right && dir != Direction::Left) {
            m_snake.setDirection(Direction::Right);
            m_isMoving = true;
        } else if (keyPressed == sf::Keyboard::Up && dir != Direction::Down) {
            m_snake.setDirection(Direction::Up);
            m_isMoving = true;
        } else if (keyPressed == sf::Keyboard::Down && dir != Direction::Up) {
            m_snake.setDirection(Direction::Down);
            m_isMoving = true;
        }
    }

    if (keyPressed == sf::Keyboard::Escape)
        m_snake.setDirection(Direction::None);
    else if (keyPressed == sf::Keyboard::R) {
        m_snake.reset();
        m_scoreText.setString("0000");
        m_food.randomizePosition(m_snake, m_specialFood);
    }
}

void GameScreen::tick(sf::RenderWindow& window) {
    // Update the snake's position
    if (m_snake.getDirection() != Direction::None) {
        m_snake.tick(*this);
        m_isMoving = false;

        if (m_specialFood.isActive()) {
            m_specialFood.tick();
            unsigned int timeToLive = m_specialFood.getTimeToLive();
            m_timerText.setString(padNumberWithZeros(timeToLive, TIMER_DIGIT_COUNT));
        }
    }

    if (!m_snake.hasLost()) {
        // Clear the window
        window.clear(BACKGROUND_COLOR);

        // Draw the objects of the UI
        window.draw(m_scoreText);
        window.draw(m_line);
        window.draw(m_playground);

        // Draw the snake and food
        m_snake.render(window);
        m_food.render(window);

        if (m_specialFood.isActive()) {
            window.draw(m_specialFoodIcon);
            window.draw(m_timerText);
            m_specialFood.render(window);
        }
    }
}

std::string GameScreen::padNumberWithZeros(unsigned int number, unsigned int pad) {
    std::string numberString = std::to_string(number);
    int padCount = pad - numberString.length();
    return std::string(padCount, '0') + numberString;
}
