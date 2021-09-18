#ifndef GAME_H
#define GAME_H

#include "level.h"

typedef struct Game
{
    struct Level * levels[10];
    int currentLevel;
} Game;

/**
 * @brief Render the game
 * 
 * @param game Game informations
 */
void render(Game * game);

/**
 * @brief Execute the game
 * 
 * @param game Game informations
 */
void gameLoop(Game * game);

#endif /* GAME_H */