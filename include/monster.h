#ifndef MONSTER_H
#define MONSTER_H

#include "position.h"

typedef struct Monster
{
    char string[2];
    char symbol;
    int health;
    int attack;
    int speed;
    int defence;
    int pathfinding;
    Position * position;
    int alive;
    int expReward;
    int goldReward;
    int detectionRange;
} Monster;

/**
 * @brief Select which monster to create based on the level
 * 
 * @param level Informations on the level
 * @return Monster* Pointer to the monster created
 */
Monster * selectMonster(int level);

/**
 * @brief Create a Monster object
 * 
 * @param symbol Symbol for the monster display
 * @param health Health point of the monster
 * @param attack Attack stat of the monster
 * @param speed Speed stat of the monster
 * @param defence Defence stat of the monster
 * @param pathfinding Pathfinding algorithm of the monster
 * @param expReward Reward of experience given by this monster
 * @param goldReward Reward of gold given by this monster
 * @return Monster* Pointer to the monster created
 */
Monster * createMonster(char symbol, int health, int attack, int speed,
                        int defence, int pathfinding, int expReward,
                        int goldReward, int detectionRange);

/**
 * @brief Kill a monster
 * 
 * @param monster Monster pointer
 */
void killMonster(Monster * monster);

/**
 * @brief Pathfinding algorithm seeking
 * 
 * @param start Position of the object
 * @param destination Destination of the object
 * @return int 0 on success
 */
int pathfindingSeek(Position * start, Position * destination);

/**
 * @brief Pathfinding algorithm random
 * 
 * @param position Starting position
 * 
 * @return int 0 on success
 */
int pathfindingRandom(Position * position);

/**
 * @brief Get the Monster At position
 * 
 * @param position position where we check
 * @param monsters List of monsters in the level
 * @return Monster* Monster at the position checked
 */
Monster * getMonsterAt(Position * position, Monster ** monsters);

/**
 * @brief Draw a monster
 * 
 * @param monster Monster informations
 */
void drawMonster(Monster * monster);

#endif /* MONSTER_H */