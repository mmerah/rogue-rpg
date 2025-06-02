#ifndef ITEM_TABLE_H
#define ITEM_TABLE_H

#define POTION_PER_LEVEL    1
#define WEAPON_PER_LEVEL    1
#define ARMOR_PER_LEVEL     1

// MAX_ITEMS_PER_LEVEL definition
// (POTION_PER_LEVEL + WEAPON_PER_LEVEL + ARMOR_PER_LEVEL + buffer) = (1 + 1 + 1 + 2) = 5
#define MAX_ITEMS_PER_LEVEL (POTION_PER_LEVEL + WEAPON_PER_LEVEL + ARMOR_PER_LEVEL + 2)

#define potionHealing(level)    (level*2)

// Sword with attack scaling by level, health/durability fixed for now
#define swordAttack(level)    (level)
#define swordHealth(level)    (10)    // Placeholder if weapon health is used later
// Armor with defense scaling by level
#define armorDefense(level)   (level)

#endif /* ITEM_TABLE_H */