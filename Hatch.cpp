//
// Created by Radek on 28.04.2026.
//

#include "Hatch.h"
#include "Module.h"


Hatch::Hatch(Direction direction, bool isLocked) {
    m_direction = direction;
    m_isLocked = isLocked;
}

Direction Hatch::getDirection() {
    return m_direction;
}

bool Hatch::isLocked() {
    return m_isLocked;
}

void Hatch::unlock() {
    m_isLocked = false;
}

Hatch* Hatch::clone() const {
    return new Hatch(m_direction, m_isLocked);
}
