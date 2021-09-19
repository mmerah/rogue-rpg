#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "item.h"

typedef struct Player
{
    Position * position;
    int health;
    int maxHealth;
    int attack;
    int gold;
    int exp;
    int numberItems;
    int playerLevel;
    // Room * room;
    Item ** items;
} Player;

/******************
 * PLAYER AND MOVEMENT FUNCTIONS
 *****************/

/** 
 * @brief Set up a new entity
 * 
 * @return Pointer on the new entity
 */
Player * playerSetUp();

/**
 * @brief React to on input by the user
 * 
 * @param input Character inputted by the user
 * @param user Player pointer
 * 
 * @return New Position calculated based on the input.
 */
Position * handleInput(const int input, Player * user);

/**
 * @brief Moves an entity to new coordinates
 * 
 * @param newPosition X,Y position to move the entity to
 * @param user Player that needs to move
 * @param level Map of the level
 * 
 * @return 0 on success
 */
int playerMove(const Position * newPosition, Player * user, char ** level);

/**
 * @brief Draw the player
 * 
 * @param player Player informations
 */
void drawPlayer(const Player * player);

#endif /* PLAYER_H */