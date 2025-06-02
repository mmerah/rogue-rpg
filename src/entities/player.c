#include "rogue.h"
#include "player.h"

Player * playerSetUp()
{
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));
    newPlayer->position = malloc(sizeof(Position));

    newPlayer->health = 20;
    newPlayer->attack = 1;
    newPlayer->defense = 0;
    newPlayer->gold = 0;
    newPlayer->exp = 0;
    newPlayer->inventoryCount = 0;
    newPlayer->maxHealth = 20;
    newPlayer->playerLevel = 1;
    newPlayer->detectionRange = 10;
    newPlayer->equippedWeapon = NULL;
    newPlayer->equippedArmor = NULL;

    for (int i = 0; i < MAX_PLAYER_ITEMS; i++) {
        newPlayer->inventory[i] = NULL;
    }

    /* Give player starting weapon */
    Item* startingSword = createSword(1, 20);
    if (newPlayer->inventoryCount < MAX_PLAYER_ITEMS) {
        newPlayer->inventory[newPlayer->inventoryCount++] = startingSword;
        newPlayer->equippedWeapon = startingSword->item.weapon;
    }

    return newPlayer;
}

Position * handleInput(const int input, Player * user)
{
    Position * newPosition;
    newPosition = malloc(sizeof(Position));
    
    switch(input)
    {
        /* Move Up */
        case 'w':
        case 'W':
            newPosition->y = user->position->y - 1;
            newPosition->x = user->position->x;
            break;
        
        /* Move down */
        case 's':
        case 'S':
            newPosition->y = user->position->y + 1;
            newPosition->x = user->position->x;
            break;

        /* Move left */
        case 'a':
        case 'A':
            newPosition->y = user->position->y;
            newPosition->x = user->position->x - 1;
            break;

        /* Move right */
        case 'd':
        case 'D':
            newPosition->y = user->position->y;
            newPosition->x = user->position->x + 1;
            break;

        default:
            break;
    }

    return newPosition;
}

int playerMove(const Position * newPosition, Player * user, char ** level)
{
    /* Update player position to new coordinates */
    user->position->y = newPosition->y;
    user->position->x = newPosition->x;

    return 0;
}

void drawPlayer(const Player * player)
{
    mvprintw(player->position->y, player->position->x, "@");
    move(player->position->y, player->position->x);
}

void itemPickManagement(Player * user, Item * item)
{
    switch (item->type)
    {
        case WEAPON_TYPE:
        case ARMOR_TYPE:
        case RING_TYPE:
            if (user->inventoryCount < MAX_PLAYER_ITEMS) {
                user->inventory[user->inventoryCount++] = item;
                item->notPicked = 0;
            } else {
                // Item remains on the ground (item->notPicked remains 1)
            }
            break;

        case POTION_TYPE:
            user->health += item->item.potion->healing;
            if (user->health > user->maxHealth)
            {
                user->health = user->maxHealth;
            }
            item->notPicked = 0;
            if (item->item.potion != NULL) {
                free(item->item.potion);
                item->item.potion = NULL;
            }
            free(item);
            item = NULL;
            break;
    }    
}