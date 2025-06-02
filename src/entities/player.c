#include "rogue.h"
#include "player.h"
#include <stdio.h>  // For fprintf
#include <stdlib.h> // For malloc, free, NULL (though often via rogue.h)

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

    if (user == NULL || user->position == NULL) {
        fprintf(stderr, "ERROR: handleInput called with NULL user or user->position.\n");
        // Attempt to allocate and return a fallback position to prevent caller from crashing on NULL.
        // However, the caller (levelLoop) should ideally check for NULL return.
        newPosition = malloc(sizeof(Position));
        if (newPosition == NULL) {
            fprintf(stderr, "ERROR: Failed to allocate memory for newPosition in handleInput (user/user->position was NULL).\n");
            return NULL; // Critical failure, cannot even return a fallback.
        }
        newPosition->y = 0; // Fallback y position
        newPosition->x = 0; // Fallback x position
        return newPosition; // Return fallback position
    }

    newPosition = malloc(sizeof(Position));
    if (newPosition == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate memory for newPosition in handleInput.\n");
        return NULL; // Critical failure
    }
    
    // Default to current position initially
    newPosition->y = user->position->y;
    newPosition->x = user->position->x;

    switch(input)
    {
        case 'w': case 'W':
            newPosition->y = user->position->y - 1;
            // newPosition->x = user->position->x; // Already set by default
            break;
        
        case 's': case 'S':
            newPosition->y = user->position->y + 1;
            // newPosition->x = user->position->x; // Already set by default
            break;

        case 'a': case 'A':
            // newPosition->y = user->position->y; // Already set by default
            newPosition->x = user->position->x - 1;
            break;

        case 'd': case 'D':
            // newPosition->y = user->position->y; // Already set by default
            newPosition->x = user->position->x + 1;
            break;

        default:
            // If input is not recognized, newPosition remains as player's current position (set by default)
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