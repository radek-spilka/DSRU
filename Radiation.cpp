//
// Created by vojtech on 6/15/26.
//

#include "Radiation.h"

#include <iostream>
#include <ostream>

Radiation::Radiation(float damagePerSecond) {
    m_damagePerSecond = damagePerSecond;
}

Radiation::~Radiation() {
}

float Radiation::getDamagePerSecond() {
    return m_damagePerSecond;
}


HazardType Radiation::getHazardType() {
    return HazardType::Radiation;
}

char Radiation::getRenderIcon() {
    return 'R';
}

Hazard* Radiation::clone() {
    return new Radiation(m_damagePerSecond);
}
