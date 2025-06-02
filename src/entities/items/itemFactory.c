#include "rogue.h"
#include "item.h"
#include "armor.h" // Added for Armor struct
#include "itemTable.h"

Item * createSword(const int attack, const int health)
{
    Item * item = malloc(sizeof(Item));
    if (item == NULL) {
        return NULL; // Malloc for Item failed
    }

    item->type = WEAPON_TYPE;
    item->notPicked = 1;
    item->position = malloc(sizeof(Position));
    if (item->position == NULL) {
        free(item); // Malloc for Position failed
        return NULL;
    }
    strcpy(item->string, "Sword");

    Weapon * weapon = malloc(sizeof(Weapon));
    if (weapon == NULL) {
        free(item->position); // Malloc for Weapon failed
        free(item);
        return NULL;
    }
    weapon->attack = attack;
    weapon->health = health;

    item->item.weapon = weapon;
    return item;
}

Item * createArmor(const int defense)
{
    Item * item = malloc(sizeof(Item));
    if (item == NULL) {
        return NULL; // Malloc for Item failed
    }

    item->type = ARMOR_TYPE;
    item->notPicked = 1;
    item->position = malloc(sizeof(Position));
    if (item->position == NULL) {
        free(item); // Malloc for Position failed
        return NULL;
    }
    strcpy(item->string, "Armor"); // Generic name for now

    Armor * armor = malloc(sizeof(Armor));
    if (armor == NULL) {
        free(item->position); // Malloc for Armor failed
        free(item);
        return NULL;
    }
    armor->defense = defense;

    item->item.armor = armor;
    return item;
}

Item * createPotion(const int healing)
{
    Item * item = malloc(sizeof(Item));
    if (item == NULL) {
        return NULL; // Malloc for Item failed
    }

    item->type = POTION_TYPE;
    item->notPicked = 1;
    item->position = malloc(sizeof(Position));
    if (item->position == NULL) {
        free(item); // Malloc for Position failed
        return NULL;
    }
    strcpy(item->string, "Potion");

    Potion * potion = malloc(sizeof(Potion));
    if (potion == NULL) {
        free(item->position); // Malloc for Potion failed
        free(item);
        return NULL;
    }
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
            Item* newItem = createPotion(potionHealing(level));
            if (newItem != NULL) {
                items[currentItemIndex] = newItem;
                currentItemIndex++;
            }
        }
    }

    // Generate Weapons (Swords for now)
    for (i = 0; i < WEAPON_PER_LEVEL; i++)
    {
        if (currentItemIndex < MAX_ITEMS_PER_LEVEL) {
            Item* newItem = createSword(swordAttack(level), swordHealth(level));
            if (newItem != NULL) {
                items[currentItemIndex] = newItem;
                currentItemIndex++;
            }
        }
    }

    // Generate Armor
    for (i = 0; i < ARMOR_PER_LEVEL; i++)
    {
        if (currentItemIndex < MAX_ITEMS_PER_LEVEL) {
            Item* newItem = createArmor(armorDefense(level));
            if (newItem != NULL) {
                items[currentItemIndex] = newItem;
                currentItemIndex++;
            }
        }
    }

    return currentItemIndex;
}