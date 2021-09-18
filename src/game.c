#include "rogue.h"
#include "game.h"
#include "level.h"
#include "utils.h"

void render(Level * level)
{
    /* Redraw the level */
    clear();
    printGameHub(level);
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
            printInventory(level->user);
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