#include "rogue.h"
#include "room.h"

Room * createRoom(const int grid, const int numberOfDoors)
{
    int i;
    Room * newRoom;
    newRoom = malloc(sizeof(Room));
    newRoom->numberOfDoors = numberOfDoors;

    switch (grid)
    {
        case 0:
            newRoom->position.x = 0;
            newRoom->position.y = 0;
            break;

        case 1:
            newRoom->position.x = 33;
            newRoom->position.y = 0;
            break;

        case 2:
            newRoom->position.x = 66;
            newRoom->position.y = 0;
            break;

        case 3:
            newRoom->position.x = 0;
            newRoom->position.y = 14;
            break;

        case 4:
            newRoom->position.x = 33;
            newRoom->position.y = 14;
            break;

        case 5:
            newRoom->position.x = 66;
            newRoom->position.y = 14;
            break;
    }

    newRoom->height = (rand() % 6) + 4; /* max size 9 */
    newRoom->width = (rand() % 14) + 4; /* max size 17 */

    /* offset */
    newRoom->position.x += rand() % (30 - newRoom->width) + 1;
    newRoom->position.y += rand() % (10 - newRoom->height) + 1;
    
    newRoom->doors = malloc(sizeof(Door *) * numberOfDoors);

    for (i = 0; i < numberOfDoors; i++)
    {
        newRoom->doors[i] = malloc(sizeof(Door));
        newRoom->doors[i]->connected = 0;
    }

    /* Top door */
    newRoom->doors[0]->position.x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
    newRoom->doors[0]->position.y = newRoom->position.y;

    /* Left door */
    newRoom->doors[1]->position.y = rand() % (newRoom->height - 2) + newRoom->position.y + 1;
    newRoom->doors[1]->position.x = newRoom->position.x;

    /* Bottom door */
    newRoom->doors[2]->position.x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
    newRoom->doors[2]->position.y = newRoom->position.y + newRoom->height -1;

    /* Right door */
    newRoom->doors[3]->position.y = rand() % (newRoom->height - 2) + newRoom->position.y + 1;
    newRoom->doors[3]->position.x = newRoom->position.x + newRoom->width -1;

    return newRoom;
}

int drawRoom(const Room * room)
{
    int x;
    int y;

    /* Draw top and bottom */
    for (x = room->position.x; x < (room->position.x + room->width); x++)
    {
        mvprintw(room->position.y, x, "-"); /* top */
        mvprintw(room->position.y + room->height - 1, x, "-"); /* bottom */
    }

    /* Draw floors and side walls */
    for (y = room->position.y + 1; y < (room->position.y + room->height - 1); y++)
    {
        /* Draw side walls */
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");

        /* Draw floors */
        for (x = room->position.x + 1; x < (room->position.x + room->width -1); x++)
        {
            mvprintw(y, x, ".");
        }
    }

    /* Draw doors */
    mvprintw(room->doors[0]->position.y, room->doors[0]->position.x, "+");
    mvprintw(room->doors[1]->position.y, room->doors[1]->position.x, "+");
    mvprintw(room->doors[2]->position.y, room->doors[2]->position.x, "+");
    mvprintw(room->doors[3]->position.y, room->doors[3]->position.x, "+");

    return 0;
}

void placePlayer(const Room ** rooms, Player * user)
{
    user->position->x = rooms[3]->position.x + 1;
    user->position->y = rooms[3]->position.y + 1;
}

void placeItems(const Room ** rooms, Item ** items, const int numberOfItems)
{
    int roomChosen;

    for (int i = 0; i < numberOfItems; i++)
    {
        /* Choose a random room */
        roomChosen = rand() % 6;
        /* Random spot in the room */
        items[i]->position->x = (rand() % (rooms[roomChosen]->height - 2)) + rooms[roomChosen]->position.y + 1;
        items[i]->position->y = (rand() % (rooms[roomChosen]->height - 2)) + rooms[roomChosen]->position.y + 1;
    }
}

void setStartingPosition(Monster * monster, Room * room)
{
    monster->position->x = (rand() % (room->height - 2)) + room->position.y + 1;
    monster->position->y = (rand() % (room->height - 2)) + room->position.y + 1;
}
