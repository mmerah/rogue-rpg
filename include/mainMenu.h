#ifndef MAIN_MENU_H
#define MAIN_MENU_H

enum 
{
    START_GAME,
    QUIT_GAME
};

/**
 * @brief Main menu function
 * 
 * @param numberItems 
 * @param choices 
 * @return int 0 on success
 */
int mainMenu(int numberItems, char * choices[]);

#endif /* MAIN_MENU_H */