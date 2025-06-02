#include "rogue.h"
#include "item.h"

void drawItem(Item * item)
{
    if (item == NULL) {
        return;
    }
    if (item->notPicked)
    {
        mvprintw(item->position->y, item->position->x, "=");
    }
}

Item * getItemAt(Position * position, Item ** items, const int numberOfItems)
{
    int x;

    if (items == NULL || position == NULL) { // Check if the array or target position is NULL
        return NULL;
    }

    for (x = 0; x < numberOfItems; x++)
    {
        if (items[x] == NULL) { // Skip if the item pointer in the array is NULL
            continue;
        }
        if (items[x]->position == NULL) { // Skip if the item's position pointer is NULL
            continue;
        }

        // Now it's safe to access items[x]->position->y and items[x]->position->x
        if ((position->y == items[x]->position->y) && (position->x == items[x]->position->x))
        {
            return items[x];
        }
    }
    return NULL;
}