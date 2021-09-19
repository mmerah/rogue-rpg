#ifndef UTILS_H
#define UTILS_H

#include "level.h"
#include "position.h"
#include "player.h"
#include "monster.h"
#include "rankTable.h"

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
void printGameHub(const Level * level);

/**
 * @brief Print the inventory of the player
 * 
 * @param player Informations on the player
 */
void printInventory(Player * player);

/**
 * @brief Print the game over screen
 */
void printGameOver(void);

/**
 * @brief Print the next level screen
 */
void printNextLevelScreen(void);

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
void combat(Player * player, Monster * monster, const int order);

/**
 * @brief Handle the reward post-combat
 * 
 * @param player Information on the winning player
 * @param monster Information on the killed monster
 */
void handleReward(Player * player, const Monster * monster);

#endif /* UTILS_H */