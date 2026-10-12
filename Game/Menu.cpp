//
// Created by PC on 15.05.2026.
//

#include "Menu.h"

Menu::Menu(std::vector<MenuItem> options) : m_options(options), m_selectedIndex(0) {}

void Menu::moveUp() {
    if (m_selectedIndex > 0) {
        m_selectedIndex--;
    }
}

void Menu::moveDown() {
    if (m_selectedIndex < static_cast<int>(m_options.size()) - 1) {
        m_selectedIndex++;
    }
}

void Menu::selectOption() {
    if (m_selectedIndex >= 0 && m_selectedIndex < m_options.size()) {
        if (m_options[m_selectedIndex].m_command != nullptr) {
            m_options[m_selectedIndex].m_command->execute();
        }
    }
}