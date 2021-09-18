#include "rogue.h"
#include "level.h"
#include "utils.h"

Level * createLevel(int level, Player * user)
{
    Level * newLevel;
    newLevel = malloc(sizeof(Level));

    newLevel->level = level;
    newLevel->numberOfRooms = 6;
    newLevel->rooms = roomsSetUp();
    connectDoors(newLevel);
    newLevel->tiles = saveLevelPositions();

    /* Set up a player */
    newLevel->user = user;
    placePlayer(newLevel->rooms, newLevel->user);

    addMonsters(newLevel);

    return newLevel;
}

void drawLevel(Level * level)
{
    int x, y, i;

    /* Printing tiles */
    for (y = 0; y < MAX_HEIGHT; y++)
    {
        for (x = 0; x < MAX_WIDTH; x++)
        {
            mvaddch(y, x, level->tiles[y][x]);
        }
    }

    /* Printing monsters */
    for (i = 0; i < level->numberOfMonsters; i++)
    {
        drawMonster(level->monsters[i]);
    }

    /* Printing player */
    drawPlayer(level->user);
}

Room ** roomsSetUp()
{
    int x;

    Room ** rooms;
    rooms = malloc(sizeof(Room)*6);

    for (x = 0; x < 6; x++)
    {
        rooms[x] = createRoom(x, 4);
        drawRoom(rooms[x]);
    }

    return rooms;
}

void connectDoors(Level * level)
{
    int i, j;
    int randomRoom, randomDoor;
    int count;

    for (i = 0; i < level->numberOfRooms; i++)
    {
        for (j = 0; j < level->rooms[i]->numberOfDoors; j++)
        {
            if (level->rooms[i]->doors[j]->connected == 1)
            {
                continue;
            }

            count = 0;

            while (count < 2)
            {
                randomRoom = rand() % level->numberOfRooms;
                randomDoor = rand() % level->rooms[randomRoom]->numberOfDoors;

                if (level->rooms[randomRoom]->doors[randomDoor]->connected == 1 || randomRoom == i)
                {
                    count++;
                    continue;
                }

                pathFind(&(level->rooms[randomRoom]->doors[randomDoor]->position), &(level->rooms[i]->doors[j]->position));

                level->rooms[randomRoom]->doors[randomDoor]->connected = 1;
                level->rooms[i]->doors[j]->connected = 1;
                break;
            }
        }
    }
}

char ** saveLevelPositions()
{
    int x, y;
    char ** positions;
    positions = malloc(sizeof(char *) * MAX_HEIGHT);


    for (y = 0; y < MAX_HEIGHT; y++)
    {
        positions[y] = malloc(sizeof(char) * MAX_WIDTH);
        for (x = 0; x < MAX_WIDTH; x++)
        {
            positions[y][x] = mvinch(y, x);
        }
    }

    return positions;
}


int checkPosition(Position * newPosition, Level * level)
{
    Player * user;
    Monster * monster;
    user = level->user;

    /* Check if a move on new coordinates is posible */
    switch (mvinch(newPosition->y, newPosition->x))
    {
        case '.':
        case '+':
        case '#':
            playerMove(newPosition, user, level->tiles);
            break;
        case 'X':
        case 'G':
        case 'T':
            monster = getMonsterAt(newPosition, level->monsters);
            combat(user, monster, 1);
            if (monster->alive == 0)
            {
                level->numberOfMonstersAlive--;
            }
        default:
            break;
    }

    return 0;
}

void moveMonsters(Level * level)
{
    int x;
    for (x = 0; x < level->numberOfMonsters; x++)
    {
        if (level->monsters[x]->alive == 0)
        {
            continue;
        }
        if (level->monsters[x]->pathfinding == 1)
        {

            pathfindingRandom(level->monsters[x]->position);
        }
        else
        {
            pathfindingSeek(level->monsters[x]->position, level->user->position);
        }
    }
}

void addMonsters(Level * level)
{
    int x;
    level->monsters = malloc(sizeof(Monster *)* 6);
    level->numberOfMonsters = 0;
    level->numberOfMonstersAlive = 0;

    for (x = 0; x < level->numberOfRooms; x++)
    {
        if ((rand() % 2) == 0)
        {
            level->monsters[level->numberOfMonsters] = selectMonster(level->level);
            setStartingPosition(level->monsters[level->numberOfMonsters], level->rooms[x]);
            level->numberOfMonsters++;
            level->numberOfMonstersAlive++;
        }
    }
}