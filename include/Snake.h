#ifndef SNAKE_H
#define SNAKE_H

#include "Food.h"
#include "SpecialFood.h"
#include <SFML/Graphics.hpp>
#include <queue>

enum class Direction {
    None,
    Up,
    Down,
    Left,
    Right
};

struct SnakeBodyBlock {
    sf::RectangleShape shape;
    Direction direction;
};

class GameScreen;

class Snake {
public:
    Snake();
    ~Snake();

    // gets the body of snake
    const std::deque<SnakeBodyBlock*>& getBody() const;
    // gets head position of snake
    const sf::Vector2f& getHeadPosition() const;
    // gets speed of snake
    unsigned int getSpeed() const;
    // gets current score
    unsigned int getScore() const;
    // checks if snake has lost
    bool hasLost() const;
    // gets direction of movement
    Direction getDirection() const;

    // sets speed of snake
    void setSpeed(unsigned int speed);
    // sets snake to lost state
    void lose();
    // toggles lost state
    void toggleLost();
    // sets direction of movement
    void setDirection(Direction dir);

    // resets snake to starting position
    void reset();
    // extends snake by one block
    void extend(const sf::Vector2f* nextPos);
    // moves snake by one block
    void move(const sf::Vector2f* nextPos);
    // updates snake each tick
    void tick(GameScreen& gameScreen);
    // renders snake on screen
    void render(sf::RenderWindow &window);

private:
    sf::Vector2f* nextHeadPosition() const;
    // creates a new block for the body of the snake
    SnakeBodyBlock* createBlock(int x, int y, Direction dir) const;
    // checks for collision with walls or itself
    bool hasCollided(const sf::Vector2f* nextPos) const;
    bool hasEaten(GameScreen& gameScreen, const sf::Vector2f* nextPos) const;
    unsigned int getDirectionIndex(Direction dir) const;
    unsigned int getBodyDirectionIndex(Direction prevDir, Direction dir) const;

    // clears the snake body queue
    void clearQueue();
    void updateHeadTexture(GameScreen& gameScreen);
    void updateBodyTexture(unsigned int index);
    void updateTailTexture();

    std::deque<SnakeBodyBlock*> m_snakeBody;
    unsigned int m_normalFoodEaten;
    unsigned int m_speed;
    unsigned int m_score;
    bool m_lost;
    bool m_eaten;
    bool m_directionChanged;

    sf::Texture* m_headTextures[HEAD_VARIATIONS][DIRECTIONS];
    sf::Texture* m_bodyTextures[BODY_VARIATIONS][DIRECTIONS];
    sf::Texture* m_tailTextures[DIRECTIONS];
};

#endif // SNAKE_H
