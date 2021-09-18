#include "rogue.h"
#include "monster.h"

Monster * selectMonster(int level)
{
    int monster;
    switch (level)
    {
        case 1:
        case 2:
        case 3:
            monster = (rand() % 2) + 1;
            break;

        case 4:
        case 5:
            monster = (rand() % 2) + 2;
            break;

        case 6:
            monster = 3;
            break;
    }

    switch (monster)
    {
        case 1: /* spider */
            return createMonster('X', 2, 1, 1, 1, 1, 1, 0);

        case 2: /* goblin */
            return createMonster('G', 5, 3, 1, 1, 2, 2, 1);

        case 3: /* troll */
            return createMonster('T', 15, 5, 1, 1, 1, 5, 2);

        default:
            return createMonster('O', 15, 5, 1, 1, 1, 5, 1);
    }
}

Monster * createMonster(char symbol, int health, int attack, int speed,
                        int defence, int pathfinding, int expReward,
                        int goldReward)
{
    Monster * newMonster;
    newMonster = malloc(sizeof(Monster));

    newMonster->symbol = symbol;
    newMonster->health = health;
    newMonster->attack = attack;
    newMonster->speed = speed;
    newMonster->defence = defence;
    newMonster->pathfinding = pathfinding;
    newMonster->alive = 1;
    newMonster->expReward = expReward;
    newMonster->goldReward = goldReward;

    sprintf(newMonster->string, "%c", symbol);

    newMonster->position = malloc(sizeof(Position));

    return newMonster;
}

void killMonster(Monster * monster)
{
    monster->alive = 0;
}

int pathfindingRandom(Position * position)
{
    int random;

    random = rand() % 5;

    switch (random)
    {
        /* Step up */
        case 0:
            if (mvinch(position->y - 1, position->x) == '.')
            {
                position->y = position->y - 1;
            }
            break;
        
        /* Step down */
        case 1:
            if (mvinch(position->y + 1, position->x) == '.')
            {
                position->y = position->y + 1;
            }
            break;
        
        /* Step left */
        case 2:
            if (mvinch(position->y, position->x - 1) == '.')
            {
                position->x = position->x - 1;
            }
            break;

        /* Step right */
        case 3:
            if (mvinch(position->y, position->x + 1) == '.')
            {
                position->x = position->x + 1;
            }
            break;

        /* Do nothing */
        case 4:
            break;

        default:
            break;
    }

    return 0;
}

int pathfindingSeek(Position * start, Position * destination)
{
    /* Step left */
    if ((abs((start->x - 1) - destination->x) < abs(start->x - destination->x)) && (mvinch(start->y, start->x - 1) == '.'))
    {
        start->x = start->x - 1;
    }
    /* Step right */
    else if ((abs((start->x + 1) - destination->x) < abs(start->x - destination->x)) && (mvinch(start->y, start->x + 1) == '.'))
    {
        start->x = start->x + 1;
    }
    /* Step down */
    else if ((abs((start->y + 1) - destination->y) < abs(start->y - destination->y)) && (mvinch(start->y + 1, start->x) == '.'))
    {
        start->y = start->y + 1;
    }
    /* Step up */
    else if ((abs((start->y - 1) - destination->y) < abs(start->y - destination->y)) && (mvinch(start->y - 1, start->x) == '.'))
    {
        start->y = start->y - 1;
    }
    else
    {
        /* Do nothing */
    }

    return 0;
}

Monster * getMonsterAt(Position * position, Monster ** monsters)
{
    int x;
    for (x = 0; x < 6; x++)
    {
        if ((position->y == monsters[x]->position->y) && (position->x == monsters[x]->position->x))
        {
            return monsters[x];
        }
    }

    return NULL;
}

void drawMonster(Monster * monster)
{
    if (monster->alive)
    {
        mvprintw(monster->position->y, monster->position->x, monster->string);
    }
}

/*
1 Spider
    symbol: X
    levels: 1-3
    health: 2
    attack: 1
    speed: 1
    defence: 1
    pathfinding: 1 (random)

2 Goblin
    symbol: G
    levels: 1-5
    health: 5
    attack: 3
    speed: 1
    defence: 1
    pathfinding: 2 (seeking)

3 Troll
    symbol: T
    levels: 4-6
    health: 15
    attack: 5
    speed: 1
    defence: 1
    pathfinding: 1 (random)
*/