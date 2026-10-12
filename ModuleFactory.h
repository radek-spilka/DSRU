//
// Created by Radek on 28.04.2026.
//

#ifndef PROJEKT_ZOO_MODULEFACTORY_H
#define PROJEKT_ZOO_MODULEFACTORY_H

#include <vector>
#include <optional>

#include "Position.h"

class Station;
class Hatch;
class Module;

class ModuleFactory {

public:
    ModuleFactory();
    Module * createStartingAirlock(Position position);
    Module * generateNextModule(Position position,
                                           std::vector<Direction> mandatoryUnlockedDirections,
                                           std::vector<Direction> mandatoryLockedDirections,
                                           std::vector<Direction> optionalDirections,
                                           std::optional<Direction> lockedGoalDirection,
                                           int moduleCount
                                           );
    Module * createGoalModule(Position position, Direction backDirection);
};


#endif //PROJEKT_ZOO_MODULEFACTORY_H