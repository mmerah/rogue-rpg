#include "rogue.h"
#include "utils.h"

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

void printGameHub(Level * level)
{
    mvprintw(25, 0, "    Level: %d", level->level);
    printw("    Gold: %d", level->user->gold);
    printw("    HP: %d(%d)", level->user->health, level->user->maxHealth);
    printw("    Attack: %d", level->user->attack);
    printw("    Exp: %d", level->user->exp);
    printw("      ");
}

void printInventory(Player * player)
{
    int i;
    mvprintw(26, 0, "    Inventory: ");
    
    for (i = 0; i < player->numberItems; i++)
    {
        printw(player->items[i]->string);
    }
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