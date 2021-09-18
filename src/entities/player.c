#include "rogue.h"
#include "player.h"

Player * playerSetUp()
{
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));
    newPlayer->position = malloc(sizeof(Position));
    newPlayer->items = malloc(sizeof(Item *));

    newPlayer->health = 20;
    newPlayer->attack = 1;
    newPlayer->gold = 0;
    newPlayer->exp = 0;
    newPlayer->numberItems = 0;
    newPlayer->maxHealth = 20;
    newPlayer->playerLevel = 1;

    /* Give player starting weapon */
    newPlayer->items[newPlayer->numberItems] = createSword(1, 20);
    newPlayer->numberItems++;

    return newPlayer;
}

Position * handleInput(int input, Player * user)
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

int playerMove(Position * newPosition, Player * user, char ** level)
{
    /* Update player position to new coordinates */
    user->position->y = newPosition->y;
    user->position->x = newPosition->x;

    return 0;
}

void drawPlayer(Player * player)
{
    mvprintw(player->position->y, player->position->x, "@");
    move(player->position->y, player->position->x);
}