//
// Created by Radek on 08.05.2026.
//

#pragma once

#ifndef PROJEKT_ZOO_DIRECTION_H
#define PROJEKT_ZOO_DIRECTION_H

enum class Direction {
    North,
    South,
    East,
    West
};

constexpr Direction getOppositeDirection(Direction direction) {
    switch (direction) {
        case Direction::North:
            return Direction::South;
        case Direction::South:
            return Direction::North;
        case Direction::East:
            return Direction::West;
        case Direction::West:
            return Direction::East;
    }

    return direction;
}

#endif //PROJEKT_ZOO_DIRECTION_H