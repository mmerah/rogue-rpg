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
    for (x = 0; x < numberOfItems; x++)
    {
        if (items[x] == NULL) { // If the item slot is empty (e.g., item picked up)
            continue;           // Skip to the next item
        }
        // Now it's safe to access items[x]->position
        if ((position->y == items[x]->position->y) && (position->x == items[x]->position->x))
        {
            return items[x];
        }
    }

    return NULL;
}