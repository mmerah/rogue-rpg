#include "rogue.h"
#include "item.h"
#include "armor.h" // Added for Armor struct
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

Item * createArmor(const int defense)
{
    Item * item = malloc(sizeof(Item));
    item->type = ARMOR_TYPE;
    item->notPicked = 1;
    item->position = malloc(sizeof(Position));
    strcpy(item->string, "Armor"); // Generic name for now

    Armor * armor = malloc(sizeof(Armor));
    armor->defense = defense;

    item->item.armor = armor;

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
    int currentItemIndex = 0;
    int i;

    // Generate Potions
    for (i = 0; i < POTION_PER_LEVEL; i++)
    {
        if (currentItemIndex < MAX_ITEMS_PER_LEVEL) {
            items[currentItemIndex] = createPotion(potionHealing(level));
            currentItemIndex++;
        }
    }

    // Generate Weapons (Swords for now)
    for (i = 0; i < WEAPON_PER_LEVEL; i++)
    {
        if (currentItemIndex < MAX_ITEMS_PER_LEVEL) {
            items[currentItemIndex] = createSword(swordAttack(level), swordHealth(level));
            currentItemIndex++;
        }
    }

    // Generate Armor
    for (i = 0; i < ARMOR_PER_LEVEL; i++)
    {
        if (currentItemIndex < MAX_ITEMS_PER_LEVEL) {
            items[currentItemIndex] = createArmor(armorDefense(level));
            currentItemIndex++;
        }
    }

    return currentItemIndex;
}