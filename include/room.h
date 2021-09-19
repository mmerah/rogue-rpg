#ifndef ROOM_H
#define ROOM_H

#include "monster.h"
#include "player.h"
#include "position.h"
#include "door.h"

typedef struct Room
{
    Position position;
    int height;
    int width;

    struct Door ** doors;
    int numberOfDoors;
    // Monster ** monsters;
    // Item ** items;
} Room;

/**
 * @brief Create a Room with input parameters
 * @param grid Part of the map where the room is created
 * @param numberOfDoors Number of doors created
 * @return *Room Pointer to the room created
 */
Room * createRoom(int grid, int numberOfDoors);

/**
 * @brief Draw a room on the map
 * @param room Pointer to the room to be drawn
 * @return 0 on success
 */
int drawRoom(Room * room);

/**
 * @brief Place a player in a room
 * 
 * @param rooms List of rooms
 * @param user Player
 */
void placePlayer(Room ** rooms, Player * user);

/**
 * @brief Place the items in the rooms
 * 
 * @param rooms List of rooms
 * @param items List of items
 * @param numberOfItems Number of items
 */
void placeItems(Room ** rooms, Item ** items, int numberOfItems);

/**
 * @brief Set the Starting Position of the monster
 * 
 * @param monster Monster to set in the room
 * @param room Room to set the monster in
 */
void setStartingPosition(Monster * monster, Room * room);

#endif /* ROOM_H */