#include "rogue.h"
#include "game.h"
#include "level.h"
#include "utils.h"
#include "screen.h" // For getInventorySelection and addMessageToLog
#include "item.h"   // For ItemType, WEAPON_TYPE, ARMOR_TYPE
#include <stdio.h>  // For sprintf

void render(Level * level)
{
    /* Redraw the level */
    clear();
    printGameHub(level);
    printGameLog(level);
    drawLevel(level);
}

void levelLoop(Level *level, int ch)
{
    Position *newPosition;

    /* Refresh positions of entities */
    newPosition = handleInput(ch, level->user);
    checkPosition(newPosition, level);
    moveMonsters(level);
    
    render(level);
}

void gameLoop(Game * game)
{
    int ch = '\0';
    Level * level;
    Player * player;

    /* Set up a new player */
    player = playerSetUp();

    if (game->currentLevel == 0)
    {
        /* Set up a map */
        game->levels[game->currentLevel] = createLevel(game->currentLevel + 1, player);
        game->currentLevel++;
    }
    level = game->levels[game->currentLevel - 1];

    while (1)
    {
        if (ch == 'q' || ch == 'Q')
        {
            break;
        }
        else if (ch == 'i' || ch == 'I')
        {
            int selectedSlot = getInventorySelection(level->user);
            clear();
            // render(level); // This was a note about alternative rendering strategy

            if (selectedSlot != -1) { // -1 indicates exit, not an error
                if (selectedSlot < level->user->inventoryCount && level->user->inventory[selectedSlot] != NULL) {
                    Item* itemToEquip = level->user->inventory[selectedSlot];
                    char message[100];

                    if (itemToEquip->type == WEAPON_TYPE) {
                        level->user->equippedWeapon = itemToEquip->item.weapon;
                        sprintf(message, "Equipped %s.", itemToEquip->string);
                        addMessageToLog(message, level->messages);
                    } else if (itemToEquip->type == ARMOR_TYPE) {
                        level->user->equippedArmor = itemToEquip->item.armor;
                        sprintf(message, "Equipped %s.", itemToEquip->string);
                        addMessageToLog(message, level->messages);
                    } else {
                        sprintf(message, "Cannot equip %s (not a weapon or armor).", itemToEquip->string);
                        addMessageToLog(message, level->messages);
                    }
                } else {
                    // This case should ideally not be reached if getInventorySelection is robust
                    char errorMessage[100];
                    sprintf(errorMessage, "Invalid item selection: slot %d.", selectedSlot);
                    addMessageToLog(errorMessage, level->messages);
                }
            }
            // Always re-render after inventory interaction to show changes or log messages
            render(level);
        }
        else
        {
            levelLoop(level, ch);
            if (level->user->health <= 0)
            {
                game->currentLevel = 0;
                printGameOver();
                return;
            }
            else if (level->numberOfMonstersAlive == 0)
            {
                printNextLevelScreen();
                game->currentLevel++;
                level = createLevel(game->currentLevel, player);
            }
        }

        ch = getch();
    }
}