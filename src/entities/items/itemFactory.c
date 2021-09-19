#include "rogue.h"
#include "item.h"
#include "itemTable.h"

Item * createSword(const int attack, const int health)
{
    Item * item = malloc(sizeof(Item));
    item->type = WEAPON_TYPE;
    item->notPicked = 1;
    item->position = malloc(sizeof(Position));
    strcpy(item->string, "Sword");

    Weapon * weapon = malloc(sizeof(Weapon));
    weapon->attack = attack;
    weapon->health = health;

    item->item.weapon = weapon;

    return item;
}

Item * createPotion(const int healing)
{
    Item * item = malloc(sizeof(Item));
    item->type = POTION_TYPE;
    item->notPicked = 1;
    item->position = malloc(sizeof(Position));
    strcpy(item->string, "Potion");

    Potion * potion = malloc(sizeof(Potion));
    potion->healing = healing;

    item->item.potion = potion;
    
    return item;
}

int generateItems(const int level, Item ** items)
{
    int i = 0;
    for (i = 0; i < POTION_PER_LEVEL; i++)
    {
        items[i] = createPotion(potionHealing(level));
    }

    return i;
}