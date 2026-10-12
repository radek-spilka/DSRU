//
// Created by PC on 15.05.2026.
//

#ifndef PROJEKT_ZOO_MENUITEM_H
#define PROJEKT_ZOO_MENUITEM_H
#include <string>

#include "ICommand.h"

struct MenuItem {
    std::string m_label;
    ICommand* m_command;
};
#endif //PROJEKT_ZOO_MENUITEM_H