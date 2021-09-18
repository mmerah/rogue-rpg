#ifndef UTILS_H
#define UTILS_H

#include "level.h"
#include "position.h"
#include "player.h"
#include "monster.h"

/******************
 * PATH FINDING
 *****************/

/**
 * @brief Find a path between start and end positions
 * 
 * @param start Starting coordinates
 * @param end Ending coordinates
 * @return int 0 on success
 */
int pathFind(Position * start, Position * end);


/******************
 * SCREEN FUNCTIONS
 *****************/

/**
 * @brief Set up our screen
 * 
 */
void screenSetUp();

/**
 * @brief Print the HUD for the game
 * 
 * @param level Informations on the level
 */
void printGameHub(Level * level);

/**
 * @brief Print the inventory of the player
 * 
 * @param player Informations on the player
 */
void printInventory(Player * player);

/******************
 * COMBAT FUNCTIONS
 *****************/

/**
 * @brief Combat function handler
 * 
 * @param player Player informations
 * @param monster Monster informations
 * @param order Attacking order
 * 
 */
void combat(Player * player, Monster * monster, int order);

#endif /* UTILS_H */