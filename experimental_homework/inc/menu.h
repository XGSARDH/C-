//
// Created by sardh on 2024/12/17.
//

#ifndef MENU_H
#define MENU_H

#include "status_enum.h"

typedef struct MenuType {
    // init the position is 0.
    int nowMenuPosition;
    // choose == 0, mean not choose, the next step is to choose
    int choose;
} MenuType;

Status createMenuType(MenuType *origin, int nowMenuPosition, int choose);

Status changeMenuType(MenuType *origin, int nowMenuPosition, int choose);

Status processMenuSelection(MenuType input);

Status resetMenuType(MenuType *origin);

Status displayMenu(MenuType input);

#endif //MENU_H
