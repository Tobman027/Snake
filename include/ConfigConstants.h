#ifndef CONFIGCONSTANTS_H_INCLUDED
#define CONFIGCONSTANTS_H_INCLUDED

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

const unsigned int PIXEL_SIZE = 11;
const unsigned int BLOCK_SIZE = 4 * PIXEL_SIZE;
const unsigned int WINDOW_WIDTH = 92 * PIXEL_SIZE;
const unsigned int WINDOW_HEIGHT = 52 * PIXEL_SIZE;
const unsigned int LINE_WIDTH = 84 * PIXEL_SIZE;
const unsigned int LINE_HEIGHT = PIXEL_SIZE;
const unsigned int LINE_X = 4 * PIXEL_SIZE;
const unsigned int LINE_Y = 8 * PIXEL_SIZE;
const unsigned int TEXT_WIDTH = 3 * PIXEL_SIZE;
const unsigned int TEXT_HEIGHT = 5 * PIXEL_SIZE;
const unsigned int SCORE_X = LINE_X + PIXEL_SIZE;
const unsigned int SCORE_Y = LINE_Y - TEXT_HEIGHT - PIXEL_SIZE;
const unsigned int TIMER_X = LINE_X + LINE_WIDTH - 2 * TEXT_WIDTH - 2 * PIXEL_SIZE;
const unsigned int TIMER_Y = SCORE_Y;
const unsigned int SPECIAL_FOOD_WIDTH = 2 * BLOCK_SIZE;
const unsigned int SPECIAL_FOOD_HEIGHT = BLOCK_SIZE;
const unsigned int SPECIAL_FOOD_X = LINE_X + LINE_WIDTH - SPECIAL_FOOD_WIDTH - 10 * PIXEL_SIZE;
const unsigned int SPECIAL_FOOD_Y = LINE_Y - SPECIAL_FOOD_HEIGHT - PIXEL_SIZE;
const unsigned int PLAYGROUND_WIDTH = LINE_WIDTH - 2 * PIXEL_SIZE;
const unsigned int PLAYGROUND_HEIGHT = 38 * PIXEL_SIZE;
const unsigned int PLAYGROUND_WIDTH_BLOCKS = PLAYGROUND_WIDTH / BLOCK_SIZE;
const unsigned int SPECIAL_PLAYGROUND_WIDTH_BLOCKS = PLAYGROUND_WIDTH_BLOCKS - 1;
const unsigned int PLAYGROUND_HEIGHT_BLOCKS = PLAYGROUND_HEIGHT / BLOCK_SIZE;
const unsigned int PLAYGROUND_X = LINE_X + PIXEL_SIZE;
const unsigned int PLAYGROUND_Y = LINE_Y + 3 * PIXEL_SIZE;
const unsigned int START_PLAYGROUND_X = PLAYGROUND_X + PIXEL_SIZE;
const unsigned int END_PLAYGROUND_X = PLAYGROUND_X + PLAYGROUND_WIDTH - PIXEL_SIZE - BLOCK_SIZE;
const unsigned int START_PLAYGROUND_Y = PLAYGROUND_Y + PIXEL_SIZE;
const unsigned int END_PLAYGROUND_Y = PLAYGROUND_Y + PLAYGROUND_HEIGHT - PIXEL_SIZE - BLOCK_SIZE;
const unsigned int FOOD_SIZE = 3 * PIXEL_SIZE;
const unsigned int STARTING_BLOCKS = 7;
const unsigned int STARTING_X = PLAYGROUND_X + PIXEL_SIZE + BLOCK_SIZE * ((PLAYGROUND_WIDTH / BLOCK_SIZE - STARTING_BLOCKS) / 2);
const unsigned int STARTING_Y = PLAYGROUND_Y + PIXEL_SIZE + BLOCK_SIZE * ((PLAYGROUND_HEIGHT / BLOCK_SIZE) / 2);
const unsigned int FRAMERATE_LIMIT = 60;
const unsigned int SCORE_DIGIT_COUNT = 4;
const unsigned int TIMER_DIGIT_COUNT = 2;
const unsigned int DEFAULT_SNAKE_SPEED = 10;
const unsigned int FOOD_SCORE = DEFAULT_SNAKE_SPEED - 1;
const unsigned int SPECIAL_FOOD_SCORE = 5 * FOOD_SCORE + 5;
const unsigned int SPECIAL_FOOD_LIFE = 20;
const sf::Color OBJECTS_COLOR = sf::Color::Black;
const sf::Color BACKGROUND_COLOR = sf::Color(90, 150, 90);
const std::string FONT_FILE = "snakeFont.ttf";
const std::string TEXTURE_DIRECTORY = "textures\\";
const std::string TEXTURE_EXTENSION = ".png";
const unsigned int DIRECTIONS = 4;
const unsigned int HEAD_VARIATIONS = 2;
const std::string HEAD_TEXTURES[HEAD_VARIATIONS][DIRECTIONS] = { { "head_left", "head_right", "head_up", "head_down" },
                                                                 { "open_head_left", "open_head_right", "open_head_up", "open_head_down" } };
const unsigned int BODY_VARIATIONS = 4;
const std::string BODY_TEXTURES[BODY_VARIATIONS][DIRECTIONS] = { { "body_horizontal", "body_horizontal", "body_vertical", "body_vertical" },
                                                                 { "full_body_horizontal", "full_body_horizontal", "full_body_vertical", "full_body_vertical" },
                                                                 { "body_lu_corner", "body_ld_corner", "body_ru_corner", "body_rd_corner" },
                                                                 { "full_body_lu_corner", "full_body_ld_corner", "full_body_ru_corner", "full_body_rd_corner" } };
const std::string TAIL_TEXTURES[DIRECTIONS] = { "tail_left", "tail_right", "tail_up", "tail_down" };
const unsigned int AMOUNT_SPECIAL_FOODS = 5;
const std::string SPECIAL_FOODS[AMOUNT_SPECIAL_FOODS] = { "spider", "chamaleon", "turtle", "frog", "worm" };

#endif // CONFIGCONSTANTS_H_INCLUDED
