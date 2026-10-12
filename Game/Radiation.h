//
// Created by vojtech on 6/15/26.
//

#ifndef PROJEKT_ZOO_RADIATION_H
#define PROJEKT_ZOO_RADIATION_H

#include "Hazard.h"

class Radiation : public Hazard {
    float m_damagePerSecond;

public:
    Radiation(float damagePerSecond);

    ~Radiation() override;

    float getDamagePerSecond();

    HazardType getHazardType() override;

    char getRenderIcon() override;
    Hazard* clone() override;
};

#endif //PROJEKT_ZOO_RADIATION_H
