//
// Created by PC on 15.05.2026.
//

#ifndef PROJEKT_ZOO_MENU_H
#define PROJEKT_ZOO_MENU_H


#include <vector>
#include "MenuItem.h"
class Menu {
protected:
    std::vector<MenuItem> m_options;
    int m_selectedIndex;

public:
    Menu(std::vector<MenuItem> options);
    void moveUp();
    void moveDown();
    void selectOption();

    // Gettery bez const
    std::vector<MenuItem>& getOptions() { return m_options; }
    int getSelectedIndex() { return m_selectedIndex; }
};


#endif //PROJEKT_ZOO_MENU_H