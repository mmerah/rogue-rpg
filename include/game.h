#ifndef GAME_H
#define GAME_H

#include "level.h"

typedef struct Game
{
    struct Level * levels[10];
    int currentLevel;
} Game;

/**
 * @brief Render the current level
 * 
 * @param level Level informations
 */
void render(const Level * level);

/**
 * @brief Execute the current level
 * 
 * @param level Level informations
 * @param ch input from the player
 */
void levelLoop(Level * level, int ch);

/**
 * @brief Execute the game
 * 
 * @param game Game informations
 */
void gameLoop(Game * game);

#endif /* GAME_H */