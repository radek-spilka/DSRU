//
// Created by Radek on 28.04.2026.
//

#ifndef PROJEKT_ZOO_HATCH_H
#define PROJEKT_ZOO_HATCH_H

#include "Direction.h"

class Hatch {
    bool m_isLocked;
    Direction m_direction;

public:
    Hatch(Direction direction, bool isLocked);
    Direction getDirection();
    bool isLocked();
    void unlock();
    Hatch* clone() const;
};


#endif //PROJEKT_ZOO_HATCH_H