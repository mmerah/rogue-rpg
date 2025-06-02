#include "rogue.h"
#include "level.h"
#include "utils.h"
#include "itemTable.h" // For MAX_ITEMS_PER_LEVEL
#include <string.h>    // For strcpy
#include <stdio.h>     // For sprintf

Level * createLevel(const int level, Player * user)
{
    Level * newLevel;
    newLevel = malloc(sizeof(Level));
    if (newLevel == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate memory for Level struct in createLevel.\n");
        return NULL;
    }

    /* Basic level creation */
    // Initialize pointers to NULL before allocation attempts, for safer cleanup
    newLevel->tiles = NULL;
    newLevel->rooms = NULL;
    newLevel->items = NULL;
    newLevel->monsters = NULL; // Though monsters are allocated in addMonsters, good practice

    newLevel->level = level;
    newLevel->numberOfRooms = 6;
    newLevel->rooms = roomsSetUp();
    connectDoors(newLevel);
    newLevel->tiles = saveLevelPositions();

    /* Set up a player */
    newLevel->user = user;
    placePlayer((const Room **)newLevel->rooms, newLevel->user);

    /* Set up the objects in the level */
    newLevel->items = malloc(sizeof(Item *) * MAX_ITEMS_PER_LEVEL);
    if (newLevel->items == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate memory for newLevel->items in createLevel.\n");
        // Attempt to free previously allocated memory for this newLevel
        if (newLevel->tiles != NULL) {
            for (int y = 0; y < MAX_HEIGHT; y++) { // MAX_HEIGHT from rogue.h
                free(newLevel->tiles[y]);
            }
            free(newLevel->tiles);
        }
        if (newLevel->rooms != NULL) {
            // roomsSetUp allocates rooms[x] = createRoom(...). createRoom mallocs Room.
            for (int i = 0; i < newLevel->numberOfRooms; i++) {
                if (newLevel->rooms[i] != NULL) {
                    // If Room struct itself contains malloced members (e.g. doors array in Room struct),
                    // a proper freeRoom(newLevel->rooms[i]) function would be ideal.
                    // Assuming Room's members like 'doors' are freed if createRoom fails or in a dedicated freeRoom.
                    // For now, freeing the Room struct itself.
                    if(newLevel->rooms[i]->doors != NULL) { // createRoom also mallocs doors
                        free(newLevel->rooms[i]->doors);
                    }
                    free(newLevel->rooms[i]);
                }
            }
            free(newLevel->rooms);
        }
        // newLevel->user is passed in, not allocated here.
        // newLevel->monsters is allocated in addMonsters, which is called later.
        free(newLevel);
        return NULL;
    }
    newLevel->numberOfItems = generateItems(newLevel->level, newLevel->items);
    placeItems((const Room **)newLevel->rooms, newLevel->items, newLevel->numberOfItems);

    /* Set up the monsters in the level */
    addMonsters(newLevel);

    /* Log the start of the game */
    addMessageToLog("Game started", newLevel->messages);

    return newLevel;
}

void drawLevel(const Level * level)
{
    int x, y, i;

    int areaDisplayed = level->user->detectionRange;

    /* Printing tiles */
    for (y = 0; y < MAX_HEIGHT; y++)
    {
        for (x = 0; x < MAX_WIDTH; x++)
        {
            if ((abs(y - level->user->position->y) < areaDisplayed) && (abs(x - level->user->position->x) < areaDisplayed))
            {
                mvaddch(y, x, level->tiles[y][x]);
            }
        }
    }

    /* Printing items */
    for (i = 0; i < level->numberOfItems; i++)
    {
        if ((abs(level->items[i]->position->y - level->user->position->y) < areaDisplayed) && (abs(level->items[i]->position->x - level->user->position->x) < areaDisplayed))
        {
            drawItem(level->items[i]);
        }
    }

    /* Printing monsters */
    for (i = 0; i < level->numberOfMonsters; i++)
    {
        if ((abs(level->monsters[i]->position->y - level->user->position->y) < areaDisplayed) && (abs(level->monsters[i]->position->x - level->user->position->x) < areaDisplayed))
        {
            drawMonster(level->monsters[i]);
        }
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
    // Item * item; // Declared later as item_from_level

    if (level == NULL) {
        fprintf(stderr, "ERROR: checkPosition called with NULL level.\n");
        return -1;
    }
    if (level->user == NULL) {
        fprintf(stderr, "ERROR: level->user is NULL in checkPosition.\n");
        return -1;
    }
    if (newPosition == NULL) {
        fprintf(stderr, "ERROR: checkPosition called with NULL newPosition.\n");
        return -1;
    }
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
                addMessageToLog("Killed a monster", level->messages);
            }
            break;
        case '=':
            if (level->items == NULL) {
                fprintf(stderr, "ERROR: level->items is NULL when trying to get item in checkPosition.\n");
                break;
            }
            Item * item_from_level = getItemAt(newPosition, level->items, level->numberOfItems);
            if (item_from_level != NULL) {
                char itemName[256];
                strcpy(itemName, item_from_level->string); // Copy name
                ItemType typeOfPickedItem = item_from_level->type; // Store type before potential free

                itemPickManagement(user, item_from_level); // Handles item effect, inventory, and notPicked for non-potions

                // For potions, item_from_level is now a dangling pointer as it's freed in itemPickManagement.
                // For other items, it was added to inventory.

                char message[300];
                snprintf(message, sizeof(message), "Picked up %s.", itemName); // Use snprintf for safety
                addMessageToLog(message, level->messages);

                // If item was not a potion, it was added to inventory.
                // Nullify its pointer in level->items to prevent double free by destroyLevel
                // and to ensure it's not accidentally interacted with again on the map.
                if (typeOfPickedItem != POTION_TYPE) {
                    for (int i = 0; i < level->numberOfItems; i++) {
                        if (level->items[i] == item_from_level) {
                            level->items[i] = NULL;
                            break;
                        }
                    }
                }
            }
            break;
        default:
            break;
    }

    return 0;
}

void moveMonsters(Level * level)
{
    int x;
    int gapPlayerX = 0;
    int gapPlayerY = 0;

    for (x = 0; x < level->numberOfMonsters; x++)
    {
        gapPlayerX = abs(level->user->position->x - level->monsters[x]->position->x);
        gapPlayerY = abs(level->user->position->y - level->monsters[x]->position->y);

        if (level->monsters[x]->alive == 0)
        {
            continue;
        }

        if (level->monsters[x]->pathfinding == 1)
        {
            pathfindingRandom(level->monsters[x]->position);
        }
        else if (gapPlayerY > level->monsters[x]->detectionRange || gapPlayerX > level->monsters[x]->detectionRange )
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