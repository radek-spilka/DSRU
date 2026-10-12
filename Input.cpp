#include "Input.h"
#include <conio.h>
Input* Input::m_instance = nullptr;

Input::Input() {
}

Input* Input::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new Input();
    }
    return m_instance;
}

Action Input::getAction() {
    if (!_kbhit()) {
        return Action::none;
    }
    int key = _getch();

    if (key == 224 || key == 0) {
        key = _getch();
        switch (key) {
            case 72: return Action::moveUp;
            case 80: return Action::moveDown;
            case 75: return Action::moveLeft;
            case 77: return Action::moveRight;
            default: return Action::none;
        }
    }
    switch (key) {
        case 'w': case 'W':
            return Action::moveUp;
        case 's': case 'S':
            return Action::moveDown;
        case 'a': case 'A':
            return Action::moveLeft;
        case 'd': case 'D':
            return Action::moveRight;
        case 'e': case 'E':
        case 13: case ' ':
            return Action::interact;
        case 27:
            return Action::pause;

        case '1': case '+': case '!':
            return Action::num1;

        case '2': case '@': case 216: case 183:
            return Action::num2;

        case '3': case '#': case 231: case 154: case 230:
            return Action::num3;
        case 128: case 159:
            return Action::cheat; //č jako čít
        default:
            return Action::none;
    }
}