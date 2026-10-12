//
// Created by vojtech on 6/15/26.
//

#include "HazardFactory.h"

#include <cstdlib>

#include "Enemy.h"
#include "Malfunction.h"
#include "Radiation.h"

HazardFactory::HazardFactory() {
    m_requiredMalfunctions = 5;
    m_alreadyGeneratedMalfunctions = m_requiredMalfunctions;
}

Hazard * HazardFactory::generate() {
    int randomness = rand() % 100;

    if (randomness < 40) {
        return new Enemy(10, (rand() % (10 - 5 + 1) + 5));
    }

    if (randomness < 60) {
        return new Radiation(rand() % (15 - 5 + 1) + 5);
    }

    if (m_alreadyGeneratedMalfunctions > 0) {
        m_alreadyGeneratedMalfunctions--;
        return new Malfunction();
    }

    return new Radiation(rand() % (15 - 5 + 1) + 5);
}

int HazardFactory::getRequiredMalfunctions() {
    return m_requiredMalfunctions;
}

void HazardFactory::repairedMalfunctions() {
    m_requiredMalfunctions--;
}

int HazardFactory::getAlreadyGeneratedMalfunctions() {
    return m_alreadyGeneratedMalfunctions;
}

void HazardFactory::setRequiredMalfunctions(int val) {
    m_requiredMalfunctions = val;
}

void HazardFactory::setAlreadyGeneratedMalfunctions(int val) {
    m_alreadyGeneratedMalfunctions = val;
}
