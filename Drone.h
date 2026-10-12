//
// Created by vojtech on 5/11/26.
//

#ifndef PROJEKT_ZOO_DRONE_H
#define PROJEKT_ZOO_DRONE_H

#include "Item.h"
#include <vector>

#include "Module.h"


class Station;

class Drone {
    int m_energy;
    std::vector<Item*> m_invetoryItems;
    Module* m_occupiedModule;

public:
    Drone(int startEnergy, Module* startModule);
    Drone(const Drone& other, Station* newStation);

    int getEnergy();
    void addEnergy(int amount);
    void drainEnergy(int amountEnergy);

    Module* getOccupiedModule();

    void setOccupiedModule(Module* newModule);

    void setInventoryItem(Item* item);

    bool consumeItem(ItemType itemType);

    std::vector<Item*> getInventoryItems();
    ~Drone();

};


#endif //PROJEKT_ZOO_DRONE_H
