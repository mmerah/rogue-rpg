#ifndef ITEM_H
#define ITEM_H

#include "weapon.h"
#include "potion.h"
#include "armor.h"
#include "ring.h"
#include "position.h"

typedef enum
{
    WEAPON_TYPE,
    ARMOR_TYPE,
    RING_TYPE,
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
        Armor * armor;
        Ring * ring;
    } item;
    char string[256];
    int notPicked;
} Item;

/**
 * @brief Create a Sword object
 * 
 * @param attack Attacking value of the sword
 * @param health Health value of the sword
 * @return Item* Object item
 */
Item * createSword(int attack, int health);

/**
 * @brief Create a Potion object
 * 
 * @param healing Healing value of the potion
 * @return Item* Object item
 */
Item * createPotion(int healing);

/**
 * @brief Generate all items on a level
 * 
 * @param level Current level index
 * @param items Array of pointers to the items
 * 
 * @return int Number of item generated
 */
int generateItems(int level, Item ** items);

/**
 * @brief Draw the item on the level
 * 
 * @param item Item informations
 */
void drawItem(Item * item);

/**
 * @brief Get the Item At position
 * 
 * @param position Position to survey
 * @param items List of items in the level
 * @param numberOfItems Number of items in the level
 * @return Item* Pointer to the item at the position
 */
Item * getItemAt(Position * position, Item ** items, int numberOfItems);

#endif /* ITEM_H */