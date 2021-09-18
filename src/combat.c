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
            handleReward(player, monster);
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

void handleReward(Player * player, Monster * monster)
{
    player->exp += monster->expReward;
    if (player->exp >= thresholdLevel(player->playerLevel))
    {
        player->exp -= thresholdLevel(player->playerLevel);
        player->playerLevel++;
        player->maxHealth += maxHealthIncrease(player->playerLevel);
        player->attack += attackIncrease(player->playerLevel);
    }

    player->gold += monster->goldReward;
}