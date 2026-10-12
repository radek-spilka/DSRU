//
// Created by Radek on 28.04.2026.
//

#ifndef PROJEKT_ZOO_MODULE_H
#define PROJEKT_ZOO_MODULE_H


#include <vector>

#include "Direction.h"
#include "Position.h"

class Hatch;
class Hazard;
class Item;

class Module {
    Position m_position;
    std::vector<Hatch *> m_hatches;
    Hazard * m_hazard;
    Item * m_item;
    bool m_isFinal;
public:
    Module(Position position, std::vector<Hatch*> hatches);
    ~Module();
    Position getPosition();
    Hatch * getHatchInDirection(Direction direction);
    std::vector<Hatch *> getHatches();
    void isFinalModule();
    bool getIsFinal();
    void philHazard(Hazard * hazard);
    void philItem(Item * item);
    char getRenderIcon();
    Hazard * getHazard();
    Item * getItem();
    void removeItem();
    void removeHazard();
    Module* clone() const;
};


#endif //PROJEKT_ZOO_MODULE_H