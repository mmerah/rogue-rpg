#ifndef RING_H
#define RING_H

typedef enum
{
    OFFENSIVE_TYPE,
    DEFENSIVE_TYPE,
    SPECIAL_TYPE
} RingType;

typedef enum
{
    CLOAK_SPECIAL,
    RANGE_SPECIAL,
    SPEED_SPECIAL
} SpecialType;

typedef struct Ring
{
    RingType type;
    union
    {
        int attack;
        int defence;
        SpecialType special;
    } effect;
} Ring;

#endif /* RING_H */