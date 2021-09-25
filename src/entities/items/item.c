#include "rogue.h"
#include "item.h"

void drawItem(Item * item)
{
    if (item->notPicked)
    {
        mvprintw(item->position->y, item->position->x, "=");
    }
}

Item * getItemAt(Position * position, Item ** items, const int numberOfItems)
{
    int x;
    for (x = 0; x < numberOfItems; x++)
    {
        if ((position->y == items[x]->position->y) && (position->x == items[x]->position->x))
        {
            return items[x];
        }
    }

    return NULL;
}