#include "rogue.h"
#include "mainMenu.h"
#include "game.h"
#include "utils.h"

void menuLoop()
{
    int choice;
    char * choices[] = {"Start Game", "End Game"};

    Game game;
    game.currentLevel = 0;

    while (true)
    {
        /* Display the main menu */
        choice = mainMenu(2, choices);

        switch (choice)
        {
            case START_GAME:
                gameLoop(&game);
                clear();
                break;

            case QUIT_GAME:
                return;
                break;

            default:
                break;
        }
    }
}

/******************
 * MAIN
 *****************/
int main ()
{
    /* Set up a screen */
    screenSetUp();

    /* Starts the menu of the Game */
    menuLoop();

    /* Stop ncurses from running before quitting */
    endwin();

    return 0;
}
