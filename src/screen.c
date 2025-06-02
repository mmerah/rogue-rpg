#include "rogue.h"
#include "utils.h"
#include "player.h" // For Player struct
#include "item.h"   // For Item struct
#include "weapon.h" // For Weapon struct (in Player->equippedWeapon)
#include "armor.h"  // For Armor struct (in Player->equippedArmor)
#include <string.h> // For sprintf, strlen if needed

void screenSetUp()
{
    initscr();

    /* TBA: MAX HEIGHT AND MAX WIDTH */
        
    /* Turns off what has been called in the terminal */
    noecho();

    /* Allows ncurses access to system keys */
    keypad(stdscr, TRUE);

    /* Refresh the output */
    refresh();

    /* Set up the random seed */
    srand(time(NULL));
}

void printGameHub(const Level * level)
{
    mvprintw(25, 0, "    Level: %d", level->level);
    printw("    Gold: %d", level->user->gold);
    printw("    HP: %d(%d)", level->user->health, level->user->maxHealth);

    // Calculate and print effective attack
    int effectiveAttack = level->user->attack;
    if (level->user->equippedWeapon != NULL) {
        effectiveAttack += level->user->equippedWeapon->attack;
    }
    printw("    Attack: %d", effectiveAttack);

    // Calculate and print effective defense
    int effectiveDefense = level->user->defense;
    if (level->user->equippedArmor != NULL) {
        effectiveDefense += level->user->equippedArmor->defense;
    }
    printw("    Defense: %d", effectiveDefense);

    printw("    Rank: %d (XP: %d)", level->user->playerLevel, level->user->exp);
    printw("      ");
}

void printGameLog(Level * level)
{
    mvprintw(26, 50, "Game Log: ");
    for (int i = 0; i < EVENT_LOG_SIZE; i++)
    {
        mvprintw(27 + i, 50, "%s", level->messages[i]);
    }
    updateLogBuffer(level->messages);
}

int getInventorySelection(Player* player) {
    int y_pos = 5;
    int x_pos = 5;
    int box_height = 15; // MAX_PLAYER_ITEMS + 4 (title, prompt, borders)
    int box_width = 35;  // Max item string length + number + padding

    // Crude way to "clear" a section - by drawing a blank box
    // A more robust way would be to use newwin() for a sub-window
    for (int r = y_pos -1; r < y_pos + box_height +1; ++r) {
        for (int c = x_pos-1; c < x_pos + box_width+1; ++c) {
            mvaddch(r, c, ' ');
        }
    }
    
    // Draw a simple border for the inventory box
    mvhline(y_pos -1, x_pos, ACS_HLINE, box_width);
    mvhline(y_pos + box_height -1 , x_pos, ACS_HLINE, box_width);
    mvvline(y_pos, x_pos -1, ACS_VLINE, box_height -1);
    mvvline(y_pos, x_pos + box_width -1, ACS_VLINE, box_height-1);
    mvaddch(y_pos-1, x_pos-1, ACS_ULCORNER);
    mvaddch(y_pos-1, x_pos + box_width -1, ACS_URCORNER);
    mvaddch(y_pos + box_height -1, x_pos-1, ACS_LLCORNER);
    mvaddch(y_pos + box_height-1, x_pos + box_width -1, ACS_LRCORNER);


    mvprintw(y_pos, x_pos + 1, "Inventory:");

    if (player->inventoryCount == 0) {
        mvprintw(y_pos + 2, x_pos + 1, "Your inventory is empty.");
    } else {
        for (int i = 0; i < player->inventoryCount; i++) {
            if (player->inventory[i] != NULL) { // Should always be true up to inventoryCount
                mvprintw(y_pos + 2 + i, x_pos + 1, "%d. %s", i + 1, player->inventory[i]->string);
            }
        }
    }

    mvprintw(y_pos + box_height - 2, x_pos + 1, "Enter # to equip, or 'x' to exit.");
    refresh();

    int ch;
    while ((ch = getch())) {
        if (ch == 'x' || ch == 'X') {
            return -1;
        }
        if (ch >= '1' && ch <= ('0' + player->inventoryCount)) {
            int choice = ch - '0'; // Convert char to int
            if (choice > 0 && choice <= player->inventoryCount) {
                if (player->inventory[choice - 1] != NULL) { // Check if item at choice-1 is valid
                    return choice - 1; // Return 0-indexed slot
                }
            }
        }
        mvprintw(y_pos + box_height - 3, x_pos + 1, "Invalid selection. Try again.    ");
        mvprintw(y_pos + box_height - 2, x_pos + 1, "Enter # to equip, or 'x' to exit.");
        refresh();
    }
    return -1; // Should not be reached if loop is structured well
}

void printGameOver(void)
{
    clear();
    mvprintw(MAX_HEIGHT/2, MAX_WIDTH/2 - 10, "== GAME OVER ==");
    getch();
    clear();
}

void printNextLevelScreen(void)
{
    clear();
    mvprintw(MAX_HEIGHT/2, MAX_WIDTH/2 - 10, "** NEXT LEVEL **");
    getch();
    clear();
}

void updateLogBuffer(char buffer[EVENT_LOG_SIZE][MESSAGE_SIZE])
{
    /* Pile update */
    for (int i = EVENT_LOG_SIZE; i > 0; i--)
    {
        strcpy(buffer[i], buffer[i - 1]);
    }
    strcpy(buffer[0], "");
}

void addMessageToLog(char * message, char buffer[EVENT_LOG_SIZE][MESSAGE_SIZE])
{
    updateLogBuffer(buffer);
    strcpy(buffer[0], message);
}