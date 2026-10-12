//
// Created by vojtech on 5/11/26.
//

#include "Drone.h"
#include "Station.h"

#include <cmath>

Drone::Drone(int startEnergy, Module *startModule){
    m_energy = startEnergy;
    setOccupiedModule(startModule);
}

Drone::Drone(const Drone& other, Station* newStation) {
    m_energy = other.m_energy;
    m_invetoryItems.reserve(other.m_invetoryItems.size());
    for (Item* item : other.m_invetoryItems) {
        if (item != nullptr) {
            m_invetoryItems.push_back(item->clone());
        }
    }
    if (other.m_occupiedModule != nullptr && newStation != nullptr) {
        m_occupiedModule = newStation->getModuleAt(other.m_occupiedModule->getPosition());
    } else {
        m_occupiedModule = nullptr;
    }
}

int Drone::getEnergy() {
    return m_energy;
}

void Drone::addEnergy(int amount) {
    if (m_energy+amount<=100) {
        m_energy += amount;
    }
    else {
        m_energy=100;
    }
}

void Drone::drainEnergy(int amountEnergy) {
    m_energy -= std::abs(amountEnergy);
}

Module * Drone::getOccupiedModule() {
    return m_occupiedModule;
}

void Drone::setOccupiedModule(Module *newModule) {
    if (newModule != nullptr) {
        m_occupiedModule = newModule;
    }
}

void Drone::setInventoryItem(Item *item) {
    if (item != nullptr) {
        m_invetoryItems.push_back(item);
    }
}

bool Drone::consumeItem(ItemType itemType) {
    for (auto it = m_invetoryItems.begin(); it != m_invetoryItems.end(); ++it) {
        if ((*it) != nullptr && (*it)->getItemType() == itemType) {
            delete *it;
            m_invetoryItems.erase(it);
            return true;
        }
    }
    return false;
}

std::vector<Item *> Drone::getInventoryItems() {
    return m_invetoryItems;
}

Drone::~Drone() {
    for (Item* item : m_invetoryItems) {
        delete item;
    }
    m_invetoryItems.clear();
}

