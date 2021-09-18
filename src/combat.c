#include "rogue.h"
#include "utils.h"

void combat(Player * player, Monster * monster, int order)
{
    /* Player attacking */
    if (order == 1)
    {
        monster->health -= player->attack;
        if (monster->health > 0)
        {
            player->health -= monster->attack;
        }
        else
        {
            killMonster(monster);
            player->exp++;
        }
    }
    /* Monster attacking */
    else
    {
        player->health -= monster->attack;
        if (player->health > 0)
        {
            monster->health -= player->attack;
        }
    }
}