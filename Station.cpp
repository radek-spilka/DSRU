//
// Created by Radek on 28.04.2026.
//

#include "Station.h"
#include "Drone.h"
#include "Hatch.h"
#include "Module.h"

#include <optional>

Station::Station(int mapWidth, int mapHeight) {
    m_mapGrid.resize(mapWidth, std::vector<Module*>(mapHeight, nullptr));
    m_moduleCount = 0;
    m_moduleFactory = new ModuleFactory();
    m_goalModuleGenerated = false;
    m_itemFactory = new ItemFactory();
    m_hazardFactory = new HazardFactory();
    m_finalModule = nullptr;
}

Station::Station(const Station& other) {
    m_moduleCount = other.m_moduleCount;
    m_goalModuleGenerated = other.m_goalModuleGenerated;
    m_moduleFactory = new ModuleFactory();
    m_itemFactory = new ItemFactory();
    m_hazardFactory = new HazardFactory();
    if (other.m_hazardFactory != nullptr) {
        m_hazardFactory->setRequiredMalfunctions(other.m_hazardFactory->getRequiredMalfunctions());
        m_hazardFactory->setAlreadyGeneratedMalfunctions(other.m_hazardFactory->getAlreadyGeneratedMalfunctions());
    }

    int width = other.m_mapGrid.size();
    int height = width > 0 ? other.m_mapGrid[0].size() : 0;
    m_mapGrid.resize(width, std::vector<Module*>(height, nullptr));

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (other.m_mapGrid[x][y] != nullptr) {
                m_mapGrid[x][y] = other.m_mapGrid[x][y]->clone();
            }
        }
    }

    if (other.m_finalModule != nullptr) {
        Position finalPos = other.m_finalModule->getPosition();
        m_finalModule = m_mapGrid[finalPos.x][finalPos.y];
    } else {
        m_finalModule = nullptr;
    }
}

Station::~Station() {
    delete m_moduleFactory;
    delete m_itemFactory;
    delete m_hazardFactory;


     for (std::vector<Module*>& row : m_mapGrid) {
        for (Module* module : row) {
            if (module != nullptr) {
                delete module;
            }
        }
    }

    m_mapGrid.clear();
}

std::vector<std::vector<Module *>> Station::getMapGrid() {
    return m_mapGrid;
}

Module * Station::createNewModule(Position position, std::optional<Direction> fromDirection) {
    Module * newModule = nullptr;

    std::optional<Direction> lockedGoalDirection = std::nullopt;

    if (m_moduleCount == 0 ) {
        newModule = m_moduleFactory->createStartingAirlock(position);
    } else if (fromDirection.has_value()) {
        std::vector<Direction> mandatoryUnlockedDirections;
        std::vector<Direction> mandatoryLockedDirections;
        std::vector<Direction> optionalDirections;

        mandatoryUnlockedDirections.push_back(fromDirection.value());

        analyzeSurroundings(position, fromDirection, mandatoryUnlockedDirections, mandatoryLockedDirections, optionalDirections);

        lockedGoalDirection = findIsolatedGoalDirection(position, optionalDirections);

        newModule = m_moduleFactory->generateNextModule(position, mandatoryUnlockedDirections, mandatoryLockedDirections, optionalDirections, lockedGoalDirection, m_moduleCount);

        if (m_moduleCount % 8 == 0) {
            newModule->philHazard(m_hazardFactory->generate());
        }
        else if (m_moduleCount % 5 ==  0) {
            newModule->philItem(m_itemFactory->generateRandom());
        }

    } else {
        return nullptr;
    }

    if (newModule == nullptr) return nullptr;

    m_mapGrid[position.x][position.y] = newModule;
    m_moduleCount++;

    if (lockedGoalDirection.has_value() && !m_goalModuleGenerated) {
        Direction goalDirection = lockedGoalDirection.value();
        Position goalPosition = position.getNewPosition(goalDirection);
        Direction backToUs = getOppositeDirection(goalDirection);

        m_finalModule = m_moduleFactory->createGoalModule(goalPosition, backToUs);

        m_mapGrid[goalPosition.x][goalPosition.y] = m_finalModule;
        m_moduleCount++;
        m_goalModuleGenerated = true;
    }

    return newModule;
}

