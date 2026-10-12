//
// Created by Radek on 28.04.2026.
//

#ifndef PROJEKT_ZOO_STATION_H
#define PROJEKT_ZOO_STATION_H

#include <vector>

#include "Direction.h"
#include "ModuleFactory.h"
#include "Position.h"

#include <optional>

#include "HazardFactory.h"
#include "ItemFactory.h"

class Module;
class Drone;

class Station {
    std::vector<std::vector<Module*>> m_mapGrid;
    ModuleFactory * m_moduleFactory;
    int m_moduleCount;
    bool m_goalModuleGenerated;
    const int m_whenToGenerateGoal=15;
    const Direction m_allDirs[4] = {Direction::North, Direction::South, Direction::East, Direction::West};
    Module * m_finalModule;
    ItemFactory * m_itemFactory;
    HazardFactory * m_hazardFactory;

public:
    Station(int mapWidth, int mapHeight);
    Station(const Station& other);
    ~Station();
    Module * getModuleAt(Position position);
    std::vector<std::vector<Module*>> getMapGrid();
    Module * createNewModule(Position position, std::optional<Direction> fromDirection);
    void tryToMoveDrone(Drone * drone, Direction direction);
    int getModuleCount();
    void unlockHatchInDirection(Module * droneModule, Direction hatchDirection);
    HazardFactory * getHazardFactory();
    ItemFactory * getItemFactory();
    void unlockFinalModule();
    Module* getFinalModule();
private:
    bool isPositionInMapBoundaries(Position position);
    void analyzeSurroundings(Position position,
                                  std::optional<Direction> ignoreDirection,
                                  std::vector<Direction>& outMandatoryUnlocked,
                                  std::vector<Direction>& outMandatoryLocked,
                                  std::vector<Direction>& outOptional);
    std::optional<Direction> findIsolatedGoalDirection(Position currentPosition, std::vector<Direction>& optionalDirections);
};


#endif //PROJEKT_ZOO_STATION_H