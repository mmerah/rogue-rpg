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

void printGameHub(const Level * level)
{
    mvprintw(25, 0, "    Level: %d", level->level);
    printw("    Gold: %d", level->user->gold);
    printw("    HP: %d(%d)", level->user->health, level->user->maxHealth);
    printw("    Attack: %d", level->user->attack);
    printw("    Rank: %d (XP: %d)", level->user->playerLevel, level->user->exp);
    printw("      ");
}

void printGameLog(Level * level)
{
    mvprintw(26, 50, "Game Log: ");
    for (int i = 0; i < EVENT_LOG_SIZE; i++)
    {
        mvprintw(27 + i, 50, level->messages[i]);
    }
    updateLogBuffer(level->messages);
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