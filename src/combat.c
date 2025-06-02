#include "rogue.h"
#include "utils.h"

void combat(Player * player, Monster * monster, const int order)
{
    int playerEffectiveAttack = player->attack;
    if (player->equippedWeapon != NULL) {
        playerEffectiveAttack += player->equippedWeapon->attack;
    }

    int playerEffectiveDefense = player->defense;
    if (player->equippedArmor != NULL) {
        playerEffectiveDefense += player->equippedArmor->defense;
    }

    /* Player attacking */
    if (order == 1)
    {
        monster->health -= playerEffectiveAttack;
        if (monster->health > 0)
        {
            int damageTaken = monster->attack - playerEffectiveDefense;
            if (damageTaken < 0) { damageTaken = 0; }
            player->health -= damageTaken;
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
        int damageTaken = monster->attack - playerEffectiveDefense;
        if (damageTaken < 0) { damageTaken = 0; }
        player->health -= damageTaken;
        if (player->health > 0)
        {
            monster->health -= playerEffectiveAttack;
        }
    }
}

void handleReward(Player * player, const Monster * monster)
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