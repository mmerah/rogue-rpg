#ifndef ITEM_H
#define ITEM_H

#include "weapon.h"
#include "potion.h"
#include "position.h"

typedef enum
{
    WEAPON_TYPE,
    POTION_TYPE
} ItemType;

typedef struct Item
{
    ItemType type;
    Position * position;

    union
    {
        Weapon * weapon;
        Potion * potion;
    } item;

    char string[256];

} Item;

/**
 * @brief Create a Sword object
 * 
 * @param attack Attacking value of the sword
 * @param health Health value of the sword
 * @return Item* Object item
 */
Item * createSword(int attack, int health);

#endif /* ITEM_H */