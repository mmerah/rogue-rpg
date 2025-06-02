#include "rogue.h"
#include "player.h"

Player * playerSetUp()
{
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));
    newPlayer->position = malloc(sizeof(Position));
    // Removed: newPlayer->items = malloc(sizeof(Item *));

    newPlayer->health = 20;
    newPlayer->attack = 1;
    newPlayer->defense = 0; // Initialize base defense
    newPlayer->gold = 0;
    newPlayer->exp = 0;
    // Removed: newPlayer->numberItems = 0;
    newPlayer->inventoryCount = 0; // Initialize inventory count
    newPlayer->maxHealth = 20;
    newPlayer->playerLevel = 1;
    newPlayer->detectionRange = 10;
    newPlayer->equippedWeapon = NULL;
    newPlayer->equippedArmor = NULL; // Initialize equipped armor

    // Initialize inventory slots to NULL
    for (int i = 0; i < MAX_PLAYER_ITEMS; i++) {
        newPlayer->inventory[i] = NULL;
    }

    /* Give player starting weapon */
    Item* startingSword = createSword(1, 20);
    if (newPlayer->inventoryCount < MAX_PLAYER_ITEMS) {
        newPlayer->inventory[newPlayer->inventoryCount++] = startingSword;
        // Equip the starting weapon
        newPlayer->equippedWeapon = startingSword->item.weapon;
    }
    // Removed: newPlayer->numberItems++;, was associated with old items array

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
        case RING_TYPE: // Rings will also go to inventory for now
            if (user->inventoryCount < MAX_PLAYER_ITEMS) {
                user->inventory[user->inventoryCount++] = item;
                item->notPicked = 0; // Mark as picked up
                // TODO: Add a game log message: e.g., "Picked up Sword"
            } else {
                // TODO: Inventory full message - game log needed
                // Item remains on the ground (item->notPicked remains 1)
            }
            break;

        case POTION_TYPE:
            user->health += item->item.potion->healing;
            if (user->health > user->maxHealth)
            {
                user->health = user->maxHealth;
            }
            item->notPicked = 0; // Potion is consumed and removed from map
            // Free the potion data and the item itself
            if (item->item.potion != NULL) {
                free(item->item.potion);
                item->item.potion = NULL;
            }
            // free(item->position); // Position is part of item, not separately allocated for item itself in createPotion
            // item->position = NULL;
            free(item);
            item = NULL;
            break;
    }    
}