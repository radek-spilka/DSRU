//
// Created by Radek on 28.04.2026.
//

#include "ModuleFactory.h"

#include <algorithm>

#include "Module.h"
#include "Hatch.h"

#include <random>


ModuleFactory::ModuleFactory() {

}

Module* ModuleFactory::createStartingAirlock(Position position) {
    Direction firstHatch = rand() % 100 < 50 ? Direction::South : Direction::East;
    Direction secondHatch = rand() % 100 < 50 ? Direction::North : Direction::West;

    std::vector<Hatch*> hatches;
    hatches.push_back(new Hatch(firstHatch, false));
    hatches.push_back(new Hatch(secondHatch, false));

    Module* newModule = new Module(position, hatches);

    return newModule;
}

Module * ModuleFactory::generateNextModule(Position position,
                                           std::vector<Direction> mandatoryUnlockedDirections,
                                           std::vector<Direction> mandatoryLockedDirections,
                                           std::vector<Direction> optionalDirections,
                                           std::optional<Direction> lockedGoalDirection,
                                           int moduleCount) {
    std::vector<Hatch*> hatches;

    for (Direction direction : mandatoryUnlockedDirections) {
        hatches.push_back(new Hatch(direction, false));
    }

    for (Direction direction : mandatoryLockedDirections) {
        hatches.push_back(new Hatch(direction, true));
    }

    if (lockedGoalDirection.has_value()) {
        hatches.push_back(new Hatch(lockedGoalDirection.value(), true));
    }

    if (!optionalDirections.empty()) {

        for (int i = optionalDirections.size() - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            std::swap(optionalDirections[i], optionalDirections[j]);
        }

        int currentChance = 95;
        const int chanceDecay = 40;

        for (Direction direction : optionalDirections) {
            bool createNewHatch = false;

            if ((rand() % 100) < currentChance) {
                createNewHatch = true;
            }

            currentChance -= chanceDecay;

            if (moduleCount < 5) createNewHatch = true;

            if (createNewHatch) {
                bool isLocked = ((rand() % 100) < 2.5);
                hatches.push_back(new Hatch(direction, isLocked));
            }
        }
    }

    return new Module(position, hatches);
}

Module* ModuleFactory::createGoalModule(Position position, Direction backDirection) {
    std::vector<Hatch*> hatches;

    hatches.push_back(new Hatch(backDirection, true));

    Module * finalModule = new Module(position, hatches);
    finalModule->isFinalModule();

    return finalModule;
}
