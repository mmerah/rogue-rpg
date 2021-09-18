#include "rogue.h"
#include "utils.h"

static void addPositionYX(int ** frontier, int frontierCount, int y, int x)
{
    frontier[frontierCount][0] = y;
    frontier[frontierCount][1] = x;
}

bool checkNeighborPosition(int y, int x)
{
    char temp = mvinch(y, x);

    if (temp == '.' || temp == '|' || temp == '-')
    {
        return false;
    }
    else
    {
        return true;
    }
}

static int addNeighbors(int ** frontier, int frontierCount, int *** cameFrom, int y, int x)
{
    /* North position */
    if (y > 0 && cameFrom[y - 1][x][0] < 0 && checkNeighborPosition(y - 1, x))
    {
        addPositionYX(frontier, frontierCount, y - 1, x);
        frontierCount++;
        cameFrom[y - 1][x][0] = y;
        cameFrom[y - 1][x][1] = x;
    }

    /* South position */
    if (y < (MAX_HEIGHT - 1) && cameFrom[y + 1][x][0] < 0 && checkNeighborPosition(y + 1, x))
    {
        addPositionYX(frontier, frontierCount, y + 1, x);
        frontierCount++;
        cameFrom[y + 1][x][0] = y;
        cameFrom[y + 1][x][1] = x;
    }

    /* east position */
    if (x < (MAX_WIDTH - 1) && cameFrom[y][x + 1][0] < 0 && checkNeighborPosition(y, x + 1))
    {
        addPositionYX(frontier, frontierCount, y, x + 1);
        frontierCount++;
        cameFrom[y][x + 1][0] = y;
        cameFrom[y][x + 1][1] = x;
    }

    /* west position */
    if (x > 0 && cameFrom[y][x - 1][0] < 0 && checkNeighborPosition(y, x - 1))
    {
        addPositionYX(frontier, frontierCount, y, x - 1);
        frontierCount++;
        cameFrom[y][x - 1][0] = y;
        cameFrom[y][x - 1][1] = x;
    }

    return frontierCount;

}

int pathFind(Position * start, Position * end)
{
    int i, j;
    int x, y;
    int tempY;
    int ** frontier = malloc(sizeof(int*) * MAX_HEIGHT * MAX_WIDTH);
    int *** cameFrom = malloc(sizeof(int**) * MAX_HEIGHT);

    int frontierIndex = 0;
    int frontierCount = 0;

    for (i = 0; i < MAX_HEIGHT * MAX_WIDTH; i++)
    {
        frontier[i] = malloc(sizeof(int)*2);
    }

    for (i = 0; i < MAX_HEIGHT; i++)
    {
        cameFrom[i] = malloc(sizeof(int*) * MAX_WIDTH);
        for (j = 0; j < MAX_WIDTH; j++)
        {
            cameFrom[i][j] = malloc(sizeof(int)*2);
            cameFrom[i][j][0] = -1;
            cameFrom[i][j][1] = -1;
        }
    }

    /* add start to cameFron */
    cameFrom[start->y][start->x][0] = -9; // Flag to indicate the start
    cameFrom[start->y][start->x][1] = -9;

    /* Add start position to the frontier */
    addPositionYX(frontier, frontierCount, start->y, start->x);
    frontierCount++;

    /* While there is still a position in the frontier to check */
    while (frontierIndex < frontierCount)
    {
        y = frontier[frontierIndex][0];
        x = frontier[frontierIndex][1];
        frontierIndex++;

        if (y == end->y && x == end->x)
        {
            break;
        }

        /* Add our neighbours */
        frontierCount = addNeighbors(frontier, frontierCount, cameFrom, y, x);
    }

    y = end->y;
    x = end->x;

    while (y != start->y || x != start->x)
    {
        tempY = y;
        y = cameFrom[tempY][x][0];
        x = cameFrom[tempY][x][1];
        mvprintw(y, x, "+");
        //getch();
    }

    return 0;
}