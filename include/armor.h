#ifndef ARMOR_H
#define ARMOR_H

typedef enum
{
    LEATHER_TYPE,
    IRON_TYPE,
    MYTHRIL_TYPE
} ArmorType;

typedef struct Armor
{
    ArmorType type;
    int defence;
    int health;
} Armor;

#endif /* ARMOR_H */