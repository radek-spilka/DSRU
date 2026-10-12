//
// Created by Radek on 28.04.2026.
//

#pragma once
#ifndef PROJEKT_ZOO_POSITION_H
#define PROJEKT_ZOO_POSITION_H

#endif //PROJEKT_ZOO_POSITION_H

#include "Direction.h"

struct Position {
    int x;
    int y;

public:
    Position getNewPosition(Direction direction) const {
        Position nextPos = {x, y};
        nextPos.move(direction);
        return nextPos;
    }

private:
    void move(Direction direction) {
        switch(direction) {
            case Direction::North: y -= 1;
                break;
            case Direction::South: y += 1;
                break;
            case Direction::East: x += 1;
                break;
            case Direction::West: x -= 1;
                break;
        }
    }


};