void Station::tryToMoveDrone(Drone* drone, Direction direction) {
    if (drone == nullptr) {
        return;
    }

    Module* fromModule = drone->getOccupiedModule();
    Position moveToPosition = fromModule->getPosition().getNewPosition(direction);
    Module* moveToModule = getModuleAt(moveToPosition);

    Hatch* hatch = fromModule->getHatchInDirection(direction);

    if (hatch == nullptr or hatch->isLocked()) {
        return;
    }

    if (moveToModule == nullptr) {
        moveToModule = createNewModule(moveToPosition, getOppositeDirection(direction));
    }

    drone->setOccupiedModule(moveToModule);
}

int Station::getModuleCount() {
    return m_moduleCount;
}

Module * Station::getModuleAt(Position position) {
    if (isPositionInMapBoundaries(position)) {
        return m_mapGrid[position.x][position.y];
    }

    return nullptr;
}

bool Station::isPositionInMapBoundaries(Position position) {
    if (position.x < 0 or position.x >= m_mapGrid.size() or position.y < 0 or position.y >= m_mapGrid[0].size()) {
        return false;
    }

    return true;
}

void Station::analyzeSurroundings(Position position,
                                  std::optional<Direction> ignoreDirection,
                                  std::vector<Direction>& outMandatoryUnlocked,
                                  std::vector<Direction>& outMandatoryLocked,
                                  std::vector<Direction>& outOptional) {

    Direction allDirs[] = {Direction::North, Direction::South, Direction::East, Direction::West};

    for (Direction direction : allDirs) {
        if (ignoreDirection.has_value() && direction == ignoreDirection.value()) {
            continue;
        }

        Position neighborPos = position.getNewPosition(direction);

        if (!isPositionInMapBoundaries(neighborPos)) continue;

        Module* neighbor = getModuleAt(neighborPos);

        if (neighbor != nullptr) {
            Direction directionToUs = getOppositeDirection(direction);
            Hatch* neighborHatch = neighbor->getHatchInDirection(directionToUs);

            if (neighborHatch != nullptr) {
                if (neighborHatch->isLocked()) {
                    outMandatoryLocked.push_back(direction);
                } else {
                    outMandatoryUnlocked.push_back(direction);
                }
            }
        } else {
            outOptional.push_back(direction);
        }
    }


}

std::optional<Direction> Station::findIsolatedGoalDirection(Position currentPosition, std::vector<Direction>& optionalDirections) {
    if (m_moduleCount < m_whenToGenerateGoal || m_goalModuleGenerated) {
        return std::nullopt;
    }

    for (size_t i = 0; i < optionalDirections.size(); i++) {
        Direction potentialDirection = optionalDirections[i];
        Position potentialGoalPosition = currentPosition.getNewPosition(potentialDirection);

        int goalNeighborsCount = 0;

        for (Direction checkDirection : m_allDirs) {
            Position checkPosition = potentialGoalPosition.getNewPosition(checkDirection);

            if (isPositionInMapBoundaries(checkPosition) && getModuleAt(checkPosition) != nullptr) {
                goalNeighborsCount++;
            }
        }

        if (goalNeighborsCount == 0) {
            optionalDirections.erase(optionalDirections.begin() + i);

            return potentialDirection;
        }
    }

    return std::nullopt;
}

void Station::unlockHatchInDirection(Module *droneModule, Direction hatchDirection) {
    if (droneModule == nullptr) {
        return;
    }

    Hatch* myHatch = droneModule->getHatchInDirection(hatchDirection);
    if (myHatch != nullptr) {
        myHatch->unlock();
    }

    Position neighborPosition = droneModule->getPosition().getNewPosition(hatchDirection);

    Module* neighborModule = getModuleAt(neighborPosition);

    if (neighborModule != nullptr) {
        Direction oppositeDirection = getOppositeDirection(hatchDirection);
        Hatch* neighborHatch = neighborModule->getHatchInDirection(oppositeDirection);

        if (neighborHatch != nullptr) {
            neighborHatch->unlock();
        }
    }
}

HazardFactory * Station::getHazardFactory() {
    return m_hazardFactory;
}

ItemFactory * Station::getItemFactory() {
    return m_itemFactory;
}

void Station::unlockFinalModule() {
    for (Hatch * hatch: m_finalModule->getHatches()) {
        unlockHatchInDirection(m_finalModule, hatch->getDirection());
    }
}

Module * Station::getFinalModule() {
    return m_finalModule;
}
