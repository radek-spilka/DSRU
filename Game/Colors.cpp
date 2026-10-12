//
// Created by Radek on 19.06.2026.
//

#include "Colors.h"

Colors::Colors() {
}

Colors * Colors::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new Colors();
    }

    return s_instance;
}
