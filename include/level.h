#ifndef LEVEL_H
#define LEVEL_H

#include "position.h"
#include "monster.h"
#include "player.h"
#include "room.h"

typedef struct Level
{
    char ** tiles;
    int level;
    int numberOfRooms;
    struct Room ** rooms;
    struct Monster ** monsters;
    int numberOfMonsters;
    int numberOfMonstersAlive;
    struct Player * user;
} Level;

/**
 * @brief Create a new Level
 * 
 * @param level Level number
 * @param user Player created in the level
 * 
 * @return Level Pointer to a level structure
 */
Level * createLevel(int level, Player * user);

/**
 * @brief Draw the level
 * 
 * @param level Current level informations
 */
void drawLevel(Level * level);

/**
 * @brief Set up a map on screen
 * 
 * @return Array of pointers to the rooms composing the map
 */
Room ** roomsSetUp();

/**
 * @brief Save current map on screen
 * 
 * @return char** 2D map
 */
char ** saveLevelPositions();

/**
 * @brief Connect all doors in a level
 * 
 * @param level Information on the current level
 */
void connectDoors(Level * level);

/**
 * @brief Check what is at next position
 * 
 * @param newPosition X,Y position that the entity wants to move to
 * @param level Informations on the level
 * 
 * @return 0 on success
 */
int checkPosition(Position * newPosition, Level * level);

/**
 * @brief Add monsters to the level
 * 
 * @param level Informations on the Level
 */
void addMonsters(Level * level);

/**
 * @brief Move a monster in the level
 * 
 * @param level Informations on the level
 */
void moveMonsters(Level * level);

#endif /* LEVEL_H */