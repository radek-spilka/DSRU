//
// Created by Radek on 28.04.2026.
//


#include "Module.h"
#include "Hatch.h"
#include "Hazard.h"
#include "Item.h"

Module::Module(Position position, std::vector<Hatch *> hatches) {
    m_hatches = hatches;
    m_position = position;
    m_hazard = nullptr;
    m_item = nullptr;
    m_isFinal = false;
}

Module::~Module() {
    for (Hatch * hatch : m_hatches) {
        delete hatch;
    }
    if (m_item != nullptr) {
        delete m_item;
    }

    if (m_hazard != nullptr) {
        delete m_hazard;
    }

    m_hatches.clear();
}

Position Module::getPosition() {
    return m_position;
}

Hatch * Module::getHatchInDirection(Direction direction) {
    for (Hatch * hatch : m_hatches) {
        if (hatch->getDirection() == direction) {
            return hatch;
        }
    }
    return nullptr;
}

std::vector<Hatch *> Module::getHatches() {
    return std::vector<Hatch *>(m_hatches);
}

void Module::isFinalModule() {
    m_isFinal = true;
}

bool Module::getIsFinal() {
    return m_isFinal;
}

void Module::philHazard(Hazard *hazard) {
    m_hazard = hazard;
}

void Module::philItem(Item *item) {
    m_item = item;
}

char Module::getRenderIcon() {
    if (m_item == nullptr and m_hazard == nullptr) {
        return ' ';
    }

    if (m_item != nullptr) {
        return m_item->getRenderIcon();
    }

    if (m_hazard != nullptr) {
        return m_hazard->getRenderIcon();
    }

}

Hazard * Module::getHazard() {
    return m_hazard;
}

Item * Module::getItem() {
    return m_item;
}

void Module::removeItem() {
    m_item = nullptr;
}

void Module::removeHazard() {
    delete m_hazard;
    m_hazard = nullptr;
}

Module* Module::clone() const {
    std::vector<Hatch*> clonedHatches;
    clonedHatches.reserve(m_hatches.size());
    for (Hatch* hatch : m_hatches) {
        if (hatch != nullptr) {
            clonedHatches.push_back(hatch->clone());
        }
    }
    Module* cloned = new Module(m_position, clonedHatches);
    if (m_hazard != nullptr) {
        cloned->philHazard(m_hazard->clone());
    }
    if (m_item != nullptr) {
        cloned->philItem(m_item->clone());
    }
    if (m_isFinal) {
        cloned->isFinalModule();
    }
    return cloned;
}
