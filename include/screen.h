#ifndef SCREEN_H
#define SCREEN_H

#include "player.h" // For Player*
#include "level.h"  // For Level* if render is called from here (not planned for now)

/**
 * @brief Displays the player's inventory and handles item selection for equipping.
 *
 * The function will draw the inventory items, allow the user to select an item
 * by number, or exit the inventory view.
 *
 * @param player Pointer to the player whose inventory is to be displayed.
 * @return The 0-indexed slot number of the selected item in the inventory,
 *         or -1 if the user chose to exit or no valid selection was made.
 */
int getInventorySelection(Player* player);

// Declaration for addMessageToLog if it's to be centralized here.
// For now, assuming game.c can access it or it's in rogue.h
// void addMessageToLog(char * message, char (*logBuffer)[MESSAGE_SIZE]);


#endif /* SCREEN_H */
